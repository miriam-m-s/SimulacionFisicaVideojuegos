#pragma once
#include "SpringForceGenerator.h"
class AnchoredSpringFG: public SpringForceGenerator
{
	public:
		AnchoredSpringFG(double k, double resting, const Vector3& anchorpos);
		~AnchoredSpringFG();
		void updateForce(Particle* particle, double t);
	bool s = true;
};
