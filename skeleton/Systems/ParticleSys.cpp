#include "ParticleSys.h"

ParticleSys::ParticleSys()
{
	auto Gauss = new GausseanParticleGen({ 3,50,3 }, { 0,0,0 }, { 3,8,3 }, { 10,10,10 }, 0.8, 1000);
	particles=Gauss->generateParticles();
	particle_generators.push_back(Gauss);
}

ParticleSys::~ParticleSys()
{

}

void ParticleSys::update(double t)
{
	
	for (std::list<Particle*>::iterator il = particles.begin(); il != particles.end(); ) {
		auto particle = *il;
		if (particle->active()) {
			particle->integrate(t);
			++il;
		}
		else {
			auto l = particle;
			delete l;
			l = nullptr;
			il = particles.erase(il);

		}
	}
}
