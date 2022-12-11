#include "ParticleRigid.h"





ParticleRigid::ParticleRigid(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, Vector3 vel, Vector4 color, float density)
{
	PxRigidDynamic* part;
	part = gPhysics->createRigidDynamic(PxTransform(pos));
	part->setLinearVelocity(vel);
	part->setAngularVelocity({ 0,0,0 });
	part->attachShape(*shape);
	PxRigidBodyExt::setMassAndUpdateInertia(*part, density);
	
	gScene->addActor(*part);
	part_ = part;
	render_ = new RenderItem(shape, part_, color);
	
}

ParticleRigid::ParticleRigid(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, Vector4 color)
{
	part_ = gPhysics->createRigidStatic(PxTransform(pos));
	part_->attachShape(*shape);
	render_ = new RenderItem(shape, part_, color);
	gScene->addActor(*part_);
}

void ParticleRigid::settimeVida(double time)
{
	 lifeTime=time;
	 InfiniteLife = false;

}

void ParticleRigid::setName(std::string s)
{
	name = s;
}

void ParticleRigid::setInfiniteVida(bool infinite)
{
	InfiniteLife = infinite;
}

double ParticleRigid::getTimeVida()
{
	return lifeTime;
}

void ParticleRigid::onCollision(ParticleRigid* name1)
{
	if (name1->getName() == "bala") {
		alive = false;
		//name1->alive=false;
	}
}

RenderItem* ParticleRigid::getRenderItem()
{
	return render_;
}

void ParticleRigid::integrate(double t)
{
	lifeTime -= t;
	if (lifeTime <= 0 && !InfiniteLife)alive = false;

}

bool ParticleRigid::isAlive()
{
	return alive;
}
