#pragma once
#include <vector>
#include <string>
#include <DirectXMath.h>

struct HitObjectInfo {
	std::string Name;
	DirectX::XMFLOAT3 Position;
};


class Collision {
public:
	
	//-------------------------------------------------
	/// [機能] ゲームにある当たり判定を追加する
	/// [引数] 追加する当たり判定
	//--------------------------------------------------
	static void AddHitBox(class HitBox* hitBox);

	//-------------------------------------------------
	/// [機能] ゲームにある当たり判定を削除する
	/// [引数] 削除する当たり判定
	//--------------------------------------------------
	static void RemoveHitBox(class HitBox* hitBox);

	//----------------------------------------------------------------------------------
	/// [機能] オブジェクトが衝突したか調べ衝突した全てのオブジェクトのタグ名を返す
	/// [引数] 衝突を検知するオブジェクト(引数のオブジェクトが他のと当たったか調べる)
	/// [戻り値] 衝突した全てのオブジェクトのタグ名
	/// [オバーライドで変化している点] 引数のhitBoxの継承先
	//----------------------------------------------------------------------------------
	static std::vector<HitObjectInfo> GetAllHitObjectsInfo(const class SphereHitBox& hitBox);

	//----------------------------------------------------------------------------------
	/// [機能] オブジェクトが衝突したか調べ最初に衝突したオブジェクトのタグ名を返す
	/// [引数] 衝突を検知するオブジェクト(引数のオブジェクトが他のと当たったか調べる)
	/// [戻り値] 最初に衝突したオブジェクトのタグ名
	/// [オーバーライドで変化している点] 引数のhitBoxの継承先
	//----------------------------------------------------------------------------------
	static HitObjectInfo GetHitObjectInfo(const class SphereHitBox& hitBox);
	/*後で引数がSphere以外の衝突検知関数を作るべき*/


private:
	static std::vector<class HitBox*> mHitBoxs;  // ゲームにある全ての当たり判定

	// シングルトンなので色々封印
	Collision() = delete;
	~Collision() = delete;
	Collision(const Collision&) = delete;
};
