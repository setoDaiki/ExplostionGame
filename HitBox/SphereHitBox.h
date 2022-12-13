#pragma once
#include "HitBox.h"
#include <iostream>

class SphereHitBox :public HitBox {
public:
	SphereHitBox(const XMFLOAT3& position,float radius,const std::string& tagName = "Object");
	~SphereHitBox()override;

	//------------------------------------------------------------
	/// [機能] 球との衝突判定
	/// [引数] このインスタンスと衝突を判別する球
	/// [戻り値] 衝突していたらtrue、衝突していないならfalse
	//------------------------------------------------------------
	bool IsHitWithSphere(const SphereHitBox& sphere)const override;

	//-------------------------------------------------------------
	/// [機能] 当たり判定の中心位置の取得
	/// [戻り値] 当たり判定の中心位置
	//-------------------------------------------------------------
	XMFLOAT3 GetPosition()const override{ return mPosition; }

	//-------------------------------------------------------------
	/// [機能] 当たり判定の半径の取得
	/// [戻り値] 当たり判定の半径
	//-------------------------------------------------------------
	float GetRadius()const { return mRadius; }

	

private:
	const XMFLOAT3& mPosition;   // ゲームオブジェクトの位置を参照している
	float mRadius;               // 当たり判定の半径
};
