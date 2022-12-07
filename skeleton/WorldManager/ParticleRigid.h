#pragma once
#include <PxPhysicsAPI.h>
#include "../core.hpp"
#include "../RenderUtils.hpp"
using namespace physx;
class ParticleRigid
{
public :
	ParticleRigid(PxRigidActor* part, RenderItem* render_);
	~ParticleRigid() {
		DeregisterRenderItem(render_);
		delete render_;

	}
	void settimeVida(double time);
	void setInfiniteVida(bool infinite);
	double getTimeVida();
	PxRigidActor* getRigid() {
		return part_;
	}
	void integrate(double t);
	bool isAlive();
protected:
	double lifeTime=5.;
	PxRigidActor* part_;
	bool InfiniteLife = true;
	bool alive = true;
	RenderItem* render_;
};

