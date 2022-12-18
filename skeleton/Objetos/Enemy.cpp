#include "Enemy.h"

Enemy::Enemy(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, ParticleSys* partSys,int vidas) :ParticleRigid(gScene, gPhysics, pos, shape,{0,0,0}, {0.2,0,0.2,1}, 10000000),partSys_(partSys),vidas(vidas)
{
	setInfiniteVida(true);
	Vector4 color = render_->color;
	changecolor = (1 - color.x) / vidas;
	setName("enemy");
}

void Enemy::GetPlayer(ParticleRigid* player)
{
	player = player_;
}

void Enemy::onCollision(PhsiscsPart* name1)
{
	if (name1->getName() == "bala") {
		vidas--;
		render_->color.x += changecolor;
	}
}

void Enemy::integrate(double t)
{
	if (vidas <= 0) {
		partSys_->createBloodExplosion(part_dy->getGlobalPose().p);
		alive = false;
	}
}
