#include "SceneShoot.h"

SceneShoot::SceneShoot(PxScene* gScene, PxPhysics* gPhysics)
{
	wold = new WorldManager(gScene, gPhysics);
}
SceneShoot::~SceneShoot()
{

}

void SceneShoot::update(double const& t)
{
	wold->integrate(t);
}

void SceneShoot::inputHandler(unsigned char key)
{
	switch (toupper(key))
	{	
	case 'X':
	
		wold->deletecurrentforces();
		break;
	
	case 'G':
		wold->generaFuerzas(Viento);
		break;
	
	case ' ':
	{
		break;
	}
	default:
		break;
	}
}
