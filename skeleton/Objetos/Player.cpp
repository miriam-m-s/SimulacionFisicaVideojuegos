#include "Player.h"
#include <iostream>

Player::Player(PxScene* gScene, PxPhysics* gPhysics,int vidas, Interfaz* inter_):ParticleRigid(gScene, gPhysics, GetCamera()->getInit(), CreateShape(PxSphereGeometry(5)), { 0,0,0 }, { 0,0,0,0 }, 10000),vidas_(vidas),inter(inter_)
{
	setInfiniteVida(true);
	setName("player");
	getRigid()->setLinearDamping(1.0f);
	getRigid()->setMass(50.0f);
	getRigid()->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y | PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);
	
}

void Player::onCollision(PhsiscsPart* name1)
{
	if (name1->getName() == "Muerte") {
		vidas_ = 0;
		
	}
	if (name1->getName() == "balaenemy") {
		inter->restavida();
		vidas_--;
		if (vidas_ == 0) {

			GetCamera()->setEye(GetCamera()->getPosIni());
			inter->restart();
			
		}
	
	}
}

void Player::integrate(double t)
{
	suelo = false;
}
