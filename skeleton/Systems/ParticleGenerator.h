#pragma once
#include"../Objetos/Particle.h"
#include<list>
#include<string>
#include <random>
#include <cmath>
class ParticleGenerator
{
public:
    ParticleGenerator():gravity_(0, -10, 0), random_color(false), color(0, 0.7, 0.8, 0.4) {};
    ~ParticleGenerator() {
        if(_model=nullptr)
        delete _model;
    }
	virtual std::list<Particle*>generateParticles()=0;
    void setGravity(Vector3 grav) {
        gravity_ = grav;
    }
    void setColor(Vector4 Color) {
        color = Color;
    }
    void setRandomColor(bool active) {
        random_color = active;
    }
    void setRadius(float r) {
        radius = r;
    }
    void setchangecolor(bool s) {
        changecolor = s;
    }
    void setfuego(bool s) {
        changecolor = s;
        fuego = s;
    }
    void setPos(Vector3 pos) {
        _mean_pos = pos;
        changepos = true;
    }
protected:
    bool changepos = false;
    Vector4 color;
    Vector3 gravity_;
    bool random_color=false;
    float radius = 1.0f;
    Vector3 _mean_pos;
    Vector3 _main_vel;
    double iMass_;
    double generation_probability;
    int num_particles;
    std::string name;
    Particle* _model=nullptr;
    std::random_device rd{};
    std::mt19937 gen{ rd() };
    double tiempo;
    bool changecolor=false;
    bool fuego=false;

};

class GausseanParticleGen :public ParticleGenerator
{
    public:
    GausseanParticleGen() {}
    ~GausseanParticleGen(){}
    GausseanParticleGen(Vector3 pos, Vector3 vel, Vector3 dev_pos, Vector3 dev_vel,double gen_prob,int num,float seconds);
    GausseanParticleGen(Particle* partmodel,Vector3 pos, Vector3 vel, Vector3 dev_pos, Vector3 dev_vel, double gen_prob, int num);
    virtual std::list<Particle*>generateParticles();
   


protected:
    Vector3 std_dev_pos, std_dev_vel;
    double std_dev_t;
   
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
    ~UniformParticleGenerator() {}
    UniformParticleGenerator(Vector3 pos, Vector3 vel, Particle* partmodel, Vector3 vel_widht, Vector3 pos_widht, double gen_prob, int num);
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

class CircleGenerator:public ParticleGenerator {
public:
    CircleGenerator( int vel, int num,Particle*model);
    virtual std::list<Particle*>generateParticles();
protected:
    int vel=10;
};
class SphereGenerator :public ParticleGenerator {
public:
    SphereGenerator(int vel, int num, Particle* model);
    virtual std::list<Particle*>generateParticles();
protected:
    int vel = 10;
};
class HeartGen :public ParticleGenerator {
public:
    HeartGen(int vel, int num, Particle* model);
    virtual std::list<Particle*>generateParticles();
protected:
    int vel = 10;
};