#pragma once
#include "ForceGenarator.h"
#include<cmath>
#include <math.h>
#define E 2.71828182845904523536;
class ExplosionGenerator:public ForceGenerator
{
public:
	ExplosionGenerator() {};
	ExplosionGenerator(int K,Vector3 posexplosion,  float cnstexplosion, double velExpansion_);
	virtual void updateForce(Particle* particle, double t);
	void setvel(double velExpansion) {
		velExpansion_ = velExpansion;
	}
private:
	int K_;
	int R_;
	int e = E;
	Vector3 posexplosion_;
	 float cnstexplosion_;
	 double velExpansion_=344.4;
};

