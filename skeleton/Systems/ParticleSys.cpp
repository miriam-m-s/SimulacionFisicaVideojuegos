#include "ParticleSys.h"

ParticleSys::ParticleSys()
{
	forceregistry = new ParticleForceRegistry();
}

ParticleSys::~ParticleSys()
{
	for (auto gpart : particle_generators) {
		delete gpart;
	}
	for (auto part : particles) {
		delete part;
	}
	forceregistry->deleteforce();
	delete forceregistry;
}

void ParticleSys::update(double t)
{
	for (auto gpart : particle_generators) {
		std::list<Particle*>aux = gpart->generateParticles();
		vector<ForceGenerator*> force = gpart->returnforce();
		
		for (auto il = aux.begin(); il != aux.end(); ++il) {
			particles.push_back(*il);
			for (auto s : force) {
				GravityForceGenerator* grav = dynamic_cast<GravityForceGenerator*>(s);
				WindGenerator* wind = dynamic_cast<WindGenerator*>(s);
				Torbellino* torb = dynamic_cast<Torbellino*>(s);
				ExplosionGenerator* exp = dynamic_cast<ExplosionGenerator*>(s);
				if (grav != nullptr) {
					forceregistry->addRegistry(grav, *il);
				}
				else if (wind != nullptr) {
					forceregistry->addRegistry(wind, *il);
				}
				else if (torb!=nullptr) {
					forceregistry->addRegistry(torb, *il);
				}
				else if (exp != nullptr) {
					forceregistry->addRegistry(exp, *il);
				}
			}
		
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
				forceregistry->deleteParticleRegistry(l);

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
				auto explosion = fire->explode();
				particles.insert(particles.end(), explosion.begin(), explosion.end());
				auto l = fire;
				delete l;
				l = nullptr;
				il = particles.erase(il);
			}
		}

	}
	forceregistry->updateForces(t);
	if (!loop_) {
		int size = particle_generators.size()-1;

		auto it = particle_generators.end();
		--it;
		it=particle_generators.erase(it);
		loop_ = true;
		//particle_generators.resize(size);
	}
}
void ParticleSys::deletecurrentgenerators()
{
	
	for (auto part : particles) {
		delete part;

	}
	for (auto gpart : particle_generators) {
		delete gpart;
	}
	particle_generators.resize(0);
	forceregistry->deleteforce();
	particles.resize(0);
}
void ParticleSys::creategenerator(TipoParticles s)
{
	TypeParticles tipo(s);
	particle_generators.push_back(tipo.getparticles());
	loop_ = tipo.isLoop();

}
ParticleGenerator* ParticleSys::getPartcleGenerator(std::string name)
{
	return nullptr;
}
void ParticleSys::generateFireWorkSystem()
{
	//firework1
	Particle* model = new Particle({ 0,0,0 }, { 0,100,0 }, { 0, 10,0 }, 0.99f, 1, 0.5, 1, { 1,0,1,1 }, false);
	Firework* fire = new Firework({ 0,0,0 }, { 0,1,0 }, { 0,100,0 }, 0.99f, 1, 0.5, 1, { 1,0,1,1 }, false);

	shared_ptr<ParticleGenerator> gener(new GausseanParticleGen(model, { 0,0,0 }, { 0,0,0 }, { 0.1,0.1,0.1 }, { 10,10,10 }, 1, 30));
	fire->addgenerator(gener);
	_fireworks_pool.push_back(fire);

	Particle* model1 = new Particle({ 0,0,0 }, { 0,100,0 }, { 0, 10,0 }, 0.99f, 1, 0.5, 1, { 0,1,1,1 }, false);
	shared_ptr<ParticleGenerator> gener3(new GausseanParticleGen(model1, { 0,0,0 }, { 0,0,0 }, { 0.1,0.1,0.1 }, { 3,3,3 }, 1, 5));
	Firework* fire2 = new Firework({ 0,0,0 }, { 0,100,0 }, { 0,0,0 }, 0.99f, 1, 0.5, 1, { 0,1,1,1 }, false);
	fire2->addgenerator(gener3);
	//PAPA
	Firework* fire1 = new Firework({ 0,0,0 }, { 0,50,0 }, { 0,-10,0 }, 0.99f, 1, 0.5, 1, { 0,1,1,1 }, false);
	/*TypeParticles tipo(TipoParticles::Explosion);*/
	auto gauss = new GausseanParticleGen(fire2, { 0,0,0 }, { 0,0,0 }, { 0.1,0.1,0.1 }, { 10,10,10 }, 1, 30);
	shared_ptr<ParticleGenerator> gener2(gauss);
	fire1->addgenerator(gener2);
	_fireworks_pool.push_back(fire1);



	shared_ptr<ParticleGenerator> gener5(new CircleGenerator(3, 40, model1));
	Firework* fire3 = new Firework({ 0,0,0 }, { 0,100,0 }, { 0,0,0 }, 0.99f, 1, 0.5, 1, { 0,1,1,1 }, false);
	fire3->addgenerator(gener5);
	//PAPA
	Firework* fire4 = new Firework({ 0,0,0 }, { 0,50,0 }, { 0,-10,0 }, 0.99f, 1, 0.5, 1, { 0,1,1,1 }, false);
	/*TypeParticles tipo(TipoParticles::Explosion);*/
	auto sphere = new CircleGenerator(10, 40, fire3);
	shared_ptr<ParticleGenerator> gener4(sphere);
	fire4->addgenerator(gener4);
	_fireworks_pool.push_back(fire4);

}
void ParticleSys::shootFireWork(int type)
{
	switch (type) {
	case 0:
		particles.push_back(_fireworks_pool[0]->clone());
		break;
	case 1:
		particles.push_back(_fireworks_pool[1]->clone());
		break;
	case 2:
		particles.push_back(_fireworks_pool[2]->clone());
		break;
	}


}
TypeParticles::TypeParticles(TipoParticles par) :partenum(par) {
	Camera* camera = GetCamera();
	Particle* part;
	Firework* fire;
	switch (par)
	{
	case Fuego:
		forcegen = new GravityForceGenerator({ 0,5,0 });
		partgaus = new GausseanParticleGen(Vector3(0, 20, 0), { 0,0,0 },
			Vector3(3, 2, 1), Vector3(0.3, 0.1, 0.1), 0.4, 200, 3);
		partgaus->setGravity({ 0,0,0 });
		partgaus->setColor({ 1,1,0,0.5f });
		partgaus->setfuego(true);
		partgaus->setRadius(0.1f);
		partgaus->addForceGenerator(forcegen);
	

		break;
	case Cascada:
		//torbe = new Torbellino(0.8, camera->getDir() * (-10), -10);
		windgen = new WindGenerator(0.8, { 3,4,0 });
		
		partgaus = new GausseanParticleGen(Vector3(0, 40, 0), {0,0,0},
			Vector3(10, 0.1, 10), Vector3(0.1, 0.1, 0.1), 0.8, 1, 100, 300);
		//partgaus->addForceGenerator(forcegen);
		partgaus->addForceGenerator(windgen);
		partgaus->setrandommass(true);

		break;
	case Explosion:
		//torbe = new Torbellino(0.8, { 0,0,0 },10);
		explosion = new ExplosionGenerator(1000,{ 3,30,3 }, 5,1000);
		explosion->setvel(2000);
		partgaus = new GausseanParticleGen({ 3,30,3 }, { 0,0,0 }, { 10,10,10 }, { 0.1,0.1,0.1 }, 0.8, 1000, 100,200);
		partgaus->setGravity({ 0,0,0 });
		partgaus->setColor({ 0,1,1,1 });
		partgaus->setfuego(true);
		partgaus->setrandommass(true);
		//partgaus->setRandomColor(true);
		partgaus->addForceGenerator(explosion);
		repeat = false;
		//partgaus->addForceGenerator(torbe);
		break;
	case Purpurina:
		torbe = new Torbellino(0.8, { 0,0,0 }, 10);
		unigen = new UniformParticleGenerator({ 0,0,0 }, { 0,0,0 }, { 0.1,0.1,0.1 }, { 8,8,8 }, 0.8, 20, 10);
		unigen->setRadius(0.5);
		unigen->setGravity({ 0,0,0 });
		unigen->addForceGenerator(torbe);
		break;
	case Polvo:
		forcegen = new GravityForceGenerator({ 0,-10,0 });
		part = new Particle({ 0,50,0 }, { 0,1,0 }, { 0, 0,0 }, 0.99f, 0.1, 0.5, 8, { 0.6,0.6,0.6,0 }, true);
		unigen = new UniformParticleGenerator({ 0,50,0 }, { 0,0,0 }, part, { 3,3,3 }, { 100,100,100 }, 0.8, 5);
		unigen->addForceGenerator(forcegen);
		break;
	case Poder:
		part = new Particle({ 0,50,0 }, { 100,0,0 }, { 0, 0,0 }, 0.99f, 0.4, 0.5, 1, { 1,1.0,1,1 }, true);
		partgaus = new GausseanParticleGen(part, part->getpos(), part->getvel(), { 3,3,3 }, { 10,10,0.1 }, 0.8, 10);
		partgaus->setfuego(true);
		partgaus->setGravity(part->getgravity());

		break;
	case Portal:
	
		part = new Particle({ 0,50,0 }, { 0,0,0 }, { 0,0,0 }, 0.99, 0.1, 3, 3, { 0.5,1,0.5,1 }, true);
		circle = new CircleGenerator(2, 30, part);
		circle->setfuego(true);
		
		break;
	case Esphere:
		part = new Particle({ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, 0.99, 0.1, 3, 1, { 0.5,1,0.5,1 }, true);

		sphere = new SphereGenerator(2, 30, part);
		sphere->setfuego(true);
		break;

	default:
		break;
	}
}
ParticleGenerator* TypeParticles::getparticles() {
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
	case Portal:
		return circle;
		break;
	case Esphere:
		return sphere;
		break;
	default:
		break;
	}
	return nullptr;
}