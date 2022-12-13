#pragma once
#include"ParticleRigid.h"
#include<list>
#include<string>
#include <random>
#include <cmath>
#include <PxPhysicsAPI.h>
using namespace physx;

using namespace std;
class ParticleRigidGenerator
{
public:
    ParticleRigidGenerator() : random_color(false), color(0, 0.7, 0.8, 0.4) {};
    ~ParticleRigidGenerator() {
      
        
    }
    virtual std::list<ParticleRigid*>generateParticles(PxScene* gScene, PxPhysics* gPhysics) = 0;
  
    void setColor(Vector4 Color) {
        color = Color;
    }

    void setRadius(float r) {
        radius = r;
    }
   
    void setPos(Vector3 pos) {
        _mean_pos = pos;
        changepos = true;
    }
    void setrandomColor(bool s) {
        random_color = true;
    }
  
protected:
    bool changepos = false;
    Vector4 color;
    bool random_color = false;
    float radius = 1.0f;
    Vector3 _mean_pos;
    Vector3 _main_vel;
    double iMass_;
    double generation_probability;
    int num_particles;
    ParticleRigid* _model = nullptr;
    std::random_device rd{};
    std::mt19937 gen{ rd() };
    double tiempo;
 
};

class GausseanParticleGenF :public ParticleRigidGenerator
{
public:
    GausseanParticleGenF(){}
    GausseanParticleGenF(ParticleRigid* partmodel, Vector3 pos, Vector3 vel, Vector3 dev_pos, Vector3 dev_vel, double gen_prob, int num);
    virtual std::list<ParticleRigid*>generateParticles(PxScene* gScene, PxPhysics* gPhysics);



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
