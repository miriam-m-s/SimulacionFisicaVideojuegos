#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <math.h>
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 acel,float dampin );
	~Particle();
	void integrate(double t);
	void cambiarcolor();
private:
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderitem;
	Vector4 color;
	bool cambio = false;
	bool changecolor = false;
	int i = 0;
	Vector3 acel_;
	float damp_;
};

