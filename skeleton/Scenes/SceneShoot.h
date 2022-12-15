#pragma once
#include "Scene.h"
#include <PxPhysicsAPI.h>
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "../WorldManager/WorldManager.h"
#include"../Interfaz/Interfaz.h"
class SceneShoot:public Scene
{
public:
	SceneShoot(PxScene* gScene, PxPhysics* gPhysics);
	~SceneShoot();
	virtual void update(double const& t) override;
	virtual void inputHandler(unsigned char key) override;
	virtual void handleCollision(PxActor* actor1, PxActor* actor2)override;
protected:
	WorldManager* wold;
	Interfaz* is;
	TipoBalas balas= TipoBalas::Balacanyon;
	
};

