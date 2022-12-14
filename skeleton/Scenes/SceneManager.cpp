#include "SceneManager.h"

SceneManager::SceneManager(PxScene* gScene, PxPhysics* gPhysics):gScene_(gScene),gPhysics_(gPhysics_)
{

	escenas.push_back(new SceneShoot(gScene_, gPhysics_));
}

SceneManager::~SceneManager()
{
	for (auto s : escenas) {
		delete s;
	}
	escenas.resize(0);
}

void SceneManager::update(double t)
{
	escenas[id]->update(t);
}

void SceneManager::changeScene(int i)
{
	
	if(!(id<0||id>escenas.size())){
		id = i;
		
	}
}

int SceneManager::getScene(int id)
{
	return id;
}

void SceneManager::InputHandler(unsigned char key)
{
	escenas[id]->inputHandler(key);
}
