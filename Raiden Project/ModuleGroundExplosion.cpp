#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleGroundExplosion.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleAudio_2.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMap1.h"
#include "ModuleMap2.h"
#include "ModuleStageClear1.h"
#include <stdlib.h>
#include <time.h>

ModuleGroundExplosion::ModuleGroundExplosion()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleGroundExplosion::~ModuleGroundExplosion()
{}

// Load assets
bool ModuleGroundExplosion::Init()
{

	srand(time(NULL));

	LOG("Loading particles");
	graphics = App->textures->Load("Assets/Player1.png");
	graphics1 = App->textures->Load("Assets/graphics2.png");

	//Tank explosion
	tank_explosion.spritesheet = 1;
	tank_explosion.anim.PushBack({ 4,2, 29, 27 });
	tank_explosion.anim.PushBack({ 35,2, 28, 26 });
	tank_explosion.anim.PushBack({ 65,2, 28, 27 });
	tank_explosion.anim.PushBack({ 92,1, 31, 28 });
	tank_explosion.anim.PushBack({ 125,1, 31, 28 });
	tank_explosion.anim.PushBack({ 160,1, 31, 28 });
	tank_explosion.anim.PushBack({ 199,2, 31, 28 });
	tank_explosion.anim.PushBack({ 234,2, 31, 28 });
	tank_explosion.anim.PushBack({ 269,2, 31, 28 });
	tank_explosion.anim.PushBack({ 304,4, 31, 28 });
	tank_explosion.anim.PushBack({ 339,4, 31, 28 });

	tank_explosion.speed.y = 1;
	tank_explosion.anim.loop = false;
	tank_explosion.anim.speed = 0.3f;
	tank_explosion.life = 100000;
	tank_explosion.size.x = 31 * 3;
	tank_explosion.size.y = 28 * 3;


	//Ship_Tank explosion
	shiptank_explosion.spritesheet = 1;
	shiptank_explosion.anim.PushBack({ 4, 2, 29, 27 });
	shiptank_explosion.anim.PushBack({ 35, 2, 28, 26 });
	shiptank_explosion.anim.PushBack({ 65, 2, 28, 27 });
	shiptank_explosion.anim.PushBack({ 92, 1, 31, 28 });
	shiptank_explosion.anim.PushBack({ 125, 1, 31, 28 });
	shiptank_explosion.anim.PushBack({ 160, 1, 31, 28 });
	shiptank_explosion.anim.PushBack({ 199, 2, 31, 28 });
	shiptank_explosion.anim.PushBack({ 234, 2, 31, 28 });
	shiptank_explosion.anim.PushBack({ 269, 2, 31, 28 });
	shiptank_explosion.anim.PushBack({ 304, 4, 31, 28 });
	shiptank_explosion.anim.PushBack({ 1, 1, 1, 1 });

	shiptank_explosion.speed.y = 1;
	shiptank_explosion.anim.loop = false;
	shiptank_explosion.anim.speed = 0.3f;
	shiptank_explosion.life = 100000;
	shiptank_explosion.size.x = 31 * 3;
	shiptank_explosion.size.y = 28 * 3;

	//Ship explosion
	ship_explosion.spritesheet = 1;
	ship_explosion.anim.PushBack({ 1, 237, 75, 66 });
	ship_explosion.anim.PushBack({ 67, 240, 75, 66 });
	ship_explosion.anim.PushBack({ 140, 241, 75, 66 });
	ship_explosion.anim.PushBack({ 218, 238, 75, 66 });
	ship_explosion.anim.PushBack({ 291, 239, 75, 66 });
	ship_explosion.anim.PushBack({ 368, 243, 75, 66 });
	ship_explosion.anim.PushBack({ 443, 243, 75, 66 });
	ship_explosion.anim.PushBack({ 524, 243, 75, 66 });
	ship_explosion.anim.PushBack({ 201, 532, 75, 66 });
	ship_explosion.anim.PushBack({ 291, 535, 75, 66 });
	ship_explosion.anim.PushBack({ 387, 538, 75, 66 });
	ship_explosion.anim.PushBack({ 481, 540, 75, 66 });
	ship_explosion.anim.PushBack({ 1, 1, 1, 1 });

	ship_explosion.speed.y = 1;
	ship_explosion.anim.loop = false;
	ship_explosion.anim.speed = 0.17f;
	ship_explosion.life = 100000;
	ship_explosion.size.x = 75 * 3;
	ship_explosion.size.y = 66 * 3;
	return true;

	//megatanks explosions
	/*megatank_explosion.anim.PushBack({ 1, 237, 77, 68 });
	megatank_explosion.anim.PushBack({ 67, 240, 77, 68 });
	megatank_explosion.anim.PushBack({ 140, 241, 77, 68 });
	megatank_explosion.anim.PushBack({ 218, 238, 77, 68 });
	megatank_explosion.anim.PushBack({ 291, 239, 77, 68 });
	megatank_explosion.anim.PushBack({ 368, 243, 77, 68 });
	megatank_explosion.anim.PushBack({ 443, 243, 77, 68 });
	megatank_explosion.anim.PushBack({ 524, 243, 77, 68 });
	megatank_explosion.anim.PushBack({ 1, 1, 1, 1 });
	megatank_explosion.speed.y = 1;
	megatank_explosion.anim.loop = false;
	megatank_explosion.anim.speed = 0.3f;
	megatank_explosion.life = 100000;
	megatank_explosion.size.x = 77 * 3;
	megatank_explosion.size.y = 68 * 3;*/
}

