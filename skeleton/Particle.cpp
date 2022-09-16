#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel):vel(Vel)
{
	pose = physx::PxTransform( Pos.x,Pos.y,Pos.z);
	color = Vector4(1, 0, 1, 1);
	renderitem = new RenderItem(CreateShape(physx::PxSphereGeometry(10)), &pose, color);

	RegisterRenderItem(renderitem);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderitem);
} 

void Particle::integrate(double t)
{
	pose.p = pose.p + vel * t;
	
	if (color.y >= 0.90) {
		color.y = 0;
	}
	else {
		color.y += 0.01;
	}
	renderitem->color = color;
}
