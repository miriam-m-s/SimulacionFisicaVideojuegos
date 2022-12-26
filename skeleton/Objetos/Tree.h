#pragma once
#include "../WorldManager/ParticleRigid.h"
#include "../Systems/ParticleSys.h"
class Trees:public ParticleRigidStatic
{
public:
	Trees(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, ParticleSys* partsys,Vector4 Color);
private:
	ParticleSys* partsys;
	
};