// Unload assets
bool ModuleGroundExplosion::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	App->textures->Unload(graphics1);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleGroundExplosion::Update()
{

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		GroundExplosion* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
			continue;
		}
		else if (SDL_GetTicks() >= p->born)
		{

			if (p->spritesheet == 1)
			{
				if (p->collider != nullptr)
				{
					p->active = true;
					App->render->Blit(graphics1, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), p->size.x, p->size.y);
				}
				else
				{
					App->render->Blit(graphics1, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), p->size.x, p->size.y);
				}
			}
			if (p->fx_played == false)
			{
				p->fx_played = true;
			}

		}
		// Always destroy out of screen particles
		if (p->position.y < -400 && p->position.y >1000)
		{
			delete active[i];
			active[i] = nullptr;

		}
	}


	return UPDATE_CONTINUE;
}



void ModuleGroundExplosion::AddGroundExplosion(const GroundExplosion& particle, int x, int y, COLLIDER_TYPE collider_type, int bullettype, int speed_x, float speed_y, bool delay, bool multipleshot, int damage, bool pactive, int position_respect_player)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			GroundExplosion* p = new GroundExplosion(particle);
			p->born = SDL_GetTicks();
			p->delay = delay;
			p->position.x = x;
			p->position.y = y;
			p->spritesheet = particle.spritesheet;
			p->bullettype = bullettype;
			p->active = pactive;
			p->position_respect_player = position_respect_player;
			if (speed_x != 0)
			{
				p->speed.x = speed_x;
			}
			if (speed_y != 0)
			{
				p->speed.y = speed_y;
			}
			p->size = particle.size;
			if (collider_type != COLLIDER_NONE)
			{
				p->collider = App->collision->AddCollider({ 10000, 10000, p->size.x, p->size.y }, collider_type, this, bullettype, damage);
			}

			active[i] = p;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

void ModuleGroundExplosion::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			if ((c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_TANK) && active[i]->bullettype == 1)
			{
				active[i]->AddPointsP1();
			}

			if ((c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_TANK) && active[i]->bullettype == 2)
			{
				active[i]->AddPointsP2();
			}

			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}
void ModuleGroundExplosion::MoveExplosionRight(bool right)
{
	if (right == true)
	{
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			if (active[i] != nullptr)
			{
				active[i]->position.x += App->map_1->xscrollspeed;
			}
		}
	}

	if (right == false)
	{
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			if (active[i] != nullptr)
			{
				active[i]->position.x -= App->map_1->xscrollspeed;
			}
		}
	}
}
void ModuleGroundExplosion::EraseParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

}
GroundExplosion::GroundExplosion()
{
	position.SetToZero();
	speed.SetToZero();
}

GroundExplosion::GroundExplosion(const GroundExplosion& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

GroundExplosion::~GroundExplosion()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool GroundExplosion::Update()
{

	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
		{
			ret = false;
		}

	}
	else
		if (anim.Finished())
			ret = false;
	//Partices won't move if delay is true;
	if (time_got == false)
	{
		initial_time = SDL_GetTicks();
		time_got = true;
	}

	if (active)
	{
		if (collider != nullptr)
			collider->SetPos(position.x, position.y);

		if (bullettype == 37 || bullettype == 27)
			displace();
	}
	else
	{
		collider->SetPos(10000, 1000);
	}

	if (delay == false)
	{
		position.x += speed.x;
		position.y += speed.y;
	}
	else
	{
		if (SDL_GetTicks() - initial_time > 500)
		{
			position.x += speed.x;
			position.y += speed.y;
		}
	}
	return ret;
}