#include "Interfaz.h"

Interfaz::Interfaz(Camera* cam):cam_(cam)
{
	part= new Particle(cam_->getTransform().p+ GetCamera()->getDir() , {0,0,0}, {0,0,0}, 0, 0,2, {0,0,1,1}, TRUE, CreateShape(physx::PxBoxGeometry(0.1, 0.1, 0.5)));
	part->setInfiniteVida(true);
	parteabajo = new Particle(cam_->getTransform().p + GetCamera()->getDir(), { 0,0,0 }, { 0,0,0 }, 0, 0, 2, { 1,1,0,1 }, TRUE, CreateShape(physx::PxBoxGeometry(0.2, 0.1, 0.1)));
	parteabajo->setInfiniteVida(true);
	punta = new Particle(cam_->getTransform().p + GetCamera()->getDir(), { 0,0,0 }, { 0,0,0 }, 0, 0, 2, { 0,0,0,1 }, TRUE, CreateShape(physx::PxBoxGeometry(0.13, 0.13, 0.13)));
	punta->setInfiniteVida(true);
}

void Interfaz::update(double t)
{
	Vector3 pos = { cam_->getDir().x,0,cam_->getDir().z };
	pos.getNormalized();
	Vector3 transladado = { -cam_->getDir().z,0,cam_->getDir().x };
	transladado.getNormalized();
	Vector3 normal=transladado.cross(GetCamera()->getDir()).getNormalized();
	part->setPos(cam_->getTransform().p + GetCamera()->getDir()*2+normal*-0.7);

	physx::PxQuat q = { cam_->getTransform().q.x ,cam_->getTransform().q.y,cam_->getTransform().q.z,cam_->getTransform().q.w };
	//q.rotate({ 20, 0, 0 });
	parteabajo->setPos(cam_->getTransform().p + GetCamera()->getDir() * 2 + normal * -1);
	part->setRot(q);
	parteabajo->setRot(q);
	//q.rotate({ 20, 0, 0 });
	punta->setPos(cam_->getTransform().p + GetCamera()->getDir() * 2.5 + normal * -0.7);
	punta->setRot(q);
	//parteabajo->setRot(q);
	
}
