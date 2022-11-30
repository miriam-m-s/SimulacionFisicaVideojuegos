#pragma once
#include "ForceGenarator.h"
#include "../core.hpp"
class BuoyancyForceGenerator:public ForceGenerator
{
public:
	BuoyancyForceGenerator(float h,float heigh, float a,float l, float d);
	virtual void updateForce(Particle* particle, double duration);
	~BuoyancyForceGenerator(){
		delete _liquid_particle;
	};
protected:
	float _height;
	float _volume;
	float _liquid_density;
	float _gravity = 9.8;
	Particle* _liquid_particle;
};

