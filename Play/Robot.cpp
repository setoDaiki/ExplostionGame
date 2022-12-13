#include "Robot.h"
#include "Random.h"
#include "MyMath.h"
#include "Player.h"
#include "SphereHitBox.h"
#include "Collision.h"
#include <iostream>

Robot::Robot(ObjectResource* resource, DirectX::XMFLOAT3 pos)
// ロボットの位置、回転大きさを基底クラスのコンストラクタで設定する
	:GameObject(resource, pos, DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT3(0.003f, 0.003f, 0.003f))
	, mStopCounter(0)
{
	mHitBox = new SphereHitBox(GetPosition(),2.0f,"Robot");
	float moveAngle = Random::RandomFloat(0,360);
	DirectX::XMFLOAT3 robotRotate(0.0f,moveAngle,0.0f);
	SetRotation(robotRotate);
	mMoveDirection = Math::GetFront(moveAngle);
	mMoveDirection = Math::MulScaler(mMoveDirection,0.3f);
}


Robot::~Robot() {
	
}

void Robot::ShutDown() {
	Collision::RemoveHitBox(mHitBox);
}


void Robot::UpdateObject() {

	if (GetState() == EOther) {    // その他にした次のフレームで
		SetState(EDead);           // デッド状態に更新
		return;                    // 移動と衝突検知前に早期リターン
	}
	const HitObjectInfo hitObject = Collision::GetHitObjectInfo(*mHitBox);  // 自身とhitしたオブジェクト検知
	if (hitObject.Name == "Robot") {                                        // hitしたのがRobotタグのオブジェクトなら
																			// Robotと衝突したら消iしたいけど,すぐ消すと不具合が出る
		SetState(EOther);                                                   // そのためいったんその他状態にして、次にフレームで消す
		return;                                                             // 移動前に早期リターン
	}
	if (hitObject.Name == "Player") {                                       // hitしたのがPlayerタグのオブジェクトなら
		BePushedByPlayer(hitObject);                                        // PlayerにRobotが押される
		return;                                                             // 移動前に早期リターン
	}


	DirectX::XMFLOAT3 pos = GetPosition(); // 現在位置の取得
	pos = Math::Add(pos,mMoveDirection);   // 現在位置に移動方向を加える
	
	if (IsHitFrontOrBackWall(pos)) {      // 前後の壁に当たってたら
		ReverseMovementX();                // X軸の移動を反転する
	}
	
	if (IsHitSideWall(pos)) {              // 再度の壁に当たってたら
		ReverseMovementZ();                // Z軸の移動を反転する
	}

	SetPosition(pos);                      // 位置の設定
}

//------------------------------------------------------
//   playerにおされる
//------------------------------------------------------
void Robot::BePushedByPlayer(HitObjectInfo hitObject) {
	DirectX::XMFLOAT3 moveVec = Math::Sub(GetPosition(), hitObject.Position);   // プレイヤーからロボットの方向ベクトル
	if (moveVec.x > moveVec.z) {
		moveVec.z = 0.0f;
	}
	else {
		moveVec.x = 0.0f;
	}
	moveVec = Math::MulScaler(moveVec, 0.3f);                                   // 移動量の調整
	DirectX::XMFLOAT3 pos = Math::Add(moveVec, GetPosition());                  // 移動量を現在位置に加える
	if (IsHitFrontOrBackWall(pos) || IsHitSideWall(pos)) {                      // 加えた結果どれかの壁に当たるなら
		pos = Math::Sub(pos,moveVec);						                    // 移動をなかったことにする
	}

	SetPosition(pos);                                                           // 位置の更新
}

//----------------------------------------
//  X軸方向の移動を反転させる
//----------------------------------------
void Robot::ReverseMovementX() {
	const DirectX::XMFLOAT3& prevRot = GetRotation();          // 現在角度の取得
	DirectX::XMFLOAT3 reverseRot = prevRot;             
	reverseRot.y = 180.0f - prevRot.y;                         // X軸移動反転後の角度は ・・・ 180°- 前の角度 
	SetRotation(reverseRot);                                   // 角度更新
	mMoveDirection = Math::GetFront(reverseRot.y);             // 求めた角度を用いてX軸の移動方向を反転
	mMoveDirection = Math::MulScaler(mMoveDirection, 0.3f);    // 速度の調整
}

//------------------------------------------
//   Z軸方向の移動を反転させる
//------------------------------------------
void Robot::ReverseMovementZ() {
	const DirectX::XMFLOAT3& prevRot = GetRotation();          // 現在角度の取得
	DirectX::XMFLOAT3 reverseRot = prevRot;
	reverseRot.y = 360.0f - prevRot.y;                         // Z軸移動反転後の角度は  ・・・ 360 - 前の角度
	SetRotation(reverseRot);                                   // 角度更新
	mMoveDirection = Math::GetFront(reverseRot.y);             // 求めた角度を用いてZ軸の移動を反転
	mMoveDirection = Math::MulScaler(mMoveDirection, 0.3f);    // 速度の調整
}


//-------------------------------------------
//   前後の壁にぶつかったのかを返す
//-------------------------------------------
bool Robot::IsHitFrontOrBackWall(const DirectX::XMFLOAT3& pos) {
	if (pos.x > 48.0f || pos.x < -48.0f) {   // x軸が48以上か-48以上なら
		return true;                         // ぶつかってる
	}
	return false;                            // そうでないならぶつかってない
}

//-------------------------------------------
//   左右の壁にぶつかったのかを返す
//-------------------------------------------
bool  Robot::IsHitSideWall(const DirectX::XMFLOAT3& pos) {
	if (pos.z > 48.0f || pos.z < -48.0f) {   // z軸が48以上か-48以下なら
		return true;                         // ぶつかってる
	}
	return false;                            // そうでないならぶつかってない
}