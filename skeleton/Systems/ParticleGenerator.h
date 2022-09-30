#pragma once
#include"../Objetos/Particle.h"
#include<list>
#include<string>
class ParticleGenerator
{
public:
    ParticleGenerator(){};
	virtual std::list<Particle*>generateParticles()=0;
    std::string name;

};

class GausseanParticleGen :public ParticleGenerator
{
    public:
    GausseanParticleGen(Vector3 pos, Vector3 vel, double iMass);
    virtual std::list<Particle*>generateParticles() = 0;

protected:
    Vector3 pos_;
    Vector3 vel_;
    double iMass_;
};

