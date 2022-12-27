#include "AnchoredSpringFG.h"
#include <iostream>


AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const Vector3& anchorpos):SpringForceGenerator(k, resting, nullptr)
{
	_other = new Particle(anchorpos, { 0,0,0 }, { 0, 0,0 }, 0.85,0.4,1e6, 1000, { 0,0,0,0 }, true,FormaParticle(BOX));
	/*_other=new Particle()*/
}

AnchoredSpringFG::~AnchoredSpringFG()
{
	delete _other;
}

void AnchoredSpringFG::updateForce(Particle* particle, double t)
{
	Vector3 forceDistance = _other->getpos() - particle->getpos();
	const float length = forceDistance.normalize();

	float minDistance = particle->getradius() + _other->getradius();

	const float delta_x = length - _resting_length;
	forceDistance *= delta_x * _k;

	//if (length <= minDistance && s) {
	//	s = false;
	//	std::cout << "ColisionAAa" << std::endl;
	//	particle->addForce({0,0,0});
	//}

	//if (force.magnitude()) {
	//	s *= -1;
	//}

    if (!goma || length > _resting_length) {
		particle->addForce(forceDistance);
	}
}

void AnchoredSpringFG::updateForce(ParticleRigid* particle, double t)
{
	Vector3 forceDistance = _other->getpos() - particle->getRigid()->getGlobalPose().p;
	const float length = forceDistance.normalize();

	const float delta_x = length - _resting_length;
	forceDistance *= delta_x * _k;

	if ( length > _resting_length) {
		particle->getRigid()->addForce(forceDistance);
	}
}
