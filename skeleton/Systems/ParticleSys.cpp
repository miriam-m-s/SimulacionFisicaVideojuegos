#include "ParticleSys.h"

ParticleSys::ParticleSys()
{
	Camera* camera = GetCamera();
	//explosión
	//auto Gauss = new GausseanParticleGen({ 3,50,3 }, { 0,0,0 }, { 3,8,3 }, { 10,10,10 }, 0.8, 20,9);
	//cascada
	//auto Gauss=new GausseanParticleGen(Vector3(15, 40, 0), camera->getDir() * (-10),
	//	Vector3(0.1, 0.1, 10), Vector3(0.1, 0.1, 0.1), 0.8, 1, 10);
	//lluvia
;  auto Gauss = new UniformParticleGenerator({ 0,70,0 }, { 0,0,0 }, { 8,8,8 }, { 8,8,8 }, 0.8, 20, 10);
	particle_generators.push_back(Gauss);
}

ParticleSys::~ParticleSys()
{

}

void ParticleSys::update(double t)
{
	for (auto gpart : particle_generators) {
		std::list<Particle*>aux = gpart->generateParticles();
		for (auto il = aux.begin(); il != aux.end(); ++il) {
			particles.push_back(*il);
		}
	}
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
