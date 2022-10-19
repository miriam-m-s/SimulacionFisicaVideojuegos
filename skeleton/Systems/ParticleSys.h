#pragma once
#include "../Objetos/Particle.h"
#include<list>
#include "ParticleGenerator.h"
enum TipoParticles {
	Fuego, Cascada, Explosion,Purpurina
};
class ParticleSys
{
public:
	ParticleSys();
	~ParticleSys();
	void update(double t);
	ParticleGenerator* getPartcleGenerator(std::string name);
protected:
	std::list<Particle*>particles;
	std::list<ParticleGenerator*>particle_generators;
	Vector3 max_pos;
	Vector3 min_pos;
};
class TypeParticles {
public:
	TypeParticles(TipoParticles par);
	ParticleGenerator* getparticles();
	~TypeParticles() {
		/*if (partgaus != nullptr) {
			delete partgaus;
		}
		else if (unigen != nullptr) {
			delete unigen;
		}*/
	};

private:
	GausseanParticleGen* partgaus=nullptr;
	UniformParticleGenerator* unigen = nullptr;
	TipoParticles partenum;
};
