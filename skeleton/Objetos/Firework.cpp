#include "Firework.h"

Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 acel, float dampin, float radius, float masa, double timevida, Vector4 coloring,bool visible) :Particle(Pos, Vel, acel, dampin, radius, masa, timevida, coloring,visible)
{
	
}

int Firework::update(double t)
{
	livetime_--;
	if (livetime_ <= 0) {
		alive = false;
		
	}
	return 0;
}



list<Particle*> Firework::explode()
{
	list<Particle*>aux;
	for (auto g :  _gens) {
		g->setPos(pose.p);
		g->setRadius(radius / 2);
		list<Particle*>lis=g->generateParticles();
		for (auto ini = lis.begin(); ini != lis.end(); ++ini) {
			aux.push_back(*ini);
		}
	}
	return aux;
}

void Firework::addgenerator(shared_ptr<ParticleGenerator> partgen)
{
	_gens.push_back(partgen);
}


