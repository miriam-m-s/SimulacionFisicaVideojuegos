#pragma once
#include <PxPhysicsAPI.h>
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include <list>
#include<vector>
#include<string>
#include"ParticleRigid.h"
//
using namespace physx;

class WorldManager
{
public:
	WorldManager(PxScene* gScene, PxPhysics* gPhysics);
	
	~WorldManager();
	void createRigidStatic(Vector3 pos, Vector3 size, Vector4 color, std::string name =" ", double time = 0);
	void createRigidDynamic(Vector3 pos, Vector3 size, Vector3 vel, Vector4 color, std::string name = " ", double time=0);
	void integrate(double t);
	void handleCollision(PxActor* actor1, PxActor* actor2);

protected:
	PxScene* gScene_;
	PxPhysics* gPhysics_;
	std::list<ParticleRigid*>Objects;
	
};

