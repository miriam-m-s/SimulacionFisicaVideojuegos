#pragma once
#include"../Objetos/Particle.h"
#include<list>
#include<string>
#include <random>
#include <cmath>
#include "../Force/ForceGenarator.h"
#include "../Force/GravityForceGenerator.h"
#include "../Force/ParticleDragGenerator.h"
#include "../Force/ExplosionGenerator.h"
using namespace std;
class ParticleGenerator
{
public:
    ParticleGenerator():gravity_(0, 0, 0), random_color(false), color(0, 0.7, 0.8, 0.4) {};
    ~ParticleGenerator() {
        if(_model!=nullptr)
        delete _model;
        if (gravitygen != nullptr) {
            delete gravitygen;
        }
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
    void setrandommass(bool h) {
        randommass_ = h;
    }
    float getrandommass(int maxmass);
    void setPos(Vector3 pos) {
        _mean_pos = pos;
        changepos = true;
    }
    int addForceGenerator(ForceGenerator* force) {
        GravityForceGenerator* grav= dynamic_cast<GravityForceGenerator*>(force);
        if (grav != nullptr) {
            gravitygen = grav;
            fuerzas.push_back(gravitygen);
            return -1;
        }
        WindGenerator* wind = dynamic_cast<WindGenerator*>(force);
        if (wind != nullptr) {
            windgen = wind;
            fuerzas.push_back(wind);
            return -1;
        }
        Torbellino* torb= dynamic_cast<Torbellino*>(force);
        if (torb != nullptr) {
            torbelline = torb;
            fuerzas.push_back(torbelline);
            return -1;
        }
        ExplosionGenerator *exp= dynamic_cast<ExplosionGenerator*>(force);
        if (exp != nullptr) {
            explosion = exp;
            fuerzas.push_back(explosion);
            return -1;
        }
        return 0;
    }
    std::vector<ForceGenerator*> returnforce() {
        return fuerzas;
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
    GravityForceGenerator* gravitygen=nullptr;
    WindGenerator * windgen = nullptr;
    Torbellino* torbelline = nullptr;
    ExplosionGenerator* explosion=nullptr;
    float mass = 5;
    vector<ForceGenerator*>fuerzas;
    bool randommass_=false;
    std::uniform_real_distribution<float>massdist_;
};

class GausseanParticleGen :public ParticleGenerator
{
    public:
    GausseanParticleGen() {}
    GausseanParticleGen(Vector3 pos, Vector3 vel, Vector3 dev_pos, Vector3 dev_vel,double gen_prob,int num,float seconds,float mass=5);
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
    UniformParticleGenerator(Vector3 pos, Vector3 vel, Particle* partmodel, Vector3 vel_widht, Vector3 pos_widht, double gen_prob, int num);
    UniformParticleGenerator(Vector3 pos, Vector3 vel,Vector3 vel_widht, Vector3 pos_widht, double gen_prob, int num, float seconds, float mass_ = 5);
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
//class HeartGen :public ParticleGenerator {
//public:
//    HeartGen(int vel, int num, Particle* model);
//    virtual std::list<Particle*>generateParticles();
//protected:
//    int vel = 10;
//};