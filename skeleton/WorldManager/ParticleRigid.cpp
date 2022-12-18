#include "ParticleRigid.h"


PhsiscsPart::PhsiscsPart()
{
}

void PhsiscsPart::integrate(double t)
{
	lifeTime -= t;
	if (lifeTime <= 0 && !InfiniteLife)alive = false;

}
RenderItem* PhsiscsPart::getRenderItem()
{
	return render_;
}
double PhsiscsPart::getTimeVida()
{
	return lifeTime;
}

bool PhsiscsPart::getInfiniteVida()
{
	return InfiniteLife;
}

bool PhsiscsPart::isAlive()
{
	return alive;
}

void PhsiscsPart::settimeVida(double time)
{
	lifeTime = time;
	InfiniteLife = false;

}

void PhsiscsPart::setName(std::string s)
{
	name = s;
}

void PhsiscsPart::setInfiniteVida(bool infinite)
{
	InfiniteLife = infinite;
}



ParticleRigid::ParticleRigid(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, Vector3 vel, Vector4 color, float density)
{

	part_dy = gPhysics->createRigidDynamic(PxTransform(pos));
	part_dy->setLinearVelocity(vel);
	part_dy->setAngularVelocity({ 0,0,0 });
	part_dy->attachShape(*shape);
	PxRigidBodyExt::setMassAndUpdateInertia(*part_dy, density);
	
	gScene->addActor(*part_dy);
	render_ = new RenderItem(shape, part_dy, color);
	shape->getGeometryType();
	
}

void ParticleRigid::onCollision(PhsiscsPart* name1)
{
	//if (name1->getName() == "bala") {
	//	alive = false;
	//	//name1->alive=false;
	//}
}

void ParticleRigid::setmass(double mass)
{
	part_dy->setMass(mass);
}



ParticleRigidStatic::ParticleRigidStatic(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, Vector4 color)
{
	part_ = gPhysics->createRigidStatic(PxTransform(pos));
	part_->attachShape(*shape);
	render_ = new RenderItem(shape, part_, color);
	gScene->addActor(*part_);
}

void ParticleRigidStatic::onCollision(PhsiscsPart* name1)
{
}



