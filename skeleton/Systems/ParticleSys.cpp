#include "ParticleSys.h"

ParticleSys::ParticleSys()
{
	TypeParticles tipo(TipoParticles::Cascada);
	
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
		auto fire = dynamic_cast<Firework*>(particle);
		if (fire == nullptr) {
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
		else {
			if (fire->active()) {
				fire->integrate(t);
				++il;
			}
			else {
				auto explosion=fire->explode();
				particles.insert(particles.end(), explosion.begin(), explosion.end());	
				auto l = fire;
				delete l;
				l = nullptr;
				il = particles.erase(il);
			}
		}
		
	}
}
ParticleGenerator* ParticleSys::getPartcleGenerator(std::string name)
{
	return nullptr;
}
void ParticleSys::generateFireWorkSystem()
{
	//firework1
	Particle*model= new Particle({ 0,0,0 }, { 0,100,0 }, { 0, 10,0 }, 0.99f, 1, 0.5, 1, { 1,0,1,1 },false);
	Firework* fire = new Firework({ 0,0,0 }, { 0,1,0 }, {0,100,0 }, 0.99f, 1, 0.5, 1, { 1,0,1,1 },false);
	/*TypeParticles tipo(TipoParticles::Explosion);*/
	shared_ptr<ParticleGenerator> gener(new GausseanParticleGen(model, { 0,0,0 }, { 0,0,0 }, { 0.1,0.1,0.1 }, { 10,10,10 }, 1, 30));
	fire->addgenerator(gener);
	_fireworks_pool.push_back(fire);
	
}
void ParticleSys::shootFireWork(int type)
{
	particles.push_back(_fireworks_pool[0]->clone());
}
TypeParticles::TypeParticles(TipoParticles par):partenum(par) {
	Camera* camera = GetCamera();
	Particle* part;
	Firework* fire;
	switch (par)
	{
	case Fuego:
		partgaus=new GausseanParticleGen(Vector3(0, 20, 0), { 0,0,0 },
		Vector3(3, 2, 1), Vector3(0.3, 0.1, 0.1), 0.4, 200, 3);
		partgaus->setGravity({ 0,5,0 });
		partgaus->setColor({ 1,1,0,0.5f });
		partgaus->setfuego(true);
		partgaus->setRadius(0.1f);

		break;
	case Cascada:
		 
		partgaus = new GausseanParticleGen(Vector3(15, 40, 0), camera->getDir() * (-10),
			Vector3(0.1, 0.1, 10), Vector3(0.1, 0.1, 0.1), 0.8, 1, 10);

		break;
	case Explosion:
		partgaus = new GausseanParticleGen({ 3,50,3 }, { 0,0,0 }, { 3,8,3 }, { 10,10,10 }, 0.8, 20, 9);
		partgaus->setRandomColor(true);
		break;
	case Purpurina:
		unigen= new UniformParticleGenerator({ 0,70,0 }, { 0,0,0 }, { 8,8,8 }, { 8,8,8 }, 0.8, 20, 10);
		unigen->setRadius(0.1f);
		break;
	case Polvo:
		part = new Particle({ 0,50,0 }, { 0,1,0 }, { 0, 0,0 }, 0.99f, 0.1, 0.5, 8, { 0.6,0.6,0.6,0 },true);
		unigen = new UniformParticleGenerator({ 0,50,0 }, { 0,0,0 }, part, { 3,3,3 }, { 100,100,100 }, 0.8, 50);
		break;
	case Poder:
		part = new Particle({ 0,50,0 }, { 100,0,0 }, { 0, 0,0 }, 0.99f, 0.4, 0.5,1, { 1,1.0,1,1 },true);
		partgaus = new GausseanParticleGen(part,part->getpos(), part->getvel(), {3,3,3}, {10,10,0.1}, 0.8, 10);
		partgaus->setfuego(true);
		partgaus->setGravity(part->getgravity());
		break;
	case Fireworks:
		 fire= new Firework({ 0,50,0 }, { 0,1,0 }, { 100, 0,0 }, 0.99f, 0.4, 0.5, 1, { 1,1.0,1,1 },false);
		partgaus = new GausseanParticleGen(fire, { 0,50,0 }, { 0,0,0 }, { 3,3,3 }, { 10,0.1,0.1 }, 0.8, 10);
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
	case Polvo:
		return unigen;
		break;
	case Poder:
		return partgaus;
		break;
	default:
		break;
	}
	return nullptr;
}