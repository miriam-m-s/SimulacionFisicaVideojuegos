#pragma once
#include <PxPhysicsAPI.h>
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include <string>
using namespace physx;
class PhsiscsPart {
	public:
	PhsiscsPart();
	~PhsiscsPart() {
		DeregisterRenderItem(render_);
		delete render_;
	}
	virtual void onCollision(PhsiscsPart* name1)=0;
	virtual void integrate(double t);
	double getTimeVida();
	bool isAlive();
	void settimeVida(double time);
	void setName(std::string s);
	std::string getName() {
		return name;
	}
	virtual PxRigidActor* getRigid() = 0;
	
	void setInfiniteVida(bool infinite);
	RenderItem* getRenderItem();
protected:
	double lifeTime = 5.;
	bool InfiniteLife = true;
	bool alive = true;
	std::string name = " ";
	RenderItem* render_;

};
class ParticleRigid:public PhsiscsPart
{
public :
	ParticleRigid(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, Vector3 vel, Vector4 color, float density=2);
	virtual void onCollision(PhsiscsPart* name1);
	 PxRigidDynamic* getRigid()override {
		return part_dy;
	 }
	 void setmass(double mass); 
protected:
	PxRigidDynamic* part_dy;
	
};
class ParticleRigidStatic :public PhsiscsPart
{
	public:
	ParticleRigidStatic(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape,  Vector4 color);
	PxRigidActor* getRigid() override {
		return part_;
	}
	virtual void onCollision(PhsiscsPart* name1);
   protected:
	  PxRigidActor* part_;
   	
};

