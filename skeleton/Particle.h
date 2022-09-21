#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
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
};

