#include "Tree.h"

Trees::Trees(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, ParticleSys* partsys, Vector4 Color):ParticleRigidStatic(gScene, gPhysics, pos, CreateShape(physx::PxBoxGeometry(4,19,4)), {0.1,0.2,0,1}), partsys(partsys)
{
	partsys->createtrees(pos + Vector3(0, 30, 0), Color,TipoParticles::Tree);
}
