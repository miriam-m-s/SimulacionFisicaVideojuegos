#include "SpringForceGenerator.h"
#include <iostream>

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other,double min_lenght_)
{
	_k = k;
	_resting_length = resting_length;
	_other = other;
	min_lenght = min_lenght_;
}

void SpringForceGenerator::updateForce(Particle* particle, double t)
{
	Vector3 forceDistance = _other->getpos() - particle->getpos();
	const float length = forceDistance.normalize();

	float minDistance = particle->getradius() + _other->getradius();

	const float delta_x = length - _resting_length;
	forceDistance *= delta_x * _k;
	
	if (length <= minDistance) {
		std::cout << "Colisiona" << std::endl;
		_other->addForce(-forceDistance);
	}

	//if (force.magnitude()) {
	//	s *= -1;
	//}

	else if (!goma || length > _resting_length) {
		particle->addForce(forceDistance);
	}



}
