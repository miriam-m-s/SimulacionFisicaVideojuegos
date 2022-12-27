#include "Enemy2.h"

Enemy2::Enemy2(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, ParticleSys* partSys, int vidas):ParticleRigid(gScene, gPhysics, pos,shape, { 0,0,0 }, { 0.1,0.2,0.4,0 }, 10),vidas_(vidas),partSys_(partSys)
{
	srand(time(NULL));
	force = 10 + rand() % (5);
	name = "enemy";
	changecolor = (1 - render_->color.x) / vidas;
	part_dy->setLinearDamping(0.2);
}
void Enemy2:: integrate(double t) {
	if (player_ != nullptr) {
		Vector3 direction = player_->getRigid()->getGlobalPose().p - part_dy->getGlobalPose().p;
		Vector3 dir = { direction.x,0,direction.z };
		dir.normalize();
		part_dy->addForce(dir * force*10);
	}
	if (vidas_ <= 0) {
		partSys_->createParticles(getRigid()->getGlobalPose().p, TipoParticles::Sangre);
		alive = false;
	}
}
void Enemy2::getPLayer(ParticleRigid* part) {
	player_=part;
}

void Enemy2::onCollision(PhsiscsPart* name1)
{
	if (name1->getName() == "bala") {
		vidas_--;
		render_->color.x += 0.4;		
	}
}