#include "ParticleRigid.h"

ParticleRigid::ParticleRigid(PxRigidActor* part, RenderItem* render) :part_(part),render_(render)
{
}

void ParticleRigid::settimeVida(double time)
{
	 lifeTime=time;
	 InfiniteLife = false;

}

void ParticleRigid::setInfiniteVida(bool infinite)
{
	InfiniteLife = infinite;
}

double ParticleRigid::getTimeVida()
{
	return lifeTime;
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
