#pragma once
#include "../Systems/ParticleGenerator.h"
#include <memory>
#include "Particle.h"
using namespace std;

class Firework:public Particle
{
public:
	Firework(Vector3 Pos, Vector3 Vel, Vector3 acel, float dampin, float radius, float masa, double timevida, Vector4 coloring,bool active);
	int update(double t);
	 Firework* clone() {
		Firework* s= new Firework(pose.p, vel, acel_, damp_, radius, masa_, livetime_, color,true);
		setpartclegenerators(*s->getGen());
		return s;
	}
	list<Particle*>explode();
	void addgenerator(shared_ptr<ParticleGenerator> partgen);
	void setgenerators(list<shared_ptr<ParticleGenerator>>gen) {
		_gens = gen;
	};
	list<shared_ptr<ParticleGenerator>>getGenerators() {
		return _gens;
	}
	list<shared_ptr<ParticleGenerator>>* getGen() {
		return &_gens;
	}
	void setpartclegenerators(list<shared_ptr<ParticleGenerator>>& partgen) {
		partgen = _gens;
	}
	
private:
	std::list<shared_ptr<ParticleGenerator>>_gens;
};

