#include "TestCamera.h"
#include "MyMath.h"
#include "KeyInput.h"
#include <iostream>

TestCamera::TestCamera(const DirectX::XMFLOAT3& cameraPos, const DirectX::XMFLOAT3& lookPos)
	:mPosition(cameraPos)
	,mLookPos(lookPos)
	,mRotationY(90.0f)
{

}

//-------------------------------------------
//  カメラの更新
//-------------------------------------------
void TestCamera::Update() {
	if (KeyInput::GetKeyState(DIK_W) == EHold) {
		mPosition.z += 5.0f;
	}
	if (KeyInput::GetKeyState(DIK_S) == EHold) {
		mPosition.z -= 5.0f;
	}
	if (KeyInput::GetKeyState(DIK_A) == EHold) {
		mPosition.x += 5.0f;
	}
	if (KeyInput::GetKeyState(DIK_D) == EHold) {
		mPosition.x -= 5.0f;
	}
	if (KeyInput::GetKeyState(DIK_Q) == EHold) {
		mRotationY -= 5.0f;
	}
	if (KeyInput::GetKeyState(DIK_E) == EHold) {
		mRotationY += 5.0f;
	}
	if (KeyInput::GetKeyState(DIK_UP) == EHold) {
		mPosition.y += 5.0f;
	}
	if (KeyInput::GetKeyState(DIK_DOWN) ==EHold) {
		mPosition.y -= 5.0f;
	}
	std::cout << "\nx" << mPosition.x << "\ny" << mPosition.y << "\nz" << mPosition.z;
	UpdateLookPos();
}


//---------------------------------------
//  カメラの注視位置を更新します
//---------------------------------------
void TestCamera::UpdateLookPos() {

	
	const XMFLOAT3 frontVector = Math::GetFront(mRotationY);
	XMFLOAT3 lookPos(mPosition.x + frontVector.x,
					 mPosition.y + frontVector.y -5.0f,
					 mPosition.z + frontVector.z +5.0f);
	mLookPos = lookPos;
	
}