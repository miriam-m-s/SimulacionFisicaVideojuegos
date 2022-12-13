#pragma once
#include"../Objetos/Particle.h"
#include"../WorldManager/ParticleRigid.h"
#include<list>
#include<random>
class ForceGenerator {
public:
	ForceGenerator(){};
	virtual void updateForce(Particle* particle, double duration) {
	}
	virtual void updateForce(ParticleRigid* particle, double duration) {
	}
	std::string _name;
	double t = -1e-10;
};