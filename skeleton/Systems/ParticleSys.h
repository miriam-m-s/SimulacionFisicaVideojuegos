#pragma once
#include "../Objetos/Particle.h"
#include "../Objetos/Firework.h"
#include<list>
#include <vector>
#include "ParticleGenerator.h"
enum TipoParticles {
	Fuego, Cascada, Explosion,Purpurina,Polvo,Poder,Fireworks
};
class ParticleSys
{
public:
	ParticleSys();
	~ParticleSys();
	void update(double t);
	ParticleGenerator* getPartcleGenerator(std::string name);
	void generateFireWorkSystem();
	void shootFireWork(int type);

protected:
	std::list<Particle*>particles;
	std::list<ParticleGenerator*>particle_generators;
	Vector3 max_pos;
	Vector3 min_pos;
	std::vector<Firework*>_fireworks_pool;
	ParticleGenerator* _firework_gen;
};


class TypeParticles {
public:
	TypeParticles(TipoParticles par);
	ParticleGenerator* getparticles();
	~TypeParticles() {
		
	};

private:
	GausseanParticleGen* partgaus=nullptr;
	UniformParticleGenerator* unigen = nullptr;
	TipoParticles partenum;
};
