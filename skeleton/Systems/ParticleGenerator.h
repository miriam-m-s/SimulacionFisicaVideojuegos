#pragma once
#include"../Objetos/Particle.h"
#include<list>
#include<string>
#include <random>
#include <cmath>
class ParticleGenerator
{
public:
    ParticleGenerator(){};
    
	virtual std::list<Particle*>generateParticles()=0;
    
protected:
    Vector3 _mean_pos;
    Vector3 _main_vel;
    double iMass_;
    double generation_probability;
    int num_particles;
    std::string name;
    Particle* _model;

};

class GausseanParticleGen :public ParticleGenerator
{
    public:
    GausseanParticleGen(Vector3 pos, Vector3 vel, Vector3 dev_pos, Vector3 dev_vel,double gen_prob,int num);
    virtual std::list<Particle*>generateParticles();
protected:
    Vector3 std_dev_pos, std_dev_vel;
    double std_dev_t;
};

