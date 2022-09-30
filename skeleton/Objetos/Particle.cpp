#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 acel, float dampin,float radius,float masa):vel(Vel),acel_(acel),damp_(dampin),masa_(masa)
{
	startime = glutGet(GLUT_ELAPSED_TIME);
	pose = physx::PxTransform( Pos.x,Pos.y,Pos.z);
	color = Vector4(1, 0, 1, 1);
	renderitem = new RenderItem(CreateShape(physx::PxSphereGeometry(radius)), &pose, color);

	RegisterRenderItem(renderitem);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderitem);
}
void Particle::setpartcle(Vector3 Pos, Vector3 Vel, Vector3 acel, float dampin, float radius, float masa)
{
	vel = Vel;
	acel_ = acel;
	damp_ = dampin;
	masa_ = masa;
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	color = Vector4(1, 0, 1, 1);
	renderitem = new RenderItem(CreateShape(physx::PxSphereGeometry(radius)), &pose, color);

	RegisterRenderItem(renderitem);
}


void Particle::integrate(double t)
{
	pose.p = pose.p + vel * t;
	vel = vel * pow(damp_, t) + acel_ * t;
	
	cambiarcolor();

	if (glutGet(GLUT_ELAPSED_TIME) > startime + 5000 || pose.p.y < 0.0f) {
		alive = false;
	}
}

void Particle::cambiarcolor()
{
	if (i == 0) {
		if (!cambio) {
			color.x -= 0.0005;
			if (color.x <= 0.5) {
				color.x = 0; cambio = true;
			}
		}
		else {
			color.x += 0.0005;
			if (color.x >= 0.99) {
				color.x = 1; cambio = false;
				i++;

			}
		}
	}
	else if (i == 1) {
		if (!cambio) {
			color.y -= 0.0005;
			if (color.y <= 0.5) {
				color.y = 0; cambio = true;
			}
		}
		else {
			color.y += 0.0005;
			if (color.y >= 0.99) {
				color.y = 1; cambio = false;
				i++;
			}
		}
	}
	else {
		if (!cambio) {
			color.z -= 0.0005;
			if (color.z <= 0.5) {
				color.z = 0; cambio = true;
			}
		}
		else {
			color.z += 0.0005;
			if (color.z >= 0.99) {
				color.z = 1; cambio = false;
				i = 0;
			}
		}
	}
	renderitem->color = color;

}
