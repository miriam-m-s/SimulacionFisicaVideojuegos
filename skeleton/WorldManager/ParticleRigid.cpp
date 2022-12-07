#include "ParticleRigid.h"


ParticleRigid::ParticleRigid(PxRigidActor* part, RenderItem* render) :part_(part),render_(render)
{
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
		name1->alive=false;
	}
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
