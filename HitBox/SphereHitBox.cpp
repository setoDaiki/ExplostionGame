#include "SphereHitBox.h"
#include "MyMath.h"
#include "Collision.h"

SphereHitBox::SphereHitBox(const XMFLOAT3& position,float radius,const std::string& tagName)
	:HitBox(tagName)
	,mPosition(position)
	,mRadius(radius)
{
	Collision::AddHitBox(this);
}

SphereHitBox::~SphereHitBox() {
}


//---------------------------------
//   球と球の衝突判定
//---------------------------------
bool SphereHitBox::IsHitWithSphere(const SphereHitBox& sphere)const {
	if (&sphere == this) {  // 自分と自分の衝突では
		return false;       // 衝突してないことにする
	}
	XMFLOAT3 pos = sphere.GetPosition();
	float radius = sphere.GetRadius();
	const XMFLOAT3 subVec = Math::Sub(pos, mPosition);   // 中心間距離
	float lenght2 = subVec.x * subVec.x + subVec.y * subVec.y + subVec.z * subVec.z;  // 中心間距離の二乗
	// 半径の和の二乗と中心間距離2乗で衝突検知
	if (lenght2 < ((radius + mRadius) * (radius * mRadius))) {
		return true;  // 衝突している
		
	}
	return false;  
}