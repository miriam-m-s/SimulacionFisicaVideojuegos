#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float a, float heigh, float l, float d):_height(h),_liquid_density(d)
{
	
	_liquid_particle = new Particle({ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, 0.99, 100, 5, {0,0.9,1,1 }, true, a, l, heigh);
	_volume = a * l* heigh;
	_liquid_particle->setInfiniteVida(true);
}

void BuoyancyForceGenerator::updateForce(Particle* particle, double duration)
{
	float h = particle->getpos().y;
	float h0 = _liquid_particle->getpos().y;
	Vector3 f(0, 0, 0);
	float immersed = 0.0;
	if (h - h0 > _height * 0.5) {
		immersed = 0.0;
	}
	else if (h0 - h > _height * 0.5) {
		immersed = 1.0;
	}
	else{
		immersed = (h0 - h) / _height + 0.5;
	}
	f.y = _liquid_density * _volume * immersed ;
	particle->addForce(f);
}
