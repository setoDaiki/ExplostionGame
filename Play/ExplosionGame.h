#pragma once
#include "Scene.h"
#include <vector>

class ExplosionGame : public Scene {
public:
	ExplosionGame();
	~ExplosionGame();

private:
	void ProcessInput();   // 入力処理
	void Update();         // 全体の更新
	void Draw();           // シーンの描画

	void CreateRobot();    // ロボットの生成
	void CreateFloor();    // 床の生成
	void CreateWalls();    // 壁の生成

	class ObjectResource* mMeshResource;
	class ObjectResource* mPlayerResource;
	class ObjectResource* m2DResource;
	
	class Camera* mCamera;
	std::vector<class GameObject*> mObjects;

	const int NumRobots = 10;
	const int NumWalls = 3;
};
