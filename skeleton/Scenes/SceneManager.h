#pragma once
#include"Scene.h"
#include <vector>
#include <PxPhysicsAPI.h>
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "SceneShoot.h"
using namespace physx;
class SceneManager
{
public:
	SceneManager(PxScene* gScene, PxPhysics* gPhysics);
	~SceneManager();
	void update(double t);
	void changeScene(int i);
	int getScene(int id);
	void InputHandler(unsigned char key);
	void handleCollision(PxActor* actor1, PxActor* actor2);
protected:
	PxScene* gScene_;
	PxPhysics* gPhysics_;
	std::vector<Scene*>escenas;
	int id = 0;

};

