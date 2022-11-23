#include "AnchoredSpringFG.h"


AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const Vector3& anchorpos):SpringForceGenerator(k, resting, nullptr)
{
	_other = new Particle({ 0,0,0 }, { 0,0,0 }, { 0, 0,0 }, 0.85, 4,1e6, 1000, { 1,1,0,1 }, true,FormaParticle(BOX));
	/*_other=new Particle()*/
}

AnchoredSpringFG::~AnchoredSpringFG()
{
	delete _other;
}
