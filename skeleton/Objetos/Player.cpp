#include "Player.h"
#include <iostream>

Player::Player(PxScene* gScene, PxPhysics* gPhysics,int vidas, Interfaz* inter_):ParticleRigid(gScene, gPhysics, GetCamera()->getTransform().p, CreateShape(PxSphereGeometry(5)), { 0,0,0 }, { 0,0,0,0 }, 10),vidas_(vidas),inter(inter_)
{
	setInfiniteVida(true);
	setName("player");
	getRigid()->setLinearDamping(1.0f);
	getRigid()->setMass(50.0f);
	getRigid()->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y | PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);
	
}

void Player::onCollision(PhsiscsPart* name1)
{
	if (name1->getName() == "Suelo") {
		suelo = true;
		
	}
	if (name1->getName() == "balaenemy") {
		inter->restavida();
		vidas_--;
		if (vidas_ == 0) {
			vidas_ = 3;
			inter->restart();
		}
	
	}
}

void Player::integrate(double t)
{
	suelo = false;
}
