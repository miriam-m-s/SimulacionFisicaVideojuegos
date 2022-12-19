#pragma once
#include"../Objetos/Particle.h"
#include <list>
class Interfaz
{
public:
	Interfaz(Camera* cam);
	void update(double t);
	void restavida();

protected:
	Camera* cam_;
	Particle* part;
	Particle* parteabajo;
	Particle* punta;
	std::list<Particle*>vidas;
	
};

