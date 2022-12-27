#pragma once
#include "../WorldManager/ParticleRigid.h"
#include "../Systems/ParticleSys.h"
class Enemy2:public ParticleRigid
{
	int vidas_;
	ParticleSys* partSys_;
	ParticleRigid* player_;
	float force;
	double changecolor;

	public:
		Enemy2(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, ParticleSys* partSys, int vidas);
		virtual void integrate(double t)override;
		void getPLayer(ParticleRigid* part);
		virtual void onCollision(PhsiscsPart* name1);
};

