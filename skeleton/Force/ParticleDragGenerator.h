#pragma once
#include "ForceGenarator.h"
#include "../core.hpp"
class ParticleDragGenerator:public ForceGenerator
{
public:
	ParticleDragGenerator();
	ParticleDragGenerator(const float k1, const float k2);
	virtual void updateForce(Particle* particle, double t);
	inline void setDrag(float k1, float k2) {
		k1_ = k1;
		k2_ = k2;
	}
	inline float getK1() {
		return k1_;
	}
	inline float getK2() {
		return k2_;
	}
protected:
	float k1_;//drags
	float k2_;
};

class WindGenerator:public ParticleDragGenerator
{
public:
	WindGenerator();
	WindGenerator(const float k1,Vector3 velwind);
	virtual void updateForce(Particle* particle, double t);
	protected:
	Vector3 velwind_;

};

//class WindGenerator :public ParticleDragGenerator
//{
//public:
//	WindGenerator();
//	WindGenerator(const float k1, Vector3 velwind);
//	virtual void updateForce(Particle* particle, double t);
//protected:
//	Vector3 velwind_;
//
//};

