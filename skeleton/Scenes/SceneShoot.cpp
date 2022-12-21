#include "SceneShoot.h"

SceneShoot::SceneShoot(PxScene* gScene, PxPhysics* gPhysics):gScene_(gScene),gPhysics_(gPhysics)
{
	is = new Interfaz(GetCamera());
	wold = new WorldManager(gScene, gPhysics);
	part_sys = new ParticleSys();
	createEnemys(gScene, gPhysics);
	createplayer();
}
void SceneShoot::createEnemys(physx::PxScene* gScene, physx::PxPhysics* gPhysics)
{
	for (int i = 0; i < 4; i++) {
		auto en = new Enemy(gScene, gPhysics, Vector3(-1*(30 * i ), 15, -15), CreateShape(PxBoxGeometry(5, 5, 5), gPhysics->createMaterial(0.1f, 0.1f, 0.1f)), part_sys, 3, wold);
		enemigos.push_back(en);
		wold->addRigid(en);
	}
	TNT* tnt=new TNT(gScene, gPhysics, Vector3(0, 17, 15), CreateShape(PxBoxGeometry(2, 7, 2), gPhysics->createMaterial(0.1f, 0.1f, 0.1f)), part_sys);
	wold->addRigid(tnt);
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
