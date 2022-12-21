#pragma once
#include "../WorldManager/ParticleRigid.h"
#include"../Systems/ParticleSys.h"
#include "../Objetos/Particle.h"
#include "../Objetos/Proyectil.h"
#include"../WorldManager/WorldManager.h"

class TNT :public ParticleRigidStatic
{
public:
	TNT(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, ParticleSys* partSys);
	virtual ~TNT();
	
	virtual void onCollision(PhsiscsPart* name1);
	virtual void integrate(double t);

protected:
	int vidas;
	double changecolor;
	ParticleSys* partSys_;
	Particle* cuerda;
	
	


};

