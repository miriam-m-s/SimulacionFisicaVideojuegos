#pragma once
#include <PxPhysicsAPI.h>
#include "../core.hpp"
#include "../RenderUtils.hpp"
using namespace physx;
class Scene {
public:
	Scene(){}
	Scene(PxScene* gScene, PxPhysics* gPhysics) {
	}
	virtual ~Scene() {
	}
	virtual void update(double const& t) = 0;
	virtual void inputHandler(unsigned char key) = 0;
	virtual void handleCollision(PxActor* actor1, PxActor* actor2) = 0;
	//virtual void mouseHandler(int button, int state, int x, int y) {};
};