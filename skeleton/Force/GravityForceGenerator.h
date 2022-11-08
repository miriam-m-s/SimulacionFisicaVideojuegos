#pragma once
#include "ForceGenarator.h"
#include "../core.hpp"
class GravityForceGenerator:public ForceGenerator
{
	public:
		GravityForceGenerator(const Vector3& g);
		virtual void updateForce(Particle* particle, double t);
		inline void setGravity(Vector3 g) {
			gravity_ = g;
		}
private:
	Vector3 gravity_;
};

