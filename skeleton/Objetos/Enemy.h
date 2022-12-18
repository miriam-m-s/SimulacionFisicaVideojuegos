#pragma once
#include "../WorldManager/ParticleRigid.h"
#include"../Systems/ParticleSys.h"
#include "../Objetos/Particle.h"
#include "../Objetos/Proyectil.h"
#include"../WorldManager/WorldManager.h"

class Enemy:public ParticleRigidStatic
{
public:
	Enemy(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, ParticleSys* partSys, int vidas,WorldManager* wold);
	virtual ~Enemy();
	void GetPlayer(ParticleRigid* player);
	virtual void onCollision(PhsiscsPart* name1);
	virtual void integrate(double t);
	
protected:
	int vidas;
	double changecolor;
	ParticleRigid* player_;
	ParticleSys* partSys_;
	double timechangecolor = 1.0;
	Particle* ojo1;
	Particle* ojo2;
	double timer=0;
	double time = 2;
	vector<Proyectil>balas;
	WorldManager* wold;

};

