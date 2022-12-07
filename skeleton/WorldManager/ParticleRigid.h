#pragma once
#include <PxPhysicsAPI.h>
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include <string>
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
	void setName(std::string s);
	std::string getName() {
		return name;
	}
	void setInfiniteVida(bool infinite);
	double getTimeVida();
	virtual void onCollision(ParticleRigid* name1);
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
	std::string name = " ";
};

