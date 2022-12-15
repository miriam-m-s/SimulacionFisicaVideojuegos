#include "Proyectil.h"



TipoBala::TipoBala(TipoBalas s) {
	switch (s)
	{
	case Bala:
		speed = 300.f;
		radius = 2;
		density = 50;

		break;
	case Laser:
		speed = 100.f;
		radius = 1;
		density = 1;
		break;
	case Balacanyon:;
		speed = 50.f;
		radius = 4;
		density = 100000;
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
	settimeVida(10);
	setName("bala");
	
	
	
}
void Proyectil::onCollision(PhsiscsPart* name1)
{
	
		alive = false;
	
}

