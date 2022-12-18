#pragma once
#include "../WorldManager/ParticleRigid.h"
#include"../Systems/ParticleSys.h"

class Enemy:public ParticleRigid
{
public:
	Enemy(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, ParticleSys* partSys, int vidas);
	void GetPlayer(ParticleRigid* player);
	virtual void onCollision(PhsiscsPart* name1);
	virtual void integrate(double t);
	
protected:
	int vidas;
	double changecolor;
	ParticleRigid* player_;
	ParticleSys* partSys_;
	double timechangecolor = 1.0;
};

