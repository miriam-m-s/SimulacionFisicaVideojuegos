#pragma once
#include"../Force/ForceGenarator.h"
#include"../core.hpp"
class SpringForceGenerator:public ForceGenerator
{
public:
	SpringForceGenerator(double k, double resting_length, Particle* other, double min_length=3);
	virtual ~SpringForceGenerator()override {

	}
	virtual void updateForce(Particle* particle, double t);
	inline void setK(double k) {
	
		_k = k;
	}
	void addK(double k) {
		_k += k;
	}
	void setGoma(bool s) {
		goma = s;
	}

protected:
	double _k;
	double _resting_length;	
	double min_lenght;
	Particle* _other;
	bool goma = false;
	int s = 1;
};

