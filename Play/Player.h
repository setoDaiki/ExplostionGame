#pragma once
#include "GameObject.h"

class Player :public GameObject {
public:
	Player(class ObjectResource* resource,const DirectX::XMFLOAT3& pos);
	~Player()override;

	//----------------------------------
	///  [機能] プレイヤーの更新
	//----------------------------------
	void UpdateObject()override;

	//---------------------------------------
	/// [機能]  オブジェクトを消す後処理
	//---------------------------------------
	void ShutDown()override;

private:
	void Move();    // 移動
	bool IsHitFrontOrBackWall(const DirectX::XMFLOAT3& pos);  // 前後の壁にぶつかったか
	bool IsHitSideWall(const DirectX::XMFLOAT3& pos);         // 左右の壁とぶつかったか

	class SphereHitBox* mHitBox;   // 当たり判定

};