#include <iostream>
#include "Particle.h"



Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 acel, float dampin, float radius, float masa, double timevida, Vector4 coloring, bool visible) :vel(Vel), acel_(acel), damp_(dampin), masa_(masa), livetime_(timevida), color(coloring), radius(radius), visible(visible)
{
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	if (visible) {
		renderitem = new RenderItem(CreateShape(physx::PxSphereGeometry(radius)), &pose, color);
	}
	restavida_ = livetime_;
	if (masa > 0) {
		inversemasa_ = (1 / masa_);
	}
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

	if (restavida_ <= 0) {
		alive = false;
	}
}

void Particle::integrate(double t)
{
	if ((1/masa_) <= 0.0f) return;
	pose.p = pose.p + vel * t;
	vel = vel * pow(damp_, t) + acel_ * t;

	cambiarcolor();
	restavida_ -= t;
	partlifetime();

	Vector3 totalAcceleration = acel_;
	totalAcceleration += force * inversemasa_;
	// Update linear
	vel += totalAcceleration * t;

	// Impose drag  (damping)
	vel *= powf(damp_, t);
	clearForce();

}

void Particle::clearForce()
{
}

void Particle::addForce(const Vector3& f)
{
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
