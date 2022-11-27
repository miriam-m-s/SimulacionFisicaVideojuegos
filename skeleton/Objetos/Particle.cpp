#include <iostream>
#include "Particle.h"



Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 acel, float dampin, float masa, double timevida, Vector4 coloring, bool visible, double ancho, double largo, double alto)
	:vel(Vel), acel_(acel), damp_(dampin), masa_(masa), livetime_(timevida), color(coloring), visible(visible)
{
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderitem = new RenderItem(CreateShape(physx::PxBoxGeometry(ancho, alto, largo)), &pose, color);
	restavida_ = livetime_;
	if (masa > 0) {
		inversemasa_ = (1 / masa_);
	}
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 acel, float dampin, float radius, float masa, double timevida, Vector4 coloring, bool visible, FormaParticle S) :
	vel(Vel), acel_(acel), damp_(dampin), masa_(masa), livetime_(timevida), color(coloring), radius(radius), visible(visible)
{
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	if (visible) {
		if(S==SPHERE)
		renderitem = new RenderItem(CreateShape(physx::PxSphereGeometry(radius)), &pose, color);
		else if(S == PLANE)
			renderitem = new RenderItem(CreateShape(physx::PxPlaneGeometry()), &pose, color);
		else if (S == BOX)
			renderitem = new RenderItem(CreateShape(physx::PxBoxGeometry(radius,radius,radius)), &pose, color);
	}

	restavida_ = livetime_;
	if (masa > 0) {
		inversemasa_ = (1 / masa_);
	}
}


void Particle::addForce(const Vector3& f) {
	force += f; 
}

Particle::~Particle()
{
	DeregisterRenderItem(renderitem);
}
void Particle::setpartcle(Vector3 Pos, Vector3 Vel, Vector3 acel, float dampin, float radius, float masa, double time)
{
	vel = Vel;
	acel_ = acel;
	damp_ = dampin;
	masa_ = masa;
	if (masa > 0) {
		inversemasa_ = (1 / masa_);
	}
	livetime_ = time;
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	color = Vector4(1, 0, 1, 1);
	renderitem = new RenderItem(CreateShape(physx::PxSphereGeometry(radius)), &pose, color);

	//RegisterRenderItem(renderitem);
}
void Particle::partlifetime() {

	if (!infinitevida&&restavida_ <= 0) {
		alive = false;
	}
}

void Particle::integrate(double t)
{
	if ((inversemasa_) <= 0.0f) return;
	cambiarcolor();
	restavida_ -= t;
	partlifetime();
	if (euelerexplicit) {
		pose.p = pose.p + vel * t;

		Vector3 totalAcceleration = acel_;
		totalAcceleration += force * inversemasa_;
		// Update linear
		vel = vel * pow(damp_, t) + totalAcceleration * t;
	}
	else {
	

		Vector3 totalAcceleration = acel_;
		totalAcceleration += force * inversemasa_;
		// Update linear
		vel = vel * pow(damp_, t) + totalAcceleration * t;
		pose.p = pose.p + vel * t;
	}
	
	clearForce();

}

void Particle::clearForce()
{
	force *= 0;
}



void Particle::cambiarcolor()
{
	if (changingcolor_) {
		if (fuego)
			color.y -= 0.0095;
		else {
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
		}

	}

	renderitem->color = color;

}
