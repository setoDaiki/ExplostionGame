#include "Sequence.h"
#include "Scene.h"
#include "ExplosionGame.h"

Sequence::Sequence() 
	:mScene(nullptr)
	,mSceneType(EGame)
{
	mScene = new ExplosionGame();
}

Sequence::~Sequence() {
	delete mScene;
	mScene = 0;
}

//--------------------------------------------
//   シーンに応じた更新処理を呼び出します
//--------------------------------------------
void Sequence::RunScene() {
	mScene->Run();
}


//--------------------------------------------
//   シーンを変更します
//--------------------------------------------
void Sequence::ChangeScene(SceneType sceneType) {
	mSceneType = sceneType;
}