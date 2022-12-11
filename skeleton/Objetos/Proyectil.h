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
    Proyectil();
    Proyectil(TipoBalas s, Vector3 Pos, Vector3 dir);
   
protected:
    void partlifetime()override;
    

   
   
};

