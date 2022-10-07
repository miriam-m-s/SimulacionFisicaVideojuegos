#pragma once
#include <math.h>
#include "../core.hpp"
#include "../RenderUtils.hpp"
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 acel,float dampin,float radius,float masa,double timevida,Vector4 coloring);
	Particle() {
		startime = float(glutGet(GLUT_ELAPSED_TIME));
	}
	~Particle();
	void setpartcle(Vector3 Pos, Vector3 Vel, Vector3 acel, float dampin, float radius, float masa,double timevida);
	void integrate(double t);
	

	bool active() {
		return alive;
	}
	void changecolors(bool s) {
		changingcolor_ = s;
	}

protected:
	virtual void partlifetime();
	void cambiarcolor();
	Vector3 vel={0,0,0};
	physx::PxTransform pose;
	RenderItem* renderitem;
	Vector4 color;
	bool cambio = false;
	bool changecolor = false;
	int i = 0;
	Vector3 acel_={0,0,0};
	float damp_=0;
	float radius=0;
	float masa_=0;
	bool alive = true;
	double startime;
	double livetime_;
	bool changingcolor_=true;
};

