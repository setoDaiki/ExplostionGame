#pragma once
#include "GameObject.h"

class Robot : public GameObject {
public:
	Robot(ObjectResource* resource,DirectX::XMFLOAT3 pos);
	~Robot()override;

	

private:
	void ShutDown()override;           // オブジェクトの解放
	void UpdateObject()override;       // 更新
	void BePushedByPlayer(struct HitObjectInfo hitObject);     // プレイヤーに押される

	void ReverseMovementX();       // X軸方向の移動を反転させる
	void ReverseMovementZ();       // Z軸方向の移動を反転させる

	bool IsHitFrontOrBackWall(const DirectX::XMFLOAT3& pos);      // 前後の壁にぶつかったのかを返す
	bool IsHitSideWall(const DirectX::XMFLOAT3& pos);              // 左右の壁にぶつかったのかを返す

	int mStopCounter;      // 停止し続けたフレーム時間

	class SphereHitBox* mHitBox;
	struct DirectX::XMFLOAT3 mMoveDirection;
};
