#include"Scene.h"

Scene::Scene() {

}

Scene::~Scene() {

}
//--------------------------------------------
//   シーンを開始します
//--------------------------------------------
void Scene::Run() {
	ProcessInput();
	Update();
	Draw();
}