#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g)
{
	
}

void GravityForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->inv_mass()) < 1e-10) {
		return;
	}
	particle->addForce(gravity_ * particle->inv_mass());
}
