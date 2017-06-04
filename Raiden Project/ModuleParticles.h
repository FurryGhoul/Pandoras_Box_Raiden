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

#define MAX_ACTIVE_PARTICLES 10000
struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	fPoint position;
	iPoint speed;
	iPoint size;
	bool active = true; // if active is true, particles have collider, if it is false they don't
	Uint32 bullettype = 0;
	bool delay; //Bool to know if the particle has to have delay
	bool time_got = false; //Bool to take initial time just once
	int initial_time;
	Uint32 born = 0;
	Uint32 life = 0;
	int spritesheet = 0; //What spritesheet does the shot belong to
	bool fx_played = false;
	int position_respect_player;
	int displacements = 0;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();

	void AddPointsP1()
	{
		App->player->score += 20;
	}

	void AddPointsP2()
	{
		App->player2->score += 20;
	}

	void displace() //Displaces the particle
	{
		if (displacements % 2 == 0)
		{
			position.x += rand() % 5 + 5;
			position.y += rand() % 5 + 5;
		}

		else
		{
			position.x -= rand() % 5 + 5;
			position.y -= rand() % 5 + 5;
		}

		if (collider != nullptr)
		{
			collider->SetPos(position.x, position.y);
		}
		
		displacements++;
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
	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, int bullettype = 0, int speed_x = 0, int speed_y = 0, bool delay = 0, bool multipleshot = false, int damage = 0, bool pactive = true, int position_respect_player = 0);
	void EraseParticles();
private:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics1 = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];

public:
	Particle laser;
	Particle laser2;
	Particle final_laser;
	Particle double_shot;
	Particle triple_shot;
	Particle quad_shot;
	Particle quad_shot_right1;
	Particle quad_shot_right2;
	Particle quad_shot_left1;
	Particle quad_shot_left2;
	Particle enemyshot;
	Particle explosion;
	Particle hitspark;
	Particle bomb;
	Particle bombexplosion;
	Particle bombexplosion2;
	Particle bonusmedium_explosion;
	Particle longmegatank_laser;
	Particle player_light_missile;
	Particle player_mid_missiles;
	Particle heavy_missiles;
	Particle player_explosion;
	Particle shiptank_explosion;
};

#endif // __MODULEPARTICLES_H__