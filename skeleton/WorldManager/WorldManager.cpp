#include "WorldManager.h"
#include <iostream>
#include"../Objetos/Enemy.h"
#include "../Objetos/plataforma.h"
#include"../Objetos/Tree.h"

WorldManager::WorldManager(PxScene* gScene, PxPhysics* gPhysics, ParticleSys* partsys):gScene_(gScene),gPhysics_(gPhysics),partsys_(partsys)
{	
	forceregistry = new ParticleForceRegistryPhis();

}

WorldManager::~WorldManager()
{
	for (std::list<PhsiscsPart*>::iterator it = Objects.begin(); it != Objects.end();) {
			//gScene_->removeActor(*((*it)->getRigid()));
			auto l = *it;
			delete l;
			l = nullptr;
			it = Objects.erase(it);
	}
	for (std::list<ParticleRigidGenerator*>::iterator it= particle_generators.begin(); it != particle_generators.end();++it) {
		delete (*it);
	}
	for (std::list<ForceGenerator*>::iterator it = forces.begin(); it != forces.end();++it) {
		delete (*it);
	}
	forceregistry->deleteforce();
	delete forceregistry;

}

ParticleRigidStatic* WorldManager::createRigidStatic(Vector3 pos, PxShape* shape, Vector4 color,  std::string name ,double time)
{
	ParticleRigidStatic* part = new ParticleRigidStatic(gScene_, gPhysics_, pos, shape, color);
	if (time != 0)part->settimeVida(time);
	if (name != "") { 
	
		part->setName(name);
	}
	Objects.push_back(part);
	return part;
}

ParticleRigid* WorldManager::createRigidDynamic(Vector3 pos, PxShape* shape, Vector3 vel, Vector4 color,float density, std::string name , double time)
{

	ParticleRigid* part = new ParticleRigid(gScene_,gPhysics_, pos, shape,  vel, color,density);
	
	if (time != 0)part->settimeVida(time);
	if (name != "") {
		
		part->setName(name);
	}
	Objects.push_back(part);
	for (auto s : forces) {
		forceregistry->addRegistry(s, part);
	}
	return part;

}

void WorldManager::integrate(double t)
{
	contador += t;
	if (contador >= time_gen) {
		for (auto gpart : particle_generators) {
			if (Objects.size() < NUMMAX) {
				std::list<ParticleRigid*>aux = gpart->generateParticles(gScene_, gPhysics_);
				for (auto il = aux.begin(); il != aux.end(); ++il) {
					Objects.push_back(*il);
					for (auto force : forces) {
						forceregistry->addRegistry(force, (*il));
					}
				}
			}

		}
		contador = 0;
	}
	
	
	for (std::list<PhsiscsPart*>::iterator it = Objects.begin(); it != Objects.end();) {
		(*it)->integrate(t);
		if (!(*it)->isAlive()) {
			auto s = dynamic_cast<ParticleRigid*>(*it);
			if (s != nullptr)forceregistry->deleteParticleRegistry((s));
			gScene_->removeActor(*((*it)->getRigid()));
			auto l = *it;
			delete l;
			l = nullptr;
			it = Objects.erase(it);
		
			
			
		}
		else ++it;

	}
	forceregistry->updateForces(t);
}

void WorldManager::addRigid(PhsiscsPart* rig)
{
	Objects.push_back(rig);
}


void WorldManager::handleCollision(PxActor* actor1, PxActor* actor2)
{
	std::vector<PhsiscsPart*>particles(2,nullptr);
	std::list<PhsiscsPart*>::iterator it = Objects.begin();
	int i = 0;
	while (it != Objects.end() && i < 2) {
		if ((*it)->getRigid() == actor1 || (*it)->getRigid() == actor2) {
		
			particles[i] = (*it);
			i++;
		}
		++it;
	}
	if ((particles[0]) != nullptr && (particles[1]) != nullptr) {
		(particles[1])->onCollision((particles[0]));
		(particles[0])->onCollision((particles[1]));
		cout << "colision" << "\n";
	}
}

