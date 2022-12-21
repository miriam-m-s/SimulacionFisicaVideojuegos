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
#include"../Muelles/SpringForceGenerator.h"
#include"../Muelles/AnchoredSpringFG.h"
#include "../Force/BuoyancyForceGenerator.h"
enum TipoParticles {
	Fuego, Cascada, Explosion,Purpurina,Polvo,Poder,Portal,Esphere,Sangre,Vient
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
	void generatemuelle(int ejs);
	void putGravity();
	void incrementK(double s);
	void createParticles(Vector3 pos,TipoParticles part);
	void createFirWorksExplosion(Vector3 pos);

protected:
	std::list<Particle*>particles;
	std::list<ParticleGenerator*>particle_generators;
	Vector3 max_pos;
	Vector3 min_pos;
	std::vector<Firework*>_fireworks_pool;
	ParticleGenerator* _firework_gen;
	ParticleForceRegistry* forceregistry;
	list<SpringForceGenerator*>fuerzasMuelles;
	list<ForceGenerator*>forces;
	bool loop_ = true;
	bool hey = true;
};


class TypeParticles {
public:
	TypeParticles(TipoParticles par);
	TypeParticles(TipoParticles par,Vector3 pos);
	ParticleGenerator* getparticles();
	bool isLoop() {
		return repeat;
	}
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
	bool repeat = true;
};
