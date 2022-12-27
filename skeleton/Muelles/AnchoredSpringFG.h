#pragma once
#include "SpringForceGenerator.h"
#include"../WorldManager/ParticleRigid.h"
class AnchoredSpringFG: public SpringForceGenerator
{
	public:
		AnchoredSpringFG(double k, double resting, const Vector3& anchorpos);
		virtual ~AnchoredSpringFG()override;
		void updateForce(Particle* particle, double t);
		void updateForce(ParticleRigid* particle, double t);
		void setmaxLenght(double ss) {
			maxlenght = s;
		}
private:
	double maxlenght = 12;
	bool s = true;
};
