#include "ParticleGenerator.h"


GausseanParticleGen::GausseanParticleGen(Vector3 pos, Vector3 vel, Vector3 dev_pos, Vector3 dev_vel, double gen_prob, int num, float seconds)
{
	_mean_pos = pos;
	_main_vel = vel;
	std_dev_pos = dev_pos;
	std_dev_vel = dev_vel;
	generation_probability = gen_prob;
	num_particles = num;
	tiempo = seconds;
	color = { 0.6,0.7,0,1 };
	std::list<Particle*>particle;
	x = std::normal_distribution<>{ _mean_pos.x,std_dev_pos.x };
	y = std::normal_distribution<>{ _mean_pos.y,std_dev_pos.y };
	z = std::normal_distribution<>{ _mean_pos.z,std_dev_pos.z };

	//distribucion vel
	velx = std::normal_distribution<>{ _main_vel.x,std_dev_vel.x };
	vely = std::normal_distribution<>{ _main_vel.y,std_dev_vel.y };
	velz = std::normal_distribution<>{ _main_vel.z,std_dev_vel.z };


	//te d aun numero entre 0 1
	distr = std::uniform_real_distribution<double>(0, 1);

	//te d aun numero entre 0 1
	time = std::uniform_real_distribution<float>(0, tiempo);
}

GausseanParticleGen::GausseanParticleGen(Particle* partmodel, Vector3 pos, Vector3 vel, Vector3 dev_pos, Vector3 dev_vel, double gen_prob, int num)
{
	_model = partmodel->clone();
	_mean_pos = pos;
	_main_vel = vel;
	std_dev_pos = dev_pos;
	std_dev_vel = dev_vel;
	generation_probability = gen_prob;
	num_particles = num;
	radius = _model->getradius();
	color = { 0.6,0.7,0,1 };
	std::list<Particle*>particle;
	x = std::normal_distribution<>{ _mean_pos.x,std_dev_pos.x };
	y = std::normal_distribution<>{ _mean_pos.y,std_dev_pos.y };
	z = std::normal_distribution<>{ _mean_pos.z,std_dev_pos.z };

	//distribucion vel
	velx = std::normal_distribution<>{ _main_vel.x,std_dev_vel.x };
	vely = std::normal_distribution<>{ _main_vel.y,std_dev_vel.y };
	velz = std::normal_distribution<>{ _main_vel.z,std_dev_vel.z };


	//te d aun numero entre 0 1
	distr = std::uniform_real_distribution<double>(0, 1);

	
}

std::list<Particle*> GausseanParticleGen::generateParticles()
{
	//porque la campana de gauss es una distrubicion normal
	std::list<Particle*>particle;
	std::default_random_engine eng(rd());

	for (int i = 0; i < num_particles; i++) {
		if (distr(eng) < generation_probability) {
			Vector3 ppos(x(gen), y(gen), z(gen));
			Vector3 vel(velx(gen), vely(gen), velz(gen));
			if (random_color)
				color = { float(distr(eng)),float(distr(eng)),float(distr(eng)),1 };
			Particle* part;
			if (_model != nullptr) {
				part = new Particle(_mean_pos, vel, { gravity_.x,gravity_.y,gravity_.x }, _model->getdamp(), radius, 0.5f, _model->gettime(), _model->getcolor(),true);
			}
			else {
				 part = new Particle(ppos, vel, { gravity_.x,gravity_.y,gravity_.x }, 0.99, radius, 0.5f, (time(eng)), color,true);
			}
			
			if (changecolor) {
				part->changecolors(true);
				if (fuego) {
					part->colorfuego(true);
				}
			}	
			else part->changecolors(false);
			particle.push_back(part);
		}

	}
	return particle;
}
UniformParticleGenerator::UniformParticleGenerator(Vector3 pos, Vector3 vel,Particle* partmodel, Vector3 vel_widht, Vector3 pos_widht, double gen_prob, int num)
{
	_model =partmodel->clone();
	_mean_pos = pos;
	_main_vel = vel;
	_vel_width = vel_widht;
	std_pos_width = pos_widht;
	generation_probability = gen_prob;
	num_particles = num;
	tiempo = partmodel->gettime();

	std::list<Particle*>particle;
	x = std::uniform_real_distribution<>{ _mean_pos.x - (pos_widht.x / 2),_mean_pos.x + (pos_widht.x / 2) };
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
UniformParticleGenerator::UniformParticleGenerator(Vector3 pos, Vector3 vel, Vector3 vel_widht, Vector3 pos_widht, double gen_prob, int num, float seconds)
{
	_model = nullptr;
	_mean_pos = pos;
	_main_vel = vel;
	_vel_width = vel_widht;
	std_pos_width = pos_widht;
	generation_probability = gen_prob;
	num_particles = num;
	tiempo = seconds;

	std::list<Particle*>particle;
	x = std::uniform_real_distribution<>{ _mean_pos.x - (pos_widht.x / 2),_mean_pos.x + (pos_widht.x / 2) };
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
			if (random_color)
				color = { float(distr(eng)),float(distr(eng)),float(distr(eng)),1 };
			Particle* part;
			if (_model == nullptr) {
				part = new Particle(ppos, vel, { gravity_.x,gravity_.y,gravity_.z }, 0.99, radius, 0.5f, (time(eng)), color,true);
			}
			else {
				part = new Particle(ppos, vel, _model->getgravity(), _model->getdamp(), _model->getradius(), 0.5, _model->gettime(), _model->getcolor(),true);
				
			}
			//part->changecolors(true);
			part->changecolors(false);
			particle.push_back(part);
		}

	}
	return particle;
}
