#include "Enemies.h"
#include <iostream>

Enemies::Enemies(Vector3 pos): Particle(pos, { 0,0,0 }, { 0, 0,0 }, 0.8, 4, 100, 1000, { 1,0,0,1 }, true, BOX)
{
	

}

void Enemies::integrate(double t)
{
	Particle::integrate(t);
	if(vidas<=0)alive = false;
}

void Enemies::colision(Particle* s)
{
	Vector3 forceDistance = s->getpos() - getpos();
	const float length = forceDistance.normalize();

	float minDistance = radius + s->getradius();

	

	if (length <= minDistance) {
		std::cout << "Colisiona" << std::endl;
	   

		

		//s->addForce(-forceDistance);
	}
}
