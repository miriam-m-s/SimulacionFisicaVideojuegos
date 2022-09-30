#pragma once
#include "../Objetos/Particle.h"
#include<list>
#include "ParticleGenerator.h"
class ParticleSys
{
public:
	ParticleSys();
	~ParticleSys();
	void update(double t);
protected:
	std::list<Particle*>particles;
	std::list<ParticleGenerator*>particle_generators;
	Vector3 max_pos;
	Vector3 min_pos;
};

