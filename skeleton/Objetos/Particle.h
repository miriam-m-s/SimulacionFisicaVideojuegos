#pragma once
#include <math.h>
#include "../core.hpp"
#include "../RenderUtils.hpp"
enum FormaParticle {
	SPHERE,PLANE,BOX

};
class Particle
{
public:
	
	Particle(Vector3 Pos, Vector3 Vel, Vector3 acel, float dampin, float radius, float masa, double timevida, Vector4 coloring,bool visible,FormaParticle S=SPHERE);	
	Particle() {
		
	}
	~Particle();
	void setpartcle(Vector3 Pos, Vector3 Vel, Vector3 acel, float dampin, float radius, float masa,double timevida);
	void integrate(double t);
	
	Particle* clone() {
		return new Particle(pose.p,vel,acel_,damp_,radius,masa_, livetime_,color,visible);
	}
	double gettime() { return livetime_; }
	void clearForce();

	void addForce(const Vector3& f);

	bool active() {
		return alive;
	}
	void changecolors(bool s) {
		changingcolor_ = s;
	}
	Vector4 getcolor() {
		return color;
	}
	Vector3 getgravity() {
		return acel_;
	}
	Vector3 getvel() {
		return vel;
	}
	Vector3 getpos() {
		return pose.p;
	}
	float getradius() {
		return radius;
	}
	float getdamp() {
		return damp_;
	}
	void colorfuego(bool s) {
		fuego = s;
	}
	float inv_mass() {
		return inversemasa_;
	}
	float mass() {
		return masa_;
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
	float inversemasa_=1;
	bool alive = true;
	double livetime_;
	double restavida_;
	bool changingcolor_=false;
	bool fuego=false;
	bool visible=true;
	Vector3 force={0,0,0};
};

