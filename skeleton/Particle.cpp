#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel):vel(Vel)
{
	pose.p = Pos;
	
	renderitem = new RenderItem(CreateShape(physx::PxSphereGeometry(10)),&pose, Vector4(1,0,1,1));
}

Particle::~Particle()
{
	delete renderitem;
}

void Particle::integrate(double t)
{
	pose.p = pose.p + vel * t;
}
