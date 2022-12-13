#include "GameObject.h"
#include "Engine.h"
#include "App.h"
#include <d3dx12.h>
#include "SharedStruct.h"
#include "ConstantBuffer.h"
#include "RootSignature.h"
#include "PipelineState.h"
#include <filesystem>
#include <iostream>
#include "Camera.h"
#include "MeshResource.h"
#include "HitBox.h"

using namespace DirectX;



//----------------------------------------------------------------
//      コンストラクター(位置、回転、拡大率、見た目)の初期化
//----------------------------------------------------------------
GameObject::GameObject(
	ObjectResource* resource,
	const XMFLOAT3& pos,
	const XMFLOAT3& rot,
	const XMFLOAT3& scale)
	:mPosition(pos.x,pos.y,pos.z)
	,mRotation(rot.x,rot.y,rot.z)
	,mScale(scale.x,scale.y,scale.z)
	,mResource(resource)
	,mNeedUpdateWorldMat(true)
	,mNeedErase(false)
	,mState(EActive)
{
	SetTransform();
	UpdateWorldMat();
}


//---------------------------------------------------------
//     デストラクタ―
//---------------------------------------------------------
GameObject::~GameObject() {
	for (int i = 0; i < Engine::FRAME_BUFFER_COUNT; i++) {
		delete mTransform[i];
		mTransform[i] = 0;
	}
}

void GameObject::Update()
{
	
	UpdateObject();         // オブジェクト更新
	UpdateWorldMat();       // ワールド行列更新
	if (mState == EDead) {  // 死に状態のオブジェクトは
		ShutDown();         // シャットダウンしてから
		mNeedErase = true;  // 消していい状態にする
	}
}


//-------------------------------------------------
//    3Dオブジェクトの描画
//-------------------------------------------------
void GameObject::Draw(const Camera& camera)
{
	UpdateViewMat(camera);
	auto currentIndex = Engine::Instance()->CurrentBackBufferIndex();  // カレントインデックス取得
	mResource->Draw(*mTransform[currentIndex]);  // コンスタントバッファを渡す
}

//---------------------------------------
//  オブジェクトを消してよいのか取得
//---------------------------------------
bool GameObject::NeedErase() {
	return mNeedErase;
}




//=================================    ここからprotectedメソッド     ==================================================//






//-------------------------------------------------
// 位置のセッター、ゲッター
//-------------------------------------------------
void GameObject::SetPosition(const XMFLOAT3& pos) {
	mPosition = pos;
	mNeedUpdateWorldMat = true;
}

const XMFLOAT3& GameObject::GetPosition() {
	return mPosition;
}

//------------------------------------------------
//   角度のセッター、ゲッター
//------------------------------------------------
void GameObject::SetRotation(const XMFLOAT3& rot) {
	mRotation = rot;
	mNeedUpdateWorldMat = true;
}

const XMFLOAT3& GameObject::GetRotation() {
	return mRotation;
}

//------------------------------------------------
//   拡大率のセッター、ゲッター
//------------------------------------------------
void GameObject::SetScale(const XMFLOAT3& scale) {
	mScale = scale;
	mNeedUpdateWorldMat = true;
}

const XMFLOAT3& GameObject::GetScale() {
	return mScale;
}

//------------------------------------------------
//   状態のセッター,ゲッター
//------------------------------------------------
void GameObject::SetState(State state) {
	mState = state;
}

GameObject::State GameObject::GetState() {
	return mState;
}

//------------------------------------------------
//    ワールド座標の更新
//------------------------------------------------
void GameObject::UpdateWorldMat() {
	
	if (mNeedUpdateWorldMat) {
		for (size_t i = 0; i < Engine::FRAME_BUFFER_COUNT; i++) {
			//現在のバッファのコンスタントバッファの取得
			auto transform = mTransform[i]->GetPtr<Transform>();
			//ワールド座標の更新用の行列の準備
			XMMATRIX scale;
			scale = XMMatrixScaling(mScale.x, mScale.y, mScale.z);  //スケール行列
			XMMATRIX rotation, rotationX, rotationY, rotationZ;
			float radianZ = XMConvertToRadians(mRotation.z);	// Z軸回転のラジアン値計算
			rotationZ = XMMatrixRotationZ(radianZ);				// Z軸のローテーション行列
			float radianY = XMConvertToRadians(mRotation.y);	// Y軸周りのラジアン値計算
			rotationY = XMMatrixRotationY(radianY);				// Y軸のローテーション行列
			float radianX = XMConvertToRadians(mRotation.x);	// X軸周りのラジアン値計算
			rotationX = XMMatrixRotationX(radianX);				// X軸のローテーション行列
			rotation = XMMatrixIdentity();
			rotation = XMMatrixMultiply(rotation, rotationZ);  //行列の乗算
			rotation = XMMatrixMultiply(rotation, rotationY);  //行列の乗算
			rotation = XMMatrixMultiply(rotation, rotationX);  //行列の乗算
			XMMATRIX translation;
			translation = XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z);  //位置行列

			//ワールド座標更新
			transform->World = XMMatrixIdentity();
			transform->World = XMMatrixMultiply(transform->World, scale);
			transform->World = XMMatrixMultiply(transform->World, rotation);
			transform->World = XMMatrixMultiply(transform->World, translation);
			mNeedUpdateWorldMat = false;
		}
	}
}

//--------------------------------------------------
//  view行列の更新
//--------------------------------------------------
void GameObject::UpdateViewMat(const Camera& camera) {
	auto currentIndex = Engine::Instance()->CurrentBackBufferIndex();
	XMFLOAT3 pos = camera.GetPosition();   // カメラ位置の取得
	XMFLOAT3 look = camera.GetLookPos();   // 注視位置の取得
	auto eyePos = XMVectorSet(pos.x, pos.y, pos.z, 0.0f);    // XMFLOAT3型をXMVECTORに変換
	auto lookPos = XMVectorSet(look.x,look.y,look.z,0.0f);   // XMFLOAT3型をXMVECTORに変換
	auto upward = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);       //カメラの上方ベクトル
	auto ptr = mTransform[currentIndex]->GetPtr<Transform>();
	ptr->View = XMMatrixLookAtRH(eyePos, lookPos, upward);   // ビュー行列の設定
}

//--------------------------------------------------
//  constantBufferのセット
//--------------------------------------------------
void GameObject::SetTransform() {

	constexpr auto fov = XMConvertToRadians(45);  // 画角の設定
	auto aspect = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT); // アスペクト比
	// フロントバッファとバックバッファの二つ分の行列のセット
	for (size_t i = 0; i < Engine::FRAME_BUFFER_COUNT; i++)
	{
		mTransform[i] = new ConstantBuffer(sizeof(Transform));
		if (!mTransform[i]->IsValid())
		{
			assert(!"変換行列用定数バッファの生成に失敗\n");
		}

		// 変換行列の登録
		auto ptr = mTransform[i]->GetPtr<Transform>();
		ptr->World = XMMatrixIdentity();
		ptr->Proj = XMMatrixPerspectiveFovRH(fov, aspect, 0.3f, 1000.0f);
	}
}