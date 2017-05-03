#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleAudio_1.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMap1.h"
#include "ModuleMap2.h"
#include "ModuleStageClear1.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Init()
{
	
	LOG("Loading particles");
	graphics = App->textures->Load("Assets/Player1.png");
	graphics1 = App->textures->Load("Assets/graphics2.png");
	// player laser particles
	laser.spriteshit = 0;
	laser.anim.PushBack({ 59, 100, 6, 6 });
	laser.anim.loop = false;
	laser.anim.speed = 1.0f;
	laser.life = 2100;
	laser.speed.y = -10;
	laser.size.x = 18;
	laser.size.y = 18;

	//Enemy normal shot
	enemyshot.spriteshit = 1;
	enemyshot.anim.PushBack({ 22, 41, 6, 5});
	enemyshot.anim.loop = false;
	enemyshot.anim.speed = 1.0f;
	enemyshot.life = 2100;
	enemyshot.speed.y = 10;
	enemyshot.size.x = 18;
	enemyshot.size.y = 18;
	
	//Explosion
	explosion.spriteshit = 1;
	explosion.anim.PushBack({ 26, 339, 10, 8 });
	explosion.anim.PushBack({ 41, 337, 14, 12 });
	explosion.anim.PushBack({ 88, 334, 20, 18});
	explosion.anim.PushBack({ 122, 333, 22, 19 });
	explosion.anim.PushBack({ 165, 333, 24, 22 });
	explosion.anim.PushBack({ 214, 332, 26, 24 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;
	explosion.size.x = 18 * 3;
	explosion.size.y = 18 * 3;

	//Hit spark
	hitspark.spriteshit = 1;
	hitspark.anim.PushBack({ 547, 1308, 15, 19 });
	hitspark.anim.PushBack({ 563, 1308, 15, 19 });
	hitspark.anim.PushBack({ 580, 1308, 15, 19 });
	hitspark.anim.PushBack({ 596, 1308, 16, 20 });
	hitspark.anim.loop = false;
	hitspark.anim.speed = 0.5f;
	hitspark.size.x = 18 * 3;
	hitspark.size.y = 18 * 3;
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

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
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			if (p->spriteshit == 0)
			{ 
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), p->size.x, p->size.y);
			}
			if (p->spriteshit == 1)
			{
			App->render->Blit(graphics1, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), p->size.x, p->size.y);
			}
			if (p->fx_played == false)
			{
				p->fx_played = true;
			}
			// Always destroy out of screen particles
			if (active[i]->position.y <= -1 || !App->map_1->IsEnabled() && !App->map_2->IsEnabled())
			{
				delete active[i];
				active[i] = nullptr;
				break;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, int bullettype, int speed_x, int speed_y, Uint32 delay, bool multipleshot)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->spriteshit = particle.spriteshit;
			p->bullettype = bullettype;
			if (speed_x != 0)
			{
				p->speed.x = speed_x;
			}
			if (speed_y != 0)
			{
				p->speed.y = speed_y;
			}
			p->size = particle.size;
			if (!multipleshot)
			{
				Mix_PlayChannel(-1, App->audio->fx_shoot, 0);
			}

			if (collider_type != COLLIDER_NONE)
			{ 
				p->collider = App->collision->AddCollider({ 59, 100, 18, 18 }, collider_type, this, bullettype);
			}
			active[i] = p;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
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

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}