#pragma once
#include "../WorldManager/ParticleRigid.h"
#include <string>
enum TipoBalas {
    Bala, Laser, Balacanyon
};
class TipoBala {
public:
    TipoBala(TipoBalas s);
    float density = 0;
    float speed = 0;
    float radius = 0;

    
};

class Proyectil : public ParticleRigid
{
public:
   
    Proyectil(TipoBala s, Vector3 Pos, Vector3 dir, PxScene* gScene, PxPhysics* gPhysics);
    virtual void onCollision(PhsiscsPart* name1)override;

};

