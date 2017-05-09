#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include <time.h>
#include <stdlib.h>

#define MAX_ACTIVE_PARTICLES 1000

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint initialpos;
	iPoint speed;
	iPoint size;
	bool active = true; // if active is true, particles have collider, if it is false they don't
	Uint32 bullettype = 0;
	Uint32 born = 0;
	Uint32 life = 0;
	int spritesheet = 0; //What spritesheet does the shot belong to
	bool fx_played = false;
	int position_respect_player;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();

	void AddPointsP1()
	{
		App->player->score += 60;
	}

	void AddPointsP2()
	{
		App->player2->score += 60;
	}

	void displace() //Displaces the particle
	{
		if (position.x == initialpos.x)
		{
			position.x += rand() % 2 + 5;
			position.y += rand() % 2 + 5;
		}

		else if (position.x >= initialpos.x)
		{
			position.x -= rand() % 5 + 5;
			position.y -= rand() % 5 + 5;
		}

		else if (position.x <= initialpos.x)
		{
			position.x += rand() % 5 + 5;
			position.y += rand() % 5 + 5;
		}

		if (collider != nullptr)
		{
			collider->SetPos(position.x, position.y);
		}
	}
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Init();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void MoveParticlesRight(bool);
	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, int bullettype = 0, int speed_x = 0, int speed_y = 0, Uint32 delay = 0, bool multipleshot = false, int damage = 0, bool pactive = true, int position_respect_player = 0);
	void EraseParticles();
private:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics1 = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];

public:
	Particle laser;
	Particle laser2;
	Particle double_shot;
	Particle triple_shot;
	Particle quad_shot;
	Particle enemyshot;
	Particle explosion;
	Particle hitspark;
	Particle bomb;
	Particle bombexplosion;
	Particle bombexplosion2;
};

#endif // __MODULEPARTICLES_H__