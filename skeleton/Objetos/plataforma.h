#pragma once
#include "../WorldManager/ParticleRigid.h"
#include"../WorldManager/WorldManager.h"
#include"../Systems/ParticleSys.h"
class plataforma :public ParticleRigidStatic
{
public:
	plataforma(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, Vector4 color,WorldManager*wold,ParticleSys*part);
	virtual void onCollision(PhsiscsPart* name1);
protected:
	WorldManager* wold_;
	ParticleSys* part;
	bool tocada = false;
};

