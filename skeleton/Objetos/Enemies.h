#pragma once
#include "Particle.h"
class Enemies:public Particle
{
	public:
		Enemies(Vector3 pos);
		void integrate(double t);
		void colision(Particle* s);

private:
	int vidas = 3;

};

