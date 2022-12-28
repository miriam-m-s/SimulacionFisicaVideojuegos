#include "ringpelea.h"


ringpelea::ringpelea(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, Vector4 color, WorldManager* wold, ParticleSys* part) :ParticleRigidStatic(gScene, gPhysics, pos, shape, color), wold_(wold), part(part), gPhysics_(gPhysics)
{
	
}

void ringpelea::onCollision(PhsiscsPart* name1)
{
	if (name1->getName() == "player"&&h) {
		h = false;
		wold_->creaEnemy(getRigid()->getGlobalPose().p+Vector3(-10,110,-30), 3, CreateShape(physx::PxBoxGeometry(3, 3, 3)));
		wold_->creaEnemy(getRigid()->getGlobalPose().p + Vector3(20, 110, -30), 4, CreateShape(physx::PxSphereGeometry(4)));
		wold_->creaEnemy(getRigid()->getGlobalPose().p + Vector3(-30, 110, -60),2, CreateShape(physx::PxSphereGeometry(2)));
	}
}