void WorldManager::generateparticles()
{
	TypeParticlesF* tipo_part = new TypeParticlesF(TipoParticlesF::fCascada, gScene_, gPhysics_);
	particle_generators.push_back(tipo_part->getparticles());
}

void WorldManager::eraseGenerators()
{
	for (auto il = particle_generators.begin(); il != particle_generators.end();) {
		delete (*il);
		il = particle_generators.erase(il);
	}
	particle_generators.resize(0);

}

void WorldManager::generaFuerzas(TipoFuerzasF fuerza)
{
	ForceGenerator* force;
	switch (fuerza) {
	case Viento:
		force= new WindGenerator(100, { 0,260,0 });
	
		break;
	default:
		break;
	}
	for (std::list<PhsiscsPart*>::iterator it = Objects.begin(); it != Objects.end();++it) {
		auto s = dynamic_cast<ParticleRigid*>(*it);
		if(s!=nullptr)forceregistry->addRegistry(force, s);
		

	}
	forces.push_back(force);
}

void WorldManager::deletecurrentforces()
{
	for (std::list<ForceGenerator*>::iterator it = forces.begin(); it != forces.end();) {
		delete(*it);
		it = forces.erase(it);
	}
	forceregistry->deleteforce();
}
void WorldManager::createBullet(TipoBala s, Vector3 Pos, Vector3 dir) {
	

	Objects.push_back(new Proyectil(s,Pos,dir,gScene_,gPhysics_));

}
void WorldManager::deleteActor(PhsiscsPart* part)
{
	auto it = Objects.begin();
	while (it != Objects.end() && (*it) != part)it++;
	(*it)->getRenderItem()->release();
	gScene_->removeActor(*((*it)->getRigid()));
	Objects.erase(it);
	

}
void WorldManager::creaEscenario()
{
	hsv col = { 299,0.81,0.40 };
	rgb morado = hsv2rgb(col);
	//suelo
	ParticleRigidStatic* part = new ParticleRigidStatic(gScene_, gPhysics_, { 0,0,0 }, CreateShape(PxBoxGeometry(200, 10, 50)), { 0.098,0.369,0.388,1 });
	Objects.push_back(part);

	ParticleRigidStatic* partsuelo = new ParticleRigidStatic(gScene_, gPhysics_, {-150,0,-30}, CreateShape(PxBoxGeometry(100, 10, 100)), { 0.098,0.369,0.388,1 });
	Objects.push_back(partsuelo);
	

	plataforma* plat = new plataforma(gScene_, gPhysics_, { -150,0,-150 }, CreateShape(PxBoxGeometry(50, 10, 20)), { 0,1,1,1 }, this, partsys_);
	Objects.push_back(plat);

	ParticleRigidStatic* techo = new ParticleRigidStatic(gScene_, gPhysics_, { -150,100,-280 }, CreateShape(PxBoxGeometry(100, 100, 100)), { 0.0224,0.224,0.251,1 });
	Objects.push_back(techo);

	col = { 49,0.98,0.94 };
	rgb amarillo = hsv2rgb(col);
	ParticleRigidStatic* part1 = new ParticleRigidStatic(gScene_, gPhysics_, { 10,30,-30 }, CreateShape(PxBoxGeometry(100, 20, 5)), { 0.0224,0.224,0.251,1 });
	Objects.push_back(part1);

	ParticleRigidStatic* part4 = new ParticleRigidStatic(gScene_, gPhysics_, { 0,30,50 }, CreateShape(PxBoxGeometry(100, 20, 5)), { 0.0224,0.224,0.251,1 });
	Objects.push_back(part4);

	ParticleRigidStatic* part5 = new ParticleRigidStatic(gScene_, gPhysics_, { 150,30,50 }, CreateShape(PxBoxGeometry(50, 20, 100)), { 0.0224,0.224,0.251,1 });
	Objects.push_back(part5);

	
	ParticleRigidStatic* part3 = new ParticleRigidStatic(gScene_, gPhysics_, { 0,-20,0 }, CreateShape(PxBoxGeometry(20000, 10, 10000)), { 0,0,0,0 });
	//generateparticles();
	part3->setName("Muerte");
	Objects.push_back(part3);
	Trees* hay = new Trees(gScene_, gPhysics_, { -130,30,40 }, partsys_, Vector4(0.3, 0, 0.8, 1),this);
	Objects.push_back(hay);
	Trees* hays = new Trees(gScene_, gPhysics_, { -130,210,-240 }, partsys_, Vector4(0.3, 0, 0.8, 1), this);
	Objects.push_back(hays);

	for (int i = 0; i < 4; i++) {
		auto en = new Enemy(gScene_, gPhysics_, Vector3(-1 * (30 * i), 15, -15), CreateShape(PxBoxGeometry(5, 5, 5), gPhysics_->createMaterial(0.1f, 0.1f, 0.1f)), partsys_, 3, this);
		Objects.push_back(en);

	}
	TNT* tnt = new TNT(gScene_, gPhysics_, Vector3(0, 17, 15), CreateShape(PxBoxGeometry(2, 7, 2), gPhysics_->createMaterial(0.1f, 0.1f, 0.1f)), partsys_);
	Objects.push_back(tnt);
	TNT* tnts = new TNT(gScene_, gPhysics_, Vector3(-170, 210, -240), CreateShape(PxBoxGeometry(2, 7, 2), gPhysics_->createMaterial(0.1f, 0.1f, 0.1f)), partsys_);
	Objects.push_back(tnts);
}
void WorldManager::deleteescenarios()
{
	for (std::list<PhsiscsPart*>::iterator it = Objects.begin(); it != Objects.end();) {
		gScene_->removeActor(*((*it)->getRigid()));
		auto l = *it;
		delete l;
		l = nullptr;
		it = Objects.erase(it);
	}
	for (std::list<ParticleRigidGenerator*>::iterator it = particle_generators.begin(); it != particle_generators.end();) {
		auto l = (*it);
		delete (l);
		it = particle_generators.erase(it);
	}
	particle_generators.resize(0);
	for (std::list<ForceGenerator*>::iterator it = forces.begin(); it != forces.end();) {
		auto l= (*it);
		delete (l);
		it = forces.erase(it);
	}
	forces.resize(0);
	forceregistry->deleteforce();

}
void WorldManager::createmuelle(Vector3 pos, Vector4 color)
{
	ParticleRigid* p3 = new ParticleRigid(gScene_, gPhysics_,  pos, CreateShape(physx::PxCapsuleGeometry(2,1)), {0,0,0},  color, 10);
	AnchoredSpringFG* f3 = new AnchoredSpringFG(100, 0, pos+Vector3(0, 1, 0 ));
	forceregistry->addRegistry(f3, p3);
	Objects.push_back(p3);
	forces.push_back(f3);
}
TypeParticlesF::TypeParticlesF(TipoParticlesF par, PxScene* gScene, PxPhysics* gPhysics)
{
	Camera* camera = GetCamera();
	ParticleRigid* part;
	PxMaterial* gMaterial;
	
	switch (par)
	{
	
	case fCascada:
		gMaterial = gPhysics->createMaterial(0.5f,0.5f, 0.6f);
		ParticleRigid* part = new ParticleRigid(gScene, gPhysics, { 0,100,50 }, CreateShape(physx::PxBoxGeometry(2,2, 1),gMaterial), {0,0,0}, {1,1,1,1}, 500);
		part->settimeVida(10);
		partgaus = new GausseanParticleGenF(part, { 0,30,50 }, { 0,-10,10 }, { 100,100,100 }, { 0.1,0.1,0.1 }, 0.8, 8);
		partgaus->setrandomColor(true);
	break;
	}
}

ParticleRigidGenerator* TypeParticlesF::getparticles()
{
	if (partgaus)return partgaus;
	return nullptr;
}

