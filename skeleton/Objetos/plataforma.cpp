#include "plataforma.h"


plataforma::plataforma(PxScene* gScene, PxPhysics* gPhysics, Vector3 pos, PxShape* shape, Vector4 color, WorldManager* wold, ParticleSys* part) :ParticleRigidStatic(gScene, gPhysics, pos, shape, color),wold_(wold),part(part)
{
	part->createParticles(getRigid()->getGlobalPose().p, TipoParticles::Vient);
}

void plataforma::onCollision(PhsiscsPart* name1)
{
	if (name1->getName() == "player") {
		wold_->generaFuerzas(TipoFuerzasF::Viento);
	}
}
