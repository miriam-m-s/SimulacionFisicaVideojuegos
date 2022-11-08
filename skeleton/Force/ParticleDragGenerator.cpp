#include "ParticleDragGenerator.h"
#include <iostream>

ParticleDragGenerator::ParticleDragGenerator()
{
}

ParticleDragGenerator::ParticleDragGenerator(const float k1, const float k2):k1_(k1),k2_(k2)
{
}

void ParticleDragGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->inv_mass()) < 1e-10) {
		return;
	}
	Vector3 v = particle->getvel();
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = k1_ * drag_coef + k2_ * drag_coef * drag_coef;
	dragF = -v * drag_coef;
	std::cout << dragF.x << "\t" << dragF.y << "\t" << dragF.z << std::endl;
	particle->addForce(dragF);
}
