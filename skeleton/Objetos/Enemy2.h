#pragma once
#include "../WorldManager/ParticleRigid.h"
#include "../Systems/ParticleSys.h"
class Enemy2:ParticleRigid
{
	int vidas_;
	ParticleSys* partSys_;
	public:
		Enemy2(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, ParticleSys* partSys, int vidas);
		virtual void integrate(double t)override;
};

