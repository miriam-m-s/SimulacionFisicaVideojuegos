#pragma once
#include"../Objetos/Particle.h"
class Interfaz
{
public:
	Interfaz(Camera* cam);
	void update(double t);

protected:
	Camera* cam_;
	Particle* part;
	Particle* parteabajo;
	Particle* punta;
};

