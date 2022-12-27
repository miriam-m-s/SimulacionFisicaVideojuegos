#include "plataforma.h"


plataforma::plataforma(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, Vector4 color, WorldManager* wold, ParticleSys* part) :ParticleRigidStatic(gScene, gPhysics, pos, shape, color),wold_(wold),part(part)
{
	part->createParticles(getRigid()->getGlobalPose().p, TipoParticles::Vient);
	wold_->generaFuerzas(TipoFuerzasF::Viento);
}

void plataforma::onCollision(PhsiscsPart* name1)
{
	
}
