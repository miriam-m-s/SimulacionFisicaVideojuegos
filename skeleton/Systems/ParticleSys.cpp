#include "ParticleSys.h"

ParticleSys::ParticleSys()
{
	TypeParticles tipo(TipoParticles::Fuego);
	//explosión
	//auto Gauss = new GausseanParticleGen({ 3,50,3 }, { 0,0,0 }, { 3,8,3 }, { 10,10,10 }, 0.8, 20,9);
	//cascada
	/*auto Gauss=new GausseanParticleGen(Vector3(15, 40, 0), camera->getDir() * (-10),
		Vector3(0.1, 0.1, 10), Vector3(0.1, 0.1, 0.1), 0.8, 1, 10);*/
	//lluvia
;  //auto Gauss = new UniformParticleGenerator({ 0,70,0 }, { 0,0,0 }, { 8,8,8 }, { 8,8,8 }, 0.8, 20, 10);
   /* auto Gauss = new GausseanParticleGen(Vector3(0, 20, 0),{0,0,0},*/
	/*Vector3(10, 10, 0.1), Vector3(0.1, 0.4, 0.1), 0.8, 6, 3); */
	/*Gauss->setGravity({0,10,0});*/
	particle_generators.push_back(tipo.getparticles());
}

ParticleSys::~ParticleSys()
{
	for (auto gpart : particle_generators) {
		delete gpart;
	}
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
ParticleGenerator* ParticleSys::getPartcleGenerator(std::string name)
{
	return nullptr;
}
TypeParticles::TypeParticles(TipoParticles par):partenum(par) {
	Camera* camera = GetCamera();
	switch (par)
	{
	case Fuego:
		partgaus=new GausseanParticleGen(Vector3(0, 20, 0), { 0,0,0 },
		Vector3(3, 3, 0.1), Vector3(0.3, 0.1, 0.1), 0.1, 30, 3);
		partgaus->setGravity({ 0,5,0 });
		partgaus->setColor({ 1,1,0,0.5f });
		partgaus->setRadius(0.1f);
		break;
	case Cascada:
		
		partgaus = new GausseanParticleGen(Vector3(15, 40, 0), camera->getDir() * (-10),
			Vector3(0.1, 0.1, 10), Vector3(0.1, 0.1, 0.1), 0.8, 1, 10);
		break;
	case Explosion:
		partgaus = new GausseanParticleGen({ 3,50,3 }, { 0,0,0 }, { 3,8,3 }, { 10,10,10 }, 0.8, 20, 9);
		break;
	case Purpurina:
		unigen= new UniformParticleGenerator({ 0,70,0 }, { 0,0,0 }, { 8,8,8 }, { 8,8,8 }, 0.8, 20, 10);
		partgaus->setRadius(0.1f);
		break;
	default:
		break;
	}
}
ParticleGenerator*  TypeParticles:: getparticles() {
	switch (partenum)
	{
	case Fuego:
		return partgaus;
		break;
	case Cascada:
		return partgaus;
		break;
	case Explosion:
		return partgaus;
		break;
	case Purpurina:
		return unigen;
		break;
	default:
		break;
	}
	return nullptr;
}