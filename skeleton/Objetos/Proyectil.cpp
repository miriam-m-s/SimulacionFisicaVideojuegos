#include "Proyectil.h"

Proyectil::Proyectil(Vector3 Pos, Vector3 Vel, Vector3 acel, float dampin,float radius,float masa)
{

}

Proyectil::Proyectil(TipoBalas s, Vector3 Pos, Vector3 dir)
{
	float grav=0;
	float speed=0;
	float dumping=0;
	float radius = 0;
	switch (s)
	{
	case Bala:
		grav = -0.1f;
		speed = 300.f;
		dumping = 0.99;
		radius = 2;
		break;
	case Laser:
		grav = -0.01f;
		speed = 100.f;
		dumping = 0.99;
		radius = 1;
		break;
	case Balacanyon:
		grav = -9.8f;
		speed = 50.f;
		dumping = 0.99;
		radius = 4;
		break;

	default:
		break;
	}
	setpartcle(Pos, dir.getNormalized() * speed, { 0,grav,0 }, 0.99, radius, 5.0f);
	startime = glutGet(GLUT_ELAPSED_TIME);
}

void Proyectil::integrate(double t)
{
	pose.p = pose.p + vel * t;
	vel = vel * pow(damp_, t) + acel_ * t;

	cambiarcolor();
	if (glutGet(GLUT_ELAPSED_TIME) > startime + 5000||pose.p.y < 0.0f) {
		alive = false;
	}
}
