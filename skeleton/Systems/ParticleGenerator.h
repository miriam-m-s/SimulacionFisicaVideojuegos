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
    std::random_device rd{};
    std::mt19937 gen{ rd() };
    double tiempo;

};

class GausseanParticleGen :public ParticleGenerator
{
    public:
    GausseanParticleGen() {}
    GausseanParticleGen(Vector3 pos, Vector3 vel, Vector3 dev_pos, Vector3 dev_vel,double gen_prob,int num,float seconds);
    virtual std::list<Particle*>generateParticles();
    void activateGravity() {
        gravity_ = !gravity_;
    }
protected:
    Vector3 std_dev_pos, std_dev_vel;
    double std_dev_t;

    bool gravity_=true;
    std::normal_distribution<>x;
    std::normal_distribution<>y;
    std::normal_distribution<>z;
    std::normal_distribution<>velx; std::normal_distribution<>vely; std::normal_distribution<>velz;
    std::uniform_real_distribution<double>distr;
    std::uniform_real_distribution<float>time;
};
class UniformParticleGenerator :public ParticleGenerator
{
public:
    UniformParticleGenerator() {}
    UniformParticleGenerator(Vector3 pos, Vector3 vel,Vector3 vel_widht, Vector3 pos_widht, double gen_prob, int num, float seconds);
    virtual std::list<Particle*>generateParticles();
protected:
    Vector3 _vel_width, std_pos_width;
    double std_dev_t;
    std::uniform_real_distribution<>x;
    std::uniform_real_distribution<>y;
    std::uniform_real_distribution<>z;
    std::uniform_real_distribution<>velx; std::uniform_real_distribution<>vely; std::uniform_real_distribution<>velz;
    std::uniform_real_distribution<double>distr;
    std::uniform_real_distribution<float>time;
};

