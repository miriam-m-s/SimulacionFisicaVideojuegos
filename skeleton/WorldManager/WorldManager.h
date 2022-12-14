#pragma once
#include <PxPhysicsAPI.h>
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include <list>
#include<vector>
#include<string>
#include"ParticleRigid.h"
#include "ParticleRigidGenerator.h"
#include "../Force/ParticleDragGenerator.h"
#include "../Force/ForceGenarator.h"
#include "../Force/ParticleForceRegistry.h"
#define MAXPART 400;
//
using namespace physx;
enum TipoParticlesF {
	fCascada
};
enum TipoFuerzasF {
	Viento
};
class WorldManager
{
public:
	WorldManager(PxScene* gScene, PxPhysics* gPhysics);
	~WorldManager();
	ParticleRigidStatic* createRigidStatic(Vector3 pos, PxShape* shape, Vector4 color,  std::string name =" ", double time = 0);
	ParticleRigid* createRigidDynamic(Vector3 pos, PxShape* shape, Vector3 vel, Vector4 color,float density=2, std::string name="", double time=0);
	void integrate(double t);
	void handleCollision(PxActor* actor1, PxActor* actor2);
	void generateparticles();
	void eraseGenerators();
	void generaFuerzas(TipoFuerzasF fuerza);
	void deletecurrentforces();
protected:
	PxScene* gScene_;
	PxPhysics* gPhysics_;
	std::list<PhsiscsPart*>Objects;
	ParticleForceRegistryPhis* forceregistry;
	list<ParticleRigidGenerator*>particle_generators;
	list<ForceGenerator*>forces;
	int NUMMAX = MAXPART;
	double time_gen=1;
	double contador=0;
};

class TypeParticlesF {
public:
	TypeParticlesF(TipoParticlesF par,PxScene* gScene, PxPhysics* gPhysics);
	ParticleRigidGenerator* getparticles();
	~TypeParticlesF() {

	};

private:
	GausseanParticleGenF* partgaus = nullptr;
	bool repeat = true;
};
