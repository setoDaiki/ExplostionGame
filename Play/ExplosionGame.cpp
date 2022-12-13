#include "ExplosionGame.h"
#include "KeyInput.h"
#include "Object2DResource.h"
#include "MeshResource.h"
#include "Robot.h"
#include "StaticCamera.h"
#include "TestCamera.h"
#include "SphereHitBox.h"
#include "Player.h"
#include <iostream>

ExplosionGame::ExplosionGame() {
	CreateRobot();     // ロボット生成
	CreateFloor();     // 床生成
	CreateWalls();     // 壁生成
	mCamera = new StaticCamera(DirectX::XMFLOAT3(0.0,75.0f,-85.0f),DirectX::XMFLOAT3(0.0f,70.0f,-79.0f));  // カメラ生成
	mPlayerResource = new MeshResource(L"Asset/boy.fbx");  // プレイヤーのリソース
	GameObject* player = new Player(mPlayerResource,DirectX::XMFLOAT3(0.0f,9.0f,0.0f));  // プレイヤー生成
	mObjects.emplace_back(player);
	
}

ExplosionGame::~ExplosionGame() {
	mObjects.clear();
	mObjects.shrink_to_fit();
	delete m2DResource;
	m2DResource = 0;
	delete mPlayerResource;
	mPlayerResource = 0;
	delete mCamera;
	mCamera = 0;
}

//---------------------------------------------------
//   入力処理
//---------------------------------------------------
void ExplosionGame::ProcessInput() {
	KeyInput::UpdateCurrentKey();
}

//---------------------------------------------------
//　　シーンの更新
//---------------------------------------------------
void ExplosionGame::Update() {
	mCamera->Update();

	for (auto obj : mObjects) {
		obj->Update();
	}
	std::erase_if(mObjects, [](GameObject* object) {return object->NeedErase() == true; });  // 消していいオブジェクトは除外しちゃう


}

//---------------------------------------------------
//   シーンの描画
//---------------------------------------------------
void ExplosionGame::Draw() {
	Engine::Instance()->BeginRender();
	for (auto obj : mObjects) {
		obj->Draw(*mCamera);
	}
	Engine::Instance()->EndRender();
}

//----------------------------------------------------
//   ロボットの生成
//----------------------------------------------------
void ExplosionGame::CreateRobot() {
	mMeshResource = new MeshResource(L"Asset/robot/robot_lowpoly@animations.fbx");  // ロボットのリソース生成
	DirectX::XMFLOAT3 robotPos(-30.0f, 9.0f, -40.0f);                               // ロボット位置
	for (int i = 0; i < NumRobots; i++) {											// ロボットの数分繰り返す
		if (robotPos.x > 29.0f) {
			robotPos.x = -30.0f;
			robotPos.z += 70.0f;
		}
		robotPos.x += 10.0f;
		GameObject* robot = new Robot(mMeshResource, robotPos);			            // 全てのロボット生成
		mObjects.emplace_back(robot);
	}
}

//--------------------------------------------------
//   床の生成
//--------------------------------------------------
void ExplosionGame::CreateFloor() {
	m2DResource = new Object2DResource(L"Asset/Floor.png");				                // 壁と床のリソース生成
	DirectX::XMFLOAT3 floorPos(0.0f, 10.0f, 0.0f);						                // 床の位置
	DirectX::XMFLOAT3 floorRot(90.0f, 0.0f, 0.0f);						           	    // 床の回転
	DirectX::XMFLOAT3 floorScale(5.0f, 5.0f, 5.0f);							            // 床の拡大率
	GameObject* floor = new GameObject(m2DResource, floorPos, floorRot, floorScale);    // 床生成
	mObjects.emplace_back(floor);

}

//------------------------------------------------------
//     壁の生成
//------------------------------------------------------
void ExplosionGame::CreateWalls() {
	DirectX::XMFLOAT3 wallsScale(5.0f, 5.0f, 5.0f);                                                  // 全ての壁共通の壁拡大率設定

	DirectX::XMFLOAT3 rightWallPos(50.0f, 10.0f, 0.0f);                                              // 右の壁位置
	DirectX::XMFLOAT3 rightWallRot(0.0f, -90.0f, 0.0f);									             // 右の壁回転
	GameObject* rightWall = new GameObject(m2DResource, rightWallPos, rightWallRot, wallsScale);     // 右の壁生成
	mObjects.emplace_back(rightWall);																 // オブジェクト軍に追加

	DirectX::XMFLOAT3 leftWallPos(-50.0f, 10.0f, 0.0f);							            		 // 左の壁位置
	DirectX::XMFLOAT3 leftWallRot(0.0f, 90.0f, 0.0f);								                 // 左の壁回転
	GameObject* leftWall = new GameObject(m2DResource, leftWallPos, leftWallRot, wallsScale);        // 左の壁生成
	mObjects.emplace_back(leftWall);																 // オブジェクト軍に追加

	DirectX::XMFLOAT3 backWallPos(0.0f, 10.0f, 50.0f);									             // 後ろの壁位置
	DirectX::XMFLOAT3 backWallRot(0.0f, 0.0f, 0.0f);									             // 後ろの壁回転
	GameObject* backWall = new GameObject(m2DResource, backWallPos, backWallRot, wallsScale);        // 後ろの壁生成
	mObjects.emplace_back(backWall);																 // オブジェクト軍に追加
}