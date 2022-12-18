#pragma once
#include "../WorldManager/ParticleRigid.h"
class Player:public ParticleRigid
{
public:
	Player(PxScene* gScene, PxPhysics* gPhysics, int vidas);
	virtual void onCollision(PhsiscsPart* name1);
	bool getSuelo() {
		return suelo;
	}
	virtual void integrate(double t);
protected:
	int vidas_;
	bool suelo = false;
};

