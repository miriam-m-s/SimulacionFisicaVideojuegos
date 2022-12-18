#include "SceneShoot.h"

SceneShoot::SceneShoot(PxScene* gScene, PxPhysics* gPhysics)
{
	is = new Interfaz(GetCamera());
	wold = new WorldManager(gScene, gPhysics);
	part_sys = new ParticleSys();
	wold->addRigid(new Enemy(gScene, gPhysics, { 10,140,-30 }, CreateShape(PxBoxGeometry(20, 20, 20)), part_sys, 1));
	player = new ParticleRigid(gScene, gPhysics, GetCamera()->getTransform().p, CreateShape(PxSphereGeometry(5)), { 0,0,0 }, { 0,0,0,0 }, 2);
	player->setInfiniteVida(true);
	player->getRigid()->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y | PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);
	wold->addRigid(player);
}
SceneShoot::~SceneShoot()
{
	delete wold;
	delete is;
	delete part_sys;
}

void SceneShoot::update(double const& t)
{
	wold->integrate(t);
	is->update(t);
	part_sys->update(t);
	GetCamera()->setEye(player->getRigid()->getGlobalPose().p + physx::PxVec3(0, 5, 0));

}

void SceneShoot::inputHandler(unsigned char key)
{
	const physx::PxVec3 dirForward = { GetCamera()->getDir().x, 0, GetCamera()->getDir().z };
	const physx::PxVec3 dirSide = { GetCamera()->getDir().cross({0, 1, 0}).getNormalized() };
	Vector3 p = GetCamera()->getTransform().p + GetCamera()->getDir() * 10 + Vector3(0, -3, 0);
	switch (toupper(key))
	{	
	case 'W':	
		player->getRigid()->addForce(dirForward * 600.f);
		break;
	case 'A':	 
		player->getRigid()->addForce(-dirSide * 600.f);
		break;
	case 'D':	 
		player->getRigid()->addForce(dirSide * 600.f); break;
	case 'S':	
		player->getRigid()->addForce(-dirForward * 600.f); 
		break;
	case ' ':	 
		player->getRigid()->addForce({ 0, 200, 0 });
		break;
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
	
	
	default:
		break;
	}
	

}

void SceneShoot::handleCollision(PxActor* actor1, PxActor* actor2)
{
	wold->handleCollision(actor1, actor2);
}
