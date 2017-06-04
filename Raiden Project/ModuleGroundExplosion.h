#ifndef __MODULEGROUNDEXPLOSION_H__
#define __MODULEGROUNDEXPLOSION_H__

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

struct GroundExplosion
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	fPoint position;
	fPoint speed;
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

	GroundExplosion();
	GroundExplosion(const GroundExplosion& p);
	~GroundExplosion();
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

class ModuleGroundExplosion : public Module
{
public:
	ModuleGroundExplosion();
	~ModuleGroundExplosion();

	bool Init();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void MoveExplosionRight(bool);
	void AddGroundExplosion(const GroundExplosion& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, int bullettype = 0, int speed_x = 0, float speed_y = 0, bool delay = 0, bool multipleshot = false, int damage = 0, bool pactive = true, int position_respect_player = 0);
	void EraseParticles();
private:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics1 = nullptr;
	GroundExplosion* active[MAX_ACTIVE_PARTICLES];

public:

	GroundExplosion tank_explosion;
	GroundExplosion shiptank_explosion;
	GroundExplosion ship_explosion;
	//GroundExplosion megatank_explosion;

};
#endif // _MODULEGROUNDEXPLOSION_

