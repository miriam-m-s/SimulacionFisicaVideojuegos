#include "WorldManager.h"
#include <iostream>


WorldManager::WorldManager(PxScene* gScene, PxPhysics* gPhysics):gScene_(gScene),gPhysics_(gPhysics)
{
	PxRigidStatic* Suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	Suelo->attachShape(*shape);
	RenderItem* item = new RenderItem(shape, Suelo, { 0.8,0.8,0.8,1 });
	gScene->addActor(*Suelo);
	ParticleRigid* part = new ParticleRigid(Suelo, item);
	Objects.push_back(part);

	PxRigidStatic* Pared = gPhysics->createRigidStatic(PxTransform({ 10,10,-30 }));
	PxShape* shape_suelo = CreateShape(PxBoxGeometry(40,20, 5));
	Pared->attachShape(*shape_suelo);
	RenderItem* item1 = new RenderItem(shape_suelo, Pared, { 0.8,0.8,0.8,1 });
	gScene->addActor(*Pared);
	ParticleRigid* part1 = new ParticleRigid(Pared, item1);
	Objects.push_back(part1);
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

void WorldManager::createRigidStatic(Vector3 pos, Vector3 size, Vector4 color, std::string name ,double time)
{
	PxRigidStatic* new_solid = gPhysics_->createRigidStatic(PxTransform(pos));
	PxShape* shape_suelo = CreateShape(PxBoxGeometry(40, 20, 5));
	new_solid->attachShape(*shape_suelo);
	RenderItem* item = new RenderItem(shape_suelo, new_solid, color);
	gScene_->addActor(*new_solid);
	ParticleRigid* part = new ParticleRigid(new_solid,item);
	if (time != 0)part->settimeVida(time);
	if (name != "") { 
	
		part->setName(name);
	}
	Objects.push_back(part);
}

void WorldManager::createRigidDynamic(Vector3 pos, Vector3 size, Vector3 vel, Vector4 color, std::string name , double time)
{
	PxRigidDynamic* new_solid;
	

	new_solid = gPhysics_->createRigidDynamic(PxTransform(pos));
	new_solid->setLinearVelocity(vel);
	new_solid->setAngularVelocity({ 0,0,0 });
	PxShape* shape = CreateShape(PxBoxGeometry(size));
	new_solid->attachShape(*shape);
	new_solid->setMassSpaceInertiaTensor({ size.y * size.z, size.x*size.z, size.x *size.y });

	RenderItem* item = new RenderItem(shape, new_solid, color);
	gScene_->addActor(*new_solid);
	ParticleRigid* part = new ParticleRigid(new_solid,item);
	if (time != 0)part->settimeVida(time);
	if (name != "") {
		
		part->setName(name);
	}
	Objects.push_back(part);

}

void WorldManager::integrate(double t)
{
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
	std::vector<std::list<ParticleRigid*>::iterator>particles(2);
	std::list<ParticleRigid*>::iterator it = Objects.begin();
	int i = 0;
	while (it != Objects.end() && i < 2) {
		if ((*it)->getRigid() == actor1 || (*it)->getRigid() == actor2) {
		
			particles[i] = (it);
			i++;
		}
		else ++it;
	}
	if ((*particles[0]) != nullptr && (*particles[1]) != nullptr) {
		(*particles[1])->onCollision((*particles[0]));
		std::cout << (*particles[0])->getName();
		(*particles[0])->onCollision((*particles[1]));
		std::cout << (*particles[1])->getName();
	}
}


