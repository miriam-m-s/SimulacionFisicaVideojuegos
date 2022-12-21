#include "Enemy.h"
#include <iostream>

Enemy::Enemy(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, ParticleSys* partSys,int vidas,WorldManager*wolds):ParticleRigidStatic(gScene, gPhysics, pos, shape, { 0,1,0.4,1 }),partSys_(partSys),vidas(vidas),wold(wolds)
{
	
	setInfiniteVida(true);
	Vector4 color = render_->color;
	changecolor = (1 - color.x) / vidas;
	setName("enemy");
	
	distr = std::uniform_real_distribution<double>(0, 3);
	ojo1 = new Particle(pos+Vector3(-5,5,5), {0,0,0}, {0,0,0}, 0.8, 20, 0, {0,1,0.4,1}, true, CreateShape(PxSphereGeometry(3)));
	ojo1->setRot(getRigid()->getGlobalPose().q);
	ojo2= new Particle(pos + Vector3(5, 5, 5), { 0,0,0 }, { 0,0,0 }, 0.8, 20, 0, { 0,1,0.4,1 }, true, CreateShape(PxSphereGeometry(3)));
	ojo2->setRot(getRigid()->getGlobalPose().q);
}

Enemy::~Enemy()
{
	delete ojo1;
	delete ojo2;
	/*DeregisterRenderItem(render_);
	delete render_;*/
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
		auto color = ojo1->getcolor();
		color.x += changecolor;
		ojo1->setColor(color);
		time /= 2;
	}
}

void Enemy::integrate(double t)
{
	timer += t;
	if (vidas <= 0) {
		partSys_->createBloodExplosion(getRigid()->getGlobalPose().p);
		alive = false;
	}
	std::default_random_engine eng(rd());
	if (timer-distr(rd) >= time+t) {
		Vector3 vec = ojo1->getpos() - ojo2->getpos();
		vec.getNormalized();
		Vector3 normal = vec.cross({0,1,0}).getNormalized();
		std::cout << "hola";
		wold->createBullet(TipoBala(BalaEnemy), (getRigid()->getGlobalPose().p+Vector3(0,0,20)), normal*-1);
		timer = t;
	}
	
}
