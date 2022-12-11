#include "WorldManager.h"
#include <iostream>


WorldManager::WorldManager(PxScene* gScene, PxPhysics* gPhysics):gScene_(gScene),gPhysics_(gPhysics)
{	
	ParticleRigid* part = new ParticleRigid(gScene_, gPhysics_, { 0,0,0 }, CreateShape(PxBoxGeometry(100, 0.1, 100)), { 0.8,0.8,0.8,1 });
	Objects.push_back(part);

	ParticleRigid* part1 = new ParticleRigid(gScene_, gPhysics_, { 10,10,-30 }, CreateShape(PxBoxGeometry(40, 20, 5)), { 0.8,0.8,0.8,1 });
	Objects.push_back(part1);

	generateparticles();
}

WorldManager::~WorldManager()
{
	for (std::list<ParticleRigid*>::iterator it = Objects.begin(); it != Objects.end();) {

			auto l = *it;
			delete l;
			l = nullptr;
			it = Objects.erase(it);
	}

}

ParticleRigid* WorldManager::createRigidStatic(Vector3 pos, PxShape* shape, Vector4 color,  std::string name ,double time)
{
	ParticleRigid* part = new ParticleRigid(gScene_, gPhysics_, pos, shape, color);
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
	return part;

}

void WorldManager::integrate(double t)
{
	for (auto gpart : particle_generators) {
		if (Objects.size() < NUMMAX){
			std::list<ParticleRigid*>aux = gpart->generateParticles(gScene_, gPhysics_);
			for (auto il = aux.begin(); il != aux.end(); ++il) {
				Objects.push_back(*il);
			}
		}
		
	}
	for (std::list<ParticleRigid*>::iterator it = Objects.begin(); it != Objects.end();) {
		(*it)->integrate(t);
		if (!(*it)->isAlive()) {
			auto l = *it;
			delete l;
			l = nullptr;
			it = Objects.erase(it);
			
		}
		else ++it;

	}
}

void WorldManager::handleCollision(PxActor* actor1, PxActor* actor2)
{
	std::vector<ParticleRigid*>particles(2,nullptr);
	std::list<ParticleRigid*>::iterator it = Objects.begin();
	int i = 0;
	while (it != Objects.end() && i < 2) {
		if ((*it)->getRigid() == actor1 || (*it)->getRigid() == actor2) {
		
			particles[i] = (*it);
			i++;
		}
		else ++it;
	}
	if ((particles[0]) != nullptr && (particles[1]) != nullptr) {
		(particles[1])->onCollision((particles[0]));
		(particles[0])->onCollision((particles[1]));
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

TypeParticlesF::TypeParticlesF(TipoParticlesF par, PxScene* gScene, PxPhysics* gPhysics)
{
	Camera* camera = GetCamera();
	ParticleRigid* part;
	PxMaterial* gMaterial;
	
	switch (par)
	{
	
	case fCascada:
		gMaterial = gPhysics->createMaterial(10.0f, 10.0f, 10.0f);
		ParticleRigid* part = new ParticleRigid(gScene, gPhysics, { 0,100,50 }, CreateShape(physx::PxBoxGeometry(1, 1, 1),gMaterial), {0,0,0}, {1,1,1,1}, 2);

		partgaus = new GausseanParticleGenF(part, { 0,100,50 }, { -10,0,-10 }, { 0.1,0.1,0.1 }, { 0.1,0.1,0.1 }, 0.8, 3);
		partgaus->setrandomColor(true);
		

	break;
	}
}

ParticleRigidGenerator* TypeParticlesF::getparticles()
{
	if (partgaus)return partgaus;
	return nullptr;
}
