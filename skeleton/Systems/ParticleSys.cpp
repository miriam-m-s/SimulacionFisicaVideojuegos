#include "ParticleSys.h"

ParticleSys::ParticleSys()
{

}

ParticleSys::~ParticleSys()
{

}

void ParticleSys::update(double t)
{
	for (std::list<Particle*>::iterator il = particles.begin(); il != particles.end(); ++il) {
		auto particle = *il;
		particle->integrate(t);
	}
}
