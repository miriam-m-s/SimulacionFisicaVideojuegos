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

	for (auto gpart : fuerzasMuelles) {
		auto anchored = dynamic_cast<AnchoredSpringFG*>(gpart);
		if (anchored == nullptr)
			delete gpart;
		else delete anchored;
	}


	for (auto gpart : forces) {

		auto buoy = dynamic_cast<BuoyancyForceGenerator*>(gpart);

		if (buoy != nullptr)delete buoy;
		else delete gpart;
	}

	forceregistry->deleteforce();
	delete forceregistry;
}

void ParticleSys::update(double t)
{
	for (auto gpar = particle_generators.begin(); gpar != particle_generators.end();) {
		auto gpart = (*gpar);
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
				else if (torb != nullptr) {
					forceregistry->addRegistry(torb, *il);
				}
				else if (exp != nullptr) {
					forceregistry->addRegistry(exp, *il);
				}
			}

		}
		auto s=gpart->gettime()--;
		if (s <= 0) {
			delete(gpart);
			gpar = particle_generators.erase(gpar);
		}
		else {
			++gpar;
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
		int size = particle_generators.size() - 1;

		auto it = particle_generators.end();
		--it;
		it = particle_generators.erase(it);
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
	if (fuerzasMuelles.size() > 0) {
		for (auto gpart : fuerzasMuelles) {
			auto anchored = dynamic_cast<AnchoredSpringFG*>(gpart);
			auto buoy = dynamic_cast<BuoyancyForceGenerator*>(gpart);
			if (anchored != nullptr)
				delete anchored;
			else if (buoy != nullptr)delete buoy;
			else delete gpart;
		}
		fuerzasMuelles.resize(0);
	}
	if (forces.size() > 0) {
		for (auto gpart : forces) {

			auto buoy = dynamic_cast<BuoyancyForceGenerator*>(gpart);

			if (buoy != nullptr)delete buoy;
			else delete gpart;
		}
		forces.resize(0);
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
void ParticleSys::generatemuelle(int ejs) {
	if (ejs == 0) {
		Particle* ancla = new Particle({ -11,10,0 }, { 0,0,0 }, { 0, 0,0 }, 0.85, 4, 2, 1000, { 1,0,0,1 }, true);
		Particle* noancla = new Particle({ 11,10,0 }, { 0,0,0 }, { 0, 0,0 }, 0.85, 4, 2, 1000, { 1,1,0,1 }, true);
		ancla->setEulerExplicit(false);
		noancla->setEulerExplicit(false);

		SpringForceGenerator* f1 = new SpringForceGenerator(15, 20, ancla);
		f1->setGoma(true);
		forceregistry->addRegistry(f1, noancla);
		SpringForceGenerator* f2 = new SpringForceGenerator(15, 20, noancla);
		f2->setGoma(true);
		forceregistry->addRegistry(f2, ancla);
		fuerzasMuelles.push_back(f1);
		fuerzasMuelles.push_back(f2);
		particles.push_back(ancla);
		particles.push_back(noancla);
	}
	else if (ejs == 1) {
		Particle* p3 = new Particle({ -10,20,0 }, { 0,0,0 }, { 0, 0,0 }, 0.85, 4, 2, 1000, { 0.7,0,1,1 }, true);
		p3->setEulerExplicit(false);
		AnchoredSpringFG* f3 = new AnchoredSpringFG(5, 10, { 10.0,20.0,0 });
		forceregistry->addRegistry(f3, p3);
		particles.push_back(p3);
		fuerzasMuelles.push_back(f3);
	}
	else if (ejs == 2) {
		//Particle* p1 = new Particle({ 0,20,0 }, { 0,0,0 }, { 0, 0,0 }, 0.85, 4, 2, 1000, { 1,0,1,1 }, true);
		Particle* p2 = new Particle({ 0,15,0 }, { 0,0,0 }, { 0, 0,0 }, 0.85, 4, 2, 1000, { 1,0,0.7,1 }, true);
		Particle* p3 = new Particle({ 0,10,0 }, { 0,0,0 }, { 0, 0,0 }, 0.85, 4, 2, 1000, { 1,0,0.4,1 }, true);
		Particle* p4 = new Particle({ 0,5,0 }, { 0,0,0 }, { 0, 0,0 }, 0.85, 4, 2, 1000, { 1,0,0.1,1 }, true);
		Particle* p5 = new Particle({ 0,0,0 }, { 0,0,0 }, { 0, 0,0 }, 0.85, 4, 2, 1000, { 0.7,0,0.1,1 }, true);
		Particle* p6 = new Particle({ 0,-5,0 }, { 0,0,0 }, { 0, 0,0 }, 0.85, 4, 2, 1000, { 0.4,0,0.1,1 }, true);
		/*p1->setEulerExplicit(false);
		p2->setEulerExplicit(false);*/
		//1,2
		AnchoredSpringFG* f1 = new AnchoredSpringFG(15, 20, { 0,20,0 });
		forceregistry->addRegistry(f1, p2);
		SpringForceGenerator* f2 = new SpringForceGenerator(15, 20, p2);
		//forceregistry->addRegistry(f2, p1);
		//2,3
		forceregistry->addRegistry(f2, p3);
		SpringForceGenerator* f3 = new SpringForceGenerator(15, 20, p3);
		forceregistry->addRegistry(f3, p2);
		//3,4
		forceregistry->addRegistry(f3, p4);
		SpringForceGenerator* f4 = new SpringForceGenerator(15, 20, p4);
		forceregistry->addRegistry(f4, p3);
		//4,5
		forceregistry->addRegistry(f4, p5);
		SpringForceGenerator* f5 = new SpringForceGenerator(15, 20, p5);
		forceregistry->addRegistry(f5, p4);
		//5,6
		forceregistry->addRegistry(f5, p6);
		SpringForceGenerator* f6 = new SpringForceGenerator(15, 20, p6);
		forceregistry->addRegistry(f6, p5);

		fuerzasMuelles.push_back(f1);
		fuerzasMuelles.push_back(f2);
		fuerzasMuelles.push_back(f3);
		fuerzasMuelles.push_back(f4);
		fuerzasMuelles.push_back(f5);
		fuerzasMuelles.push_back(f6);
		//particles.push_back(p1);
		particles.push_back(p2);
		particles.push_back(p3);
		particles.push_back(p4);
		particles.push_back(p5);
		particles.push_back(p6);

	}
	else if (ejs == 3) {
		Particle* p2 = new Particle({ 0,20,0 }, { 0,0,0 }, { 0, 0,0 }, 0.8, 4, 100, 1000, { 1,0,0,1 }, true, BOX);
		GravityForceGenerator* grav = new GravityForceGenerator({ 0,-9.8,0 });
		ParticleDragGenerator* drag = new ParticleDragGenerator(100, 0);
		forceregistry->addRegistry(grav, p2);
		BuoyancyForceGenerator* buoy = new BuoyancyForceGenerator(1, 100, 1, 50, 920);
		forces.push_back(buoy);
		forces.push_back(grav);
		forces.push_back(drag);
		forceregistry->addRegistry(buoy, p2);
		forceregistry->addRegistry(drag, p2);
		particles.push_back(p2);
	}





}

void ParticleSys::putGravity()
{
	GravityForceGenerator* grav;
	if (particles.size() > 0) {
		grav = new GravityForceGenerator({ 0,-10,0 });
	}
	for (auto s : particles) {

		forceregistry->addRegistry(grav, s);
	}
}

void ParticleSys::incrementK(double as)
{
	for (auto s : fuerzasMuelles) {
		s->addK(as);
	}
}

void ParticleSys::createBloodExplosion(Vector3 pos)
{
	TypeParticles part(Sangre,pos);
	particle_generators.push_back(part.getparticles());

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

		partgaus = new GausseanParticleGen(Vector3(0, 40, 0), { 0,0,0 },
			Vector3(10, 0.1, 10), Vector3(0.1, 0.1, 0.1), 0.8, 1, 100, 300);
		//partgaus->addForceGenerator(forcegen);
		partgaus->addForceGenerator(windgen);
		partgaus->setrandommass(true);

		break;
	case Explosion:
		//torbe = new Torbellino(0.8, { 0,0,0 },10);
		explosion = new ExplosionGenerator(1000, { 3,30,3 }, 5, 1000);
		explosion->setvel(2000);
		partgaus = new GausseanParticleGen({ 3,30,3 }, { 0,0,0 }, { 10,10,10 }, { 0.1,0.1,0.1 }, 0.8, 1000, 100, 200);
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
TypeParticles::TypeParticles(TipoParticles par, Vector3 pos):partenum(par)
{
	switch (par)
	{
	case Sangre:
		explosion = new ExplosionGenerator(10000, pos, 5, 10000);
		explosion->setvel(2000);
		partgaus = new GausseanParticleGen(pos, { 0,0,0 }, { 10,10,10 }, { 0.1,0.1,0.1 }, 0.8, 1000, 2, 50);
		partgaus->setGravity({ 0,0,0 });
		partgaus->setColor({ 1,1,0,1 });
		partgaus->setfuego(true);
		partgaus->settimes(1);
		//partgaus->setran;
		partgaus->setrandommass(true);
		//partgaus->setRandomColor(true);
		partgaus->addForceGenerator(explosion);
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
	case Sangre:
		return partgaus;
		break;
	default:
		break;
	}
	return nullptr;
}