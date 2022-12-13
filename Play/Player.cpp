#include "Player.h"
#include "Object2DResource.h"
#include "KeyInput.h"
#include <iostream>
#include "SphereHitBox.h"
#include "Collision.h"
#include <string>

Player::Player(ObjectResource* resource,const DirectX::XMFLOAT3& pos) 
	:GameObject(resource,pos,DirectX::XMFLOAT3(0.0f,0.0f,0.0f),DirectX::XMFLOAT3(0.05f,0.05f,0.05f))
{
	mHitBox = new SphereHitBox(GetPosition(), 2.8f,"Player");
}


Player::~Player() {

}

void Player::ShutDown() {
	Collision::RemoveHitBox(mHitBox);
}

//--------------------------------
//   プレイヤーの更新
//--------------------------------
void Player::UpdateObject() {
	Move();
}


//-----------------------------------------
//    移動する
//-----------------------------------------
void Player::Move() {

	const DirectX::XMFLOAT3& prevPos = GetPosition();           // 現在位置取得
	DirectX::XMFLOAT3 pos = prevPos;							// 前までの位置を代入
	DirectX::XMFLOAT3 rot = GetRotation();						// 現在角度取得
	if (KeyInput::GetKeyState(DIK_W) == EHold) {				// Wがおされたら
		pos.z += 0.5f;											// +Z方向に移動
		rot.y = 0.0f;											// 進行方向を向く
	}
	if (KeyInput::GetKeyState(DIK_S) == EHold) {			    // Sがおされたら
		pos.z -= 0.5f;											// -Z方向に移動
		rot.y = 180.0f;											// 進行方向を向く
	}
	if (KeyInput::GetKeyState(DIK_A) == EHold) {				// Aが押されたら
		pos.x += 0.5f;											// +X方向に移動
		rot.y = 90.0f;											// 進行方向を向く
	}
	if (KeyInput::GetKeyState(DIK_D) == EHold) {				// Dがおされたら
		pos.x -= 0.5f;											// -X方向に移動
		rot.y = 270.0f;											// 進行方向を向く
	}

	if (IsHitFrontOrBackWall(pos) || IsHitSideWall(pos)) {      // 壁に当たったら
		return;                                                 // 位置をセットせずに(変更せずに帰る)
	}

	SetPosition(pos);											// 位置情報の更新
	SetRotation(rot);											// 角度情報の更新
	
}

//-------------------------------------------
//   前後の壁にぶつかったのかを返す
//-------------------------------------------
bool Player::IsHitFrontOrBackWall(const DirectX::XMFLOAT3& pos) {
	if (pos.x > 48.0f || pos.x < -48.0f) {   // x軸が48以上か-48以上なら
		return true;                         // ぶつかってる
	}
	return false;                            // そうでないならぶつかってない
}

//-------------------------------------------
//   左右の壁にぶつかったのかを返す
//-------------------------------------------
bool  Player::IsHitSideWall(const DirectX::XMFLOAT3& pos) {
	if (pos.z > 48.0f || pos.z < -48.0f) {   // z軸が48以上か-48以下なら
		return true;                         // ぶつかってる
	}
	return false;                            // そうでないならぶつかってない
}




