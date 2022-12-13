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
	virtual void updateForce(ParticleRigid* particle, double t);
	protected:
	Vector3 velwind_;
	const double pi = 3.142857;
	const double airDensity = 1.2;
	const double coefAerodin = 0.5;
};

class Torbellino :public WindGenerator
{
public:
	Torbellino();
	Torbellino(const float k1, Vector3 veltorbelino,int K);
	virtual void updateForce(Particle* particle, double t);
protected:
	Vector3 postorbeline_;
	int K;

};

