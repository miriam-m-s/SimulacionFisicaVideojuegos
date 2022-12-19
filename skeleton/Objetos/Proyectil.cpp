#include "Proyectil.h"



TipoBala::TipoBala(TipoBalas s) {
	switch (s)
	{
	case Bala:
		speed = 300.f;
		radius = 0.5;
		density = 1;
		name = "bala";
		break;
	case Laser:
		speed = 100.f;
		radius = 0.1;
		density = 1;
		name = "bala";

		break;
	case Balacanyon:;
		speed = 50.f;
		radius = 1;
		density = 1;
		name = "bala";

		break;
	case BalaEnemy:
		speed = 300.f;
		radius = 0.5;
		density = 1;
		name = "balaenemy";


		break;
	default:
		break;
	}
}

Proyectil::Proyectil(TipoBala s, Vector3 Pos, Vector3 dir,PxScene* gScene, PxPhysics* gPhysics):ParticleRigid( gScene,gPhysics,  Pos, CreateShape(physx::PxSphereGeometry(s.radius)), dir.getNormalized()* s.speed, {1,1,1,1}, s.density)
{
	float grav=0;
	float speed=0;
	float dumping=0;
	float radius = 0;
	//getRigid()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION,true);

	settimeVida(10);
	setName(s.name);
	
	
	
}
void Proyectil::onCollision(PhsiscsPart* name1)
{
	
		alive = false;
	
}

