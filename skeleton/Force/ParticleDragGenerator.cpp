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
	double areaSphere = 4 * pi * particle->getradius() * particle->getradius();
	k2_= areaSphere * coefAerodin * airDensity ;
	Vector3 v = particle->getvel()- velwind_;
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = k1_ * drag_coef + k2_ * drag_coef * drag_coef;
	dragF = -v * drag_coef;
	Vector3 cuadrado;
	particle->addForce(dragF);
}

void WindGenerator::updateForce(ParticleRigid* particle, double t)
{
	if (particle == nullptr&& particle->getRigid() == nullptr) {
		return;
	}
	if (fabs(particle->getRigid()->getInvMass()) < 1e-10) {
		return;
	}
	auto type = particle->getRenderItem()->shape->getGeometryType();

	double area;
	switch (type)
	{
	case physx::PxGeometryType::eSPHERE: 
	{
		physx::PxSphereGeometry bola;
		particle->getRenderItem()->shape->getSphereGeometry(bola);
		area = 4 * pi * bola.radius * bola.radius;
	}
		
		break;
	case physx::PxGeometryType::eBOX:
	{
		physx::PxBoxGeometry caja;
		particle->getRenderItem()->shape->getBoxGeometry(caja);
		physx::PxVec3 lados = caja.halfExtents;
		auto area1 =  lados[0] *  lados[1] * 2;
		auto area2 = lados[0] *  lados[2]  * 2;
		auto area3 = lados[1]  * lados[2]  * 2;
		area = (area1 + area2 + area3)/100;
	}
		
		break;
	}
	Vector3 v = particle->getRigid()->getLinearVelocity() - velwind_;
	k2_ = area * coefAerodin * airDensity;
	float drag_coef = v.normalize();
	PxVec3 dragF;
	drag_coef = k1_ * drag_coef + k2_ * drag_coef * drag_coef;
	dragF = -v * drag_coef;
	particle->getRigid()->addForce({dragF.x,dragF.y,dragF.z}, PxForceMode::eACCELERATION);
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
