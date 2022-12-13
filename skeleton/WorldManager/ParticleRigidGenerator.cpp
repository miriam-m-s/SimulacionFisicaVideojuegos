#include "ParticleRigidGenerator.h"
GausseanParticleGenF::GausseanParticleGenF(ParticleRigid* partmodel, Vector3 pos, Vector3 vel, Vector3 dev_pos, Vector3 dev_vel, double gen_prob, int num)
{
	_model = partmodel;
	_mean_pos = pos;
	_main_vel = vel;
	std_dev_pos = dev_pos;
	std_dev_vel = dev_vel;
	generation_probability = gen_prob;
	num_particles = num;
	
	color = partmodel->getRenderItem()->color;

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

std::list<ParticleRigid*> GausseanParticleGenF::generateParticles(PxScene* gScene, PxPhysics* gPhysics)
{
	//porque la campana de gauss es una distrubicion normal
	std::list<ParticleRigid*>particle;
	std::default_random_engine eng(rd());

	for (int i = 0; i < num_particles; i++) {
		if (distr(eng) < generation_probability) {
			Vector3 ppos;
			if (changepos) {
				ppos = _mean_pos;
			}
			else ppos = Vector3(x(gen), y(gen), z(gen));
			Vector3 vel(velx(gen), vely(gen), velz(gen));
			if (random_color)
				color = { float(distr(eng)),float(distr(eng)),float(distr(eng)),1 };
			ParticleRigid* part = new ParticleRigid(gScene, gPhysics, ppos, _model->getRenderItem()->shape,vel,color);
			part->setmass(_model->getRigid()->getMass());
			double time = _model->getTimeVida();
			if (time != 0)part->settimeVida(time);
			part->setName(_model->getName());
			particle.push_back(part);
		}

	}
	return particle;
}