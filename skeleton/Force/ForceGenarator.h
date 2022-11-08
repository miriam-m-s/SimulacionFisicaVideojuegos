
#include"../Objetos/Particle.h"
#include<list>
#include<random>
class ForceGenerator {
public:
	virtual void updateForce(Particle* particle, double duration) {
	}
	std::string _name;
	double t = -1e-10;
};