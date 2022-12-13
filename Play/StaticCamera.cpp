#include "StaticCamera.h"
#include "MyMath.h"
#include "KeyInput.h"

StaticCamera::StaticCamera(const DirectX::XMFLOAT3& cameraPos, const DirectX::XMFLOAT3& lookPos)
	:mPosition(cameraPos)
	,mLookPos(lookPos)
{

}

//-------------------------------------------
//  カメラの更新
//-------------------------------------------
void StaticCamera::Update() {
	// 動かないカメラなので更新なし
}


