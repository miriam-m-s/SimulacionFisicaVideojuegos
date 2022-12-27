#pragma once
#include <random>
#include <cmath>
#include "../WorldManager/ParticleRigid.h"
#include "../WorldManager/WorldManager.h"
#include "../Systems/ParticleSys.h"

class Trees:public ParticleRigidStatic
{
public:
	Trees(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, ParticleSys* partsys,Vector4 Color,WorldManager* wold);
private:
	ParticleSys* partsys;
	std::normal_distribution<>x;
	std::normal_distribution<>y;
	std::normal_distribution<>z;
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	
};

