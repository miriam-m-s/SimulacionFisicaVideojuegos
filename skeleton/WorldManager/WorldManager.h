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
#include"../ColorHSV.h"
#include "../Objetos/Proyectil.h"
#include"../Objetos/TNT.h"
#include"../Systems/ParticleSys.h"
#include "../Objetos/Enemy2.h"

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
	WorldManager(PxScene* gScene, PxPhysics* gPhysics,ParticleSys*partsys);
	~WorldManager();
	ParticleRigidStatic* createRigidStatic(Vector3 pos, PxShape* shape, Vector4 color,  std::string name =" ", double time = 0);
	ParticleRigid* createRigidDynamic(Vector3 pos, PxShape* shape, Vector3 vel, Vector4 color,float density=2, std::string name="", double time=0);
	void integrate(double t);
	void addRigid(PhsiscsPart* rig);
	void addPlayer(ParticleRigid* rig);
	void handleCollision(PxActor* actor1, PxActor* actor2);
	void generateparticles();
	void eraseGenerators();
	void generaFuerzas(TipoFuerzasF fuerza);
	void deletecurrentforces();
	void createBullet(TipoBala s, Vector3 Pos, Vector3 dir);
	void deleteActor(PhsiscsPart* part);
	void creaEscenario();
	void deleteescenarios();
	void createmuelle(Vector3 pos ,Vector4 color);
	void creaEnemy(Vector3 pos, int vidas, PxShape* shape);
	ParticleRigid* player;
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
	std::vector<Proyectil*>bullets;
	ParticleSys* partsys_;
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
