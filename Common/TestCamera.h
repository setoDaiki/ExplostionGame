#pragma once
#include "Camera.h"

class TestCamera :public Camera {
public:
	TestCamera(const DirectX::XMFLOAT3& cameraPos,const DirectX::XMFLOAT3& lookPos);
	~TestCamera()override {};

	//-------------------------------------
	/// [機能]カメラの状態の更新
	//-------------------------------------
	void Update()override;
	

	//-----------------------------------------
	/// [機能] カメラの位置を取得します
	/// [返り値] カメラの位置です
	//-----------------------------------------
	DirectX::XMFLOAT3 GetPosition()const override { return mPosition; };


	//-----------------------------------------
	/// [機能] 注視位置を取得します
	/// [返り値] 注視位置です
	//-----------------------------------------
	DirectX::XMFLOAT3 GetLookPos()const override { return mLookPos; };

private:
	void UpdateLookPos();

	DirectX::XMFLOAT3 mLookPos;
	DirectX::XMFLOAT3 mPosition;
	float mRotationY;
};
