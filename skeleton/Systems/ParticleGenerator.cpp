#include "ParticleGenerator.h"


GausseanParticleGen::GausseanParticleGen(Vector3 pos, Vector3 vel, Vector3 dev_pos, Vector3 dev_vel, double gen_prob,int num,float seconds)
{
	_mean_pos = pos;
	_main_vel = vel;
	std_dev_pos = dev_pos;
	std_dev_vel = dev_vel;
	generation_probability = gen_prob;
	num_particles = num;
	tiempo = seconds;
	
	std::list<Particle*>particle;
	x = std::normal_distribution<>{ _mean_pos.x,std_dev_pos.x };
	y= std::normal_distribution<>{ _mean_pos.y,std_dev_pos.y };
	z= std::normal_distribution<>{ _mean_pos.z,std_dev_pos.z };

	//distribucion vel
	velx= std::normal_distribution<>{ _main_vel.x,std_dev_vel.x };
	vely= std::normal_distribution<>{ _main_vel.y,std_dev_vel.y };
	velz= std::normal_distribution<>{ _main_vel.z,std_dev_vel.z };


	//te d aun numero entre 0 1
	distr= std::uniform_real_distribution<double>(0, 1);

	//te d aun numero entre 0 1
	time= std::uniform_real_distribution<float>(0, tiempo);
}

std::list<Particle*> GausseanParticleGen::generateParticles()
{
	//porque la campana de gauss es una distrubicion normal
	std::list<Particle*>particle;
	std::default_random_engine eng(rd());
	float grav = -10;
	if (!gravity_)grav = 0;
	for (int i = 0; i < num_particles; i++) {
		if (distr(eng) < generation_probability) {
			Vector3 ppos(x(gen), y(gen), z(gen));
			Vector3 vel(velx(gen), vely(gen), velz(gen));
			Vector4 color = { float(distr(eng)),float(distr(eng)),float(distr(eng)),1 };
			Particle* part = new Particle(ppos, vel, { 0,grav,0 }, 0.99, 1.0f, 0.5f,(time(eng)),color);
			part->changecolors(false);
			particle.push_back(part);
		}
		
	}
	return particle;
}
UniformParticleGenerator::UniformParticleGenerator(Vector3 pos, Vector3 vel, Vector3 vel_widht, Vector3 pos_widht, double gen_prob, int num, float seconds)
{
	_mean_pos = pos;
	_main_vel = vel;
	_vel_width = vel_widht;
	std_pos_width = pos_widht;
	generation_probability = gen_prob;
	num_particles = num;
	tiempo = seconds;

	std::list<Particle*>particle;
	x = std::uniform_real_distribution<>{ _mean_pos.x- (pos_widht.x/2),_mean_pos.x + (pos_widht.x / 2) };
	y = std::uniform_real_distribution<>{ _mean_pos.y - (pos_widht.y / 2),_mean_pos.y + (pos_widht.y / 2) };
	z = std::uniform_real_distribution<>{ _mean_pos.z - (pos_widht.z / 2),_mean_pos.z + (pos_widht.z / 2) };

	//distribucion vel
	velx = std::uniform_real_distribution<>{ _main_vel.x - (vel_widht.x / 2),_main_vel.x + (vel_widht.x / 2) };
	vely = std::uniform_real_distribution<>{ _main_vel.y - (vel_widht.y / 2),_main_vel.y + (vel_widht.y / 2) };
	velz = std::uniform_real_distribution<>{ _main_vel.z - (vel_widht.z / 2),_main_vel.z + (vel_widht.z / 2) };


	//te d aun numero entre 0 1
	distr = std::uniform_real_distribution<double>(0, 1);

	//te d aun numero entre 0 1
	time = std::uniform_real_distribution<float>(0, tiempo);
}
std::list<Particle*> UniformParticleGenerator::generateParticles()
{
	//porque la campana de gauss es una distrubicion normal
	std::list<Particle*>particle;
	std::default_random_engine eng(rd());
	float grav = -10;
	
	for (int i = 0; i < num_particles; i++) {
		if (distr(eng) < generation_probability) {
			Vector3 ppos(x(gen), y(gen), z(gen));
			Vector3 vel(velx(gen), vely(gen), velz(gen));
			Vector4 color = {0,0.7,0.8,1 };
			Particle* part = new Particle(ppos, vel, { 0,-10,0 }, 0.99,0.1f, 0.5f, (time(eng)), color);
			part->changecolors(false);
			particle.push_back(part);
		}

	}
	return particle;
}
