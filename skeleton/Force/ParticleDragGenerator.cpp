#include "ParticleDragGenerator.h"
#include <iostream>

ParticleDragGenerator::ParticleDragGenerator()
{
}

ParticleDragGenerator::ParticleDragGenerator(const float k1, const float k2) :k1_(k1), k2_(k2)
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

	particle->addForce(dragF);
}

WindGenerator::WindGenerator()
{
}

WindGenerator::WindGenerator(const float k1, Vector3 velwind) :ParticleDragGenerator(k1, 0), velwind_(velwind)
{
}

void WindGenerator::updateForce(Particle* particle, double t)
{

	if (fabs(particle->inv_mass()) < 1e-10) {
		return;
	}
	Vector3 v = particle->getvel()- velwind_;
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = k1_ * drag_coef + k2_ * drag_coef * drag_coef;
	dragF = -v * drag_coef;
	Vector3 cuadrado;
	for (int i = 0; i < 3; i++) {
		cuadrado[i] = velwind_[i] * velwind_[i];
	}
	double areaSphere = 4 * pi * particle->getradius() * particle->getradius();
	Vector3 force = areaSphere * coefAerodin * airDensity * (velwind_);
	Vector3 force1 = k2_ * cuadrado;
	particle->addForce(dragF);
}

Torbellino::Torbellino()
{
}

Torbellino::Torbellino(const float k1, Vector3 postorbelino, int K_) :WindGenerator(k1, { 0,0,0 }), postorbeline_(postorbelino), K(K_)
{
}

void Torbellino::updateForce(Particle* particle, double t)
{


	if (fabs(particle->inv_mass()) < 1e-10) {
		return;
	}
	velwind_ = K * Vector3(-(particle->getpos().z - postorbeline_.z), 50 - (particle->getpos().y - postorbeline_.y), particle->getpos().x - postorbeline_.x);
	Vector3 v =  particle->getvel()- velwind_;
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = k1_ * drag_coef + k2_ * drag_coef * drag_coef;
	dragF = -v * drag_coef;

	particle->addForce(dragF);

}
