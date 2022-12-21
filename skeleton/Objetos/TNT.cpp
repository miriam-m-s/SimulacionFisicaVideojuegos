#include "TNT.h"

#include <iostream>

TNT::TNT(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, ParticleSys* partSys) :ParticleRigidStatic(gScene, gPhysics, pos, shape, { 0.4,0.01,0.1,1 }), partSys_(partSys)
{

	setInfiniteVida(true);
	setName("TNT");

	cuerda = new Particle(pos + Vector3(0, 10, 0), { 0,0,0 }, { 0,0,0 }, 0.8, 20, 0, { 0,0,0,0 }, true, CreateShape(PxBoxGeometry(0.5,3,0.5)));

}
TNT::~TNT()
{
	delete cuerda;
	/*DeregisterRenderItem(render_);
	delete render_;*/
}



void TNT::onCollision(PhsiscsPart* name1)
{
	if (name1->getName() == "bala") {
		partSys_->createFirWorksExplosion(getRigid()->getGlobalPose().p);
		alive = false;
	}
}

void TNT::integrate(double t)
{
	

}
