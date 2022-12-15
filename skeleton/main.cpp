#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Systems/ParticleSys.h"
#include <iostream>
#include "Objetos/Proyectil.h"
#include "WorldManager/WorldManager.h"
#include "Scenes/SceneManager.h"



using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;
//Proyectil* part=NULL;
std::vector<Proyectil*>bullets;
PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;

int firework = 0;
PxMaterial*				gMaterial	= NULL;
ParticleSys* part_system;
PxPvd*                  gPvd        = NULL;
auto changebalas = TipoBalas::Balacanyon;
PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
SceneManager* scene;

int changeparticles=0;
int changemuelles = 0;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	part_system = new ParticleSys();
	part_system->generateFireWorkSystem();
	scene = new SceneManager(gScene, gPhysics);
	
	 
	
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{

	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	part_system->update(t);
	//std::vector<Proyectil*>iterator il=bullet

	scene->update(t);

	
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	delete part_system;
	for (int i = 0; i < bullets.size(); i++) {
		delete bullets[i];
	}
	delete scene;
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	
	scene->InputHandler(key);
	switch(toupper(key))
	{
	case 'B': 
		
		
		break;
	case '1':
		changebalas = TipoBalas::Bala;
		break;
	case '2':
		changebalas = TipoBalas::Balacanyon;
		break;
	case '3':
		changebalas = TipoBalas::Laser;
		break;
	case 'F':
		part_system->shootFireWork(firework);
		firework++;
		if (firework > 3)firework = 0;

		break;
	case 'X':
		part_system->deletecurrentgenerators();
	
		break;
	case 'Q':
		part_system->creategenerator(TipoParticles(changeparticles));
		changeparticles++;
		if (changeparticles >=5) {
			changeparticles = 0;
		}
		break;
	case 'M':
		part_system->deletecurrentgenerators();
		part_system->generatemuelle(changemuelles);
		changemuelles++;
		if (changemuelles >= 4) {
			changemuelles = 0;
		}
		break;
	case 'G':
	
		break;
	case '+':
		part_system->incrementK(0.5);
		break;
	case '-':
		part_system->incrementK(-0.5);
		break;
	case ' ':
	{
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
	scene->handleCollision(actor1, actor2);
	
	
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}