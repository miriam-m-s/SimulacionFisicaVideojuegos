#include "ParticleGenerator.h"


GausseanParticleGen::GausseanParticleGen(Vector3 pos, Vector3 vel, Vector3 dev_pos, Vector3 dev_vel, double gen_prob,int num)
{
	_mean_pos = pos;
	_main_vel = vel;
	std_dev_pos = dev_pos;
	std_dev_vel = dev_vel;
	generation_probability = gen_prob;
	num_particles = num;
}

std::list<Particle*> GausseanParticleGen::generateParticles()
{
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::list<Particle*>particle;
	std::normal_distribution<>x{ _mean_pos.x,std_dev_pos.x };
	std::normal_distribution<>y{ _mean_pos.y,std_dev_pos.y };
	std::normal_distribution<>z{ _mean_pos.z,std_dev_pos.z };

	//distribucion vel
	std::normal_distribution<>velx{ _main_vel.x,std_dev_vel.x };
	std::normal_distribution<>vely{ _main_vel.y,std_dev_vel.y };
	std::normal_distribution<>velz{ _main_vel.z,std_dev_vel.z };

	std::default_random_engine eng(rd());
	//te d aun numero entre 0 1
	std::uniform_real_distribution<double>distr(0, 1);

	//te d aun numero entre 0 1
	std::uniform_real_distribution<double>time(0, 5000);

	for (int i = 0; i < num_particles; i++) {
		if (distr(eng) < generation_probability) {
			Vector3 ppos(x(gen), y(gen), z(gen));
			Vector3 vel(velx(gen), vely(gen), velz(gen));
			Vector4 color = { float(distr(eng)),float(distr(eng)),float(distr(eng)),1 };
			Particle* part = new Particle(ppos, vel, { 0,0,0 }, 0.99, 1.0f, 0.5f,(time(eng)),color);
			part->changecolors(false);
			particle.push_back(part);
		}
		
	}
	return particle;
}
