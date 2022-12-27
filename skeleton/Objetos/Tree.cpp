#include "Tree.h"

Trees::Trees(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, ParticleSys* partsys, Vector4 Color,WorldManager* wold):ParticleRigidStatic(gScene, gPhysics, pos, CreateShape(physx::PxBoxGeometry(4,19,4)), {0.1,0.2,0,1}), partsys(partsys)
{
	partsys->createtrees(pos + Vector3(0, 30, 0), Color,TipoParticles::Tree);
	x = std::normal_distribution<>{ pos.x,10 };
	y = std::normal_distribution<>{ pos.y+5,1 };
	z = std::normal_distribution<>{ pos.z,10 };
	for (int i = 0; i < 10; i++) {
		Vector3 pos= Vector3(x(gen), y(gen), z(gen));
		wold->createmuelle(pos, { 1,0.7,0.5,1 });
	}
	
	

}
