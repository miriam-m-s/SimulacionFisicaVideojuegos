#include "SceneShoot.h"

SceneShoot::SceneShoot(PxScene* gScene, PxPhysics* gPhysics)
{
	is = new Interfaz(GetCamera());
	wold = new WorldManager(gScene, gPhysics);
}
SceneShoot::~SceneShoot()
{
	delete wold;
	delete is;
}

void SceneShoot::update(double const& t)
{
	wold->integrate(t);
	is->update(t);
}

void SceneShoot::inputHandler(unsigned char key)
{
	Vector3 p = GetCamera()->getTransform().p + GetCamera()->getDir() * 10;
	switch (toupper(key))
	{	
	case 'X':
	
		wold->deletecurrentforces();
		break;
	
	case 'G':
		wold->generaFuerzas(Viento);
		break;
	case 'B':
		wold->createBullet(TipoBala(balas), p, GetCamera()->getDir());
		break;
	case '1':
		balas = TipoBalas::Balacanyon;
		break;
	case '2':
		balas = TipoBalas::Bala;
		break;
	case '3':
		balas = TipoBalas::Laser;
		break;
	
	case ' ':
	{
		break;
	}
	default:
		break;
	}
}

void SceneShoot::handleCollision(PxActor* actor1, PxActor* actor2)
{
	wold->handleCollision(actor1, actor2);
}
