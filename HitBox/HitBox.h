#pragma once
#include <DirectXmath.h>
#include <string>

using namespace DirectX;


class HitBox{
public:
	HitBox(const std::string& tagName = "Object");
	virtual ~HitBox() {};

	//------------------------------------------------------------
	/// [機能] 球との衝突判定
	/// [引数] このインスタンスと衝突を判別する球
	/// [戻り値] 衝突していたらtrue、衝突していないならfalse
	//------------------------------------------------------------
	virtual bool IsHitWithSphere(const class SphereHitBox& sphere)const = 0;

	//--------------------------------------------------
	/// [機能] 位置の取得
	/// [戻り値] 当たり判定の中心位置
	//---------------------------------------------------
	virtual DirectX::XMFLOAT3 GetPosition()const = 0;
	//----------------------------------------------------------------------------------
	/// [機能] 当たり判定のタグ名(当たり判定を持っているオブジェクトの名前など)の取得
	/// [戻り値] 当たり判定のタグ名の取得
	//-----------------------------------------------------------------------------------
	virtual std::string GetTag()const;

	
private:
	const std::string mTagName;
};
