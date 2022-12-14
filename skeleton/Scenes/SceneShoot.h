#pragma once
#include "Scene.h"
#include <PxPhysicsAPI.h>
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "../WorldManager/WorldManager.h"
class SceneShoot:public Scene
{
public:
	SceneShoot(PxScene* gScene, PxPhysics* gPhysics);
	~SceneShoot();
	virtual void update(double const& t) override;
	virtual void inputHandler(unsigned char key) override;
protected:
	WorldManager* wold;
};

