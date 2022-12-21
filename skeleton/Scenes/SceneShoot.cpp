#include "SceneShoot.h"

SceneShoot::SceneShoot(PxScene* gScene, PxPhysics* gPhysics):gScene_(gScene),gPhysics_(gPhysics)
{
	is = new Interfaz(GetCamera());

	part_sys = new ParticleSys();
	wold = new WorldManager(gScene, gPhysics, part_sys);
	createplayer();
}
void SceneShoot::createEnemys(physx::PxScene* gScene, physx::PxPhysics* gPhysics)
{
	
	
}
void SceneShoot::createplayer()
{
	player = new Player(gScene_, gPhysics_, 3, is);

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
	//is->update(t);
	wold->integrate(t);
	part_sys->update(t);
	GetCamera()->setEye(player->getRigid()->getGlobalPose().p + physx::PxVec3(0, 6, 0));
	is->update(t);
	if (player->getVidas() == 0) {
		player->resetVidas();
		wold->deleteActor(player);
		createplayer();
		wold->deleteescenarios();
		wold->creaEscenario();
	}
}

void SceneShoot::inputHandler(unsigned char key)
{
	const physx::PxVec3 dirForward = { GetCamera()->getDir().x, 0, GetCamera()->getDir().z };
	const physx::PxVec3 dirSide = { GetCamera()->getDir().cross({0, 1, 0}).getNormalized() };
	Vector3 p = GetCamera()->getTransform().p + GetCamera()->getDir() * 10 + Vector3(0, -1, 0);
	switch (toupper(key))
	{	
	case 'W':	
		player->getRigid()->addForce(dirForward * 600.f*50);
		break;
	case 'A':	 
		player->getRigid()->addForce(-dirSide * 600.f*50);
		break;
	case 'D':	 
		player->getRigid()->addForce(dirSide * 600.f*50); break;
	case 'S':	
		player->getRigid()->addForce(-dirForward * 600.f*50); 
		break;
	case ' ':	
		
		player->getRigid()->addForce({ 0, 40*50, 0 },PxForceMode::eIMPULSE);
		break;  
	case 'X':
	
		wold->deletecurrentforces();
		break;
	
	case 'G':
		wold->generaFuerzas(TipoFuerzasF::Viento);
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
