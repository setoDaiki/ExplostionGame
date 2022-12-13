#include "Collision.h"
#include "SphereHitBox.h"


std::vector<HitBox*> Collision::mHitBoxs;  // static変数の定義


//-----------------------------------------------
//   HitBoxの追加
//------------------------------------------------
void Collision::AddHitBox(HitBox* hitBox) {
	mHitBoxs.emplace_back(hitBox);   // 引数のHitBoxを追加
}

//----------------------------------------
//   HitBoxの削除
//----------------------------------------
void Collision::RemoveHitBox(HitBox* hitBox) {
	auto iter = std::find(mHitBoxs.begin(), mHitBoxs.end(), hitBox);
	mHitBoxs.erase(iter);
	mHitBoxs.shrink_to_fit();
}

//------------------------------------------------------------
//   当たった全てのオブジェクトの情報を取得
//------------------------------------------------------------
std::vector<HitObjectInfo> Collision::GetAllHitObjectsInfo(const SphereHitBox& hitBox) {
	std::vector<HitObjectInfo> hitObjectsInfo;
	for (auto hit : mHitBoxs) {
		if (hit->IsHitWithSphere(hitBox)) {
			HitObjectInfo obj;
			obj.Position = hit->GetPosition();
			obj.Name = hit->GetTag();
			hitObjectsInfo.emplace_back(obj);
		}
	}
	return hitObjectsInfo;
}

//---------------------------------------------------------------------
//   当たった一つのオブジェクトの情報を取得
//---------------------------------------------------------------------
HitObjectInfo Collision::GetHitObjectInfo(const SphereHitBox& hitBox) {
	
	for (auto hit : mHitBoxs) {
		
		if (hit->IsHitWithSphere(hitBox)) {
			HitObjectInfo obj;
			obj.Name = hit->GetTag();
			obj.Position = hit->GetPosition();
			return obj;
		}
	}
	HitObjectInfo didNotHit;
	didNotHit.Name = "Didn't hit";
	return didNotHit;
}