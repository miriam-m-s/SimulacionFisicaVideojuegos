#include "Interfaz.h"

Interfaz::Interfaz(Camera* cam):cam_(cam)
{
	part= new Particle(cam_->getTransform().p+ GetCamera()->getDir() , {0,0,0}, {0,0,0}, 0, 0.1, 0,2, {0,0,1,1}, TRUE, BOX);
	part->setInfiniteVida(true);
}

void Interfaz::update(double t)
{
	part->setPos(cam_->getTransform().p + GetCamera()->getDir() );
}
