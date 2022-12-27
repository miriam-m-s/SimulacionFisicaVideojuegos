#include "Enemy2.h"

Enemy2::Enemy2(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, ParticleSys* partSys, int vidas):ParticleRigid(gScene, gPhysics, pos,shape, { 0,0,0 }, { 0,0,0,0 }, 10),vidas_(vidas),partSys_(partSys)
{

}
void Enemy2:: integrate(double t) {

}