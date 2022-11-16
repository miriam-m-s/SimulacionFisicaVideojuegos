#pragma once
#include "../Objetos/Particle.h"
#include "../Objetos/Firework.h"
#include<list>
#include <vector>
#include "ParticleGenerator.h"
#include"../Force/ForceGenarator.h"
#include"../Force/GravityForceGenerator.h"
#include "../Force/ParticleForceRegistry.h"
#include "../Force/ParticleDragGenerator.h"
#include"../Force/ExplosionGenerator.h"
enum TipoParticles {
	Fuego, Cascada, Explosion,Purpurina,Polvo,Poder,Portal,Esphere
};
class ParticleSys
{
public:
	ParticleSys();
	~ParticleSys();
	void update(double t);
	void deletecurrentgenerators();
	void creategenerator(TipoParticles s);
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
	ParticleForceRegistry* forceregistry;
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
	CircleGenerator* circle = nullptr;
	SphereGenerator* sphere = nullptr;
	TipoParticles partenum;

	GravityForceGenerator* forcegen=nullptr;
	WindGenerator* windgen=nullptr;
	Torbellino* torbe = nullptr;
	ExplosionGenerator* explosion = nullptr;

};
