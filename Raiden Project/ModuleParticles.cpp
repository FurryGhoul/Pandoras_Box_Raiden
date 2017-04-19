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
	// laser particle
	laser.spriteshit = 0;
	laser.anim.PushBack({ 59, 100, 6, 6 });
	laser.anim.loop = false;
	laser.anim.speed = 1.0f;
	laser.life = 2100;
	laser.speed.y = -10;
	


	//Enemy normal shot
	enemyshot.spriteshit = 1;
	enemyshot.anim.PushBack({ 22, 41, 6, 5});
	enemyshot.anim.loop = false;
	enemyshot.anim.speed = 1.0f;
	enemyshot.life = 2100;
	enemyshot.speed.y = 10;
	
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
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), 18, 18);
			}
			if (p->spriteshit == 1)
			{
			App->render->Blit(graphics1, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), 18, 18);
			}
			if (p->fx_played == false)
			{
				p->fx_played = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, int speed_x, int speed_y, Uint32 delay)
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
			if (speed_x != 0)
			{
				p->speed.x = speed_x;
			}
			if (speed_y != 0)
			{
				p->speed.y = speed_y;
			}

			Mix_PlayChannel(-1, App->audio->fx_shoot, 0);
			if (collider_type != COLLIDER_NONE)
			{ 
				p->collider = App->collision->AddCollider({ 59, 100, 18, 18 }, collider_type, this);
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