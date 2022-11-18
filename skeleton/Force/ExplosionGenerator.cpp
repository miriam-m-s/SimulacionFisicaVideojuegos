#include "ExplosionGenerator.h"
#include <iostream>

ExplosionGenerator::ExplosionGenerator(int K, Vector3 posexplosion, float cnstexplosion, double velExpansion_):ForceGenerator(),K_(K),posexplosion_(posexplosion),cnstexplosion_(cnstexplosion),R_(0)
{

}

void ExplosionGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->inv_mass()) < 1e-10) {
		return;
	}
	
	double r=pow(particle->getpos().x-posexplosion_.x, 2)+ pow(particle->getpos().y - posexplosion_.y, 2)+ pow(particle->getpos().z - posexplosion_.z, 2);
	if (r < R_*R_) {
		Vector3 forexp = (K_ / r) * Vector3(particle->getpos().x - posexplosion_.x, particle->getpos().y - posexplosion_.y, particle->getpos().z - posexplosion_.z) * pow(e, -t / cnstexplosion_);
		particle->addForce(forexp * particle->mass());
	}


	
	R_ = velExpansion_ * t;
	cnstexplosion_ += t;
	//std::cout << "af  ";

}
