#pragma once
#include<map>
#include "ForceGenarator.h"
typedef std::pair<ForceGenerator*, Particle*> FRPair;
class ParticleForceRegistry:public std::multimap<ForceGenerator*,Particle*>
{
	public:
		void updateForces(double duration) {
			for (auto it = begin(); it != end(); it++) {
				it->first->updateForce(it->second, duration);
			}
		}
		void addRegistry(ForceGenerator* fg, Particle* p) {
			insert({ fg,p });
		}
		void deleteParticleRegistry(Particle* p) {
			for (auto it = begin(); it != end(); ) {
				if (it->second == p) {
					it = erase(it);
				}
				else it++;
			}
		}
		void deleteforce() {
			for (auto it = begin(); it != end(); ) {
					it = erase(it);
			}
		}
};

class ParticleForceRegistryPhis :public std::multimap<ForceGenerator*, ParticleRigid*>
{
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); it++) {
			it->first->updateForce(it->second, duration);
		}
	}
	void addRegistry(ForceGenerator* fg, ParticleRigid* p) {
		insert({ fg,p });
	}
	void deleteParticleRegistry(ParticleRigid* p) {
		for (auto it = begin(); it != end(); ) {
			if (it->second == p) {
				it = erase(it);
			}
			else it++;
		}
	}
	void deleteforce() {
		for (auto it = begin(); it != end(); ) {
			it = erase(it);
		}
	}
};

