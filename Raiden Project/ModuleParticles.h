#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"

#define MAX_ACTIVE_PARTICLES 10000

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	iPoint size;
	Uint32 bullettype = 0;
	Uint32 born = 0;
	Uint32 life = 0;
	int spriteshit = 0; //What spriteshit does the shot belong to
	bool fx_played = false;

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
	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, int bullettype = 0, int speed_x = 0, int speed_y = 0, Uint32 delay = 0, bool multipleshot = false);

private:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics1 = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];

public:

	Particle laser;
	Particle enemyshot;
	Particle explosion;
	Particle hitspark;
};

#endif // __MODULEPARTICLES_H__