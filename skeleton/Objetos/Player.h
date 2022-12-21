#pragma once
#include "../WorldManager/ParticleRigid.h"
#include "../Interfaz/Interfaz.h"
class Player:public ParticleRigid
{
public:
	Player(PxScene* gScene, PxPhysics* gPhysics, int vidas,Interfaz* inter_);
	virtual void onCollision(PhsiscsPart* name1);
	bool getSuelo() {
		return suelo;
	}
	int getVidas() {
		return vidas_;
	}
	void resetVidas() {
		vidas_ = 3;
	}
	virtual void integrate(double t);
protected:
	int vidas_;
	bool suelo = false;
	Interfaz* inter;
};

