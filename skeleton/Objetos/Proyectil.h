#pragma once
#include "Particle.h"
#include <string>

enum TipoBalas{
    Bala,Laser,Balacanyon
};
class Proyectil :
    public Particle
{
public:
    Proyectil(Vector3 Pos, Vector3 Vel, Vector3 acel, float dampin,float radius,float masa);
    Proyectil(TipoBalas s, Vector3 Pos, Vector3 dir);
   
   
    

   
   
};

