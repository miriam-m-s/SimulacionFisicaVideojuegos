#pragma once
#include"../Force/ForceGenarator.h"
#include"../core.hpp"
class SpringForceGenerator:public ForceGenerator
{
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);
	virtual void updateForce(Particle* particle);
	inline void setK(double k) {

	}
protected:
	double _k;
	double _resting_length;
	Particle* _other;
};

