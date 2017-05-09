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
#include <stdlib.h>
#include <time.h>

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
	
	srand(time(NULL));

	LOG("Loading particles");
	graphics = App->textures->Load("Assets/Player1.png");
	graphics1 = App->textures->Load("Assets/graphics2.png");

	// player double shot particles
	double_shot.spritesheet = 0;
	double_shot.anim.PushBack({ 59, 100, 6, 6 });
	double_shot.anim.loop = false;
	double_shot.anim.speed = 0.1f;
	double_shot.life = 2100;
	double_shot.speed.y = -15;
	double_shot.size.x = 18;
	double_shot.size.y = 18;

	// player triple shot particles
	triple_shot.spritesheet = 0;
	triple_shot.anim.PushBack({ 74, 100, 10, 6 });
	triple_shot.anim.loop = false;
	triple_shot.anim.speed = 0.1f;
	triple_shot.life = 2100;
	triple_shot.speed.y = -15;
	triple_shot.size.x = 30;
	triple_shot.size.y = 18;

	// player quadriple shot particles
	quad_shot.spritesheet = 0;
	quad_shot.anim.PushBack({ 89, 100, 14, 6 });
	quad_shot.anim.loop = false;
	quad_shot.anim.speed = 0.1f;
	quad_shot.life = 2100;
	quad_shot.speed.y = -15;
	quad_shot.size.x = 42;
	quad_shot.size.y = 18;

	// Player laser particles
	laser.spritesheet = 0;
	laser.anim.PushBack({ 51, 89, 1, 16 });
	laser.anim.loop = false;
	laser.anim.speed = 0.1f;
	laser.life = 2100;
	laser.speed.y = -15;
	laser.size.x = 6;
	laser.size.y = 48;

	// Player laser 2 particles
	laser2.spritesheet = 1;
	laser2.anim.PushBack({ 9, 106, 5, 8 });
	laser2.anim.loop = false;
	laser2.anim.speed = 0.1f;
	laser2.life = 2100;
	laser2.speed.y = -15;
	laser2.size.x = 15;
	laser2.size.y = 24;
	
	//Enemy normal shot
	enemyshot.spritesheet = 1;
	enemyshot.anim.PushBack({ 22, 41, 6, 5});
	enemyshot.anim.PushBack({ 39, 41, 6, 5 });
	enemyshot.anim.PushBack({ 56, 41, 6, 5 });
	enemyshot.anim.loop = true;
	enemyshot.anim.speed = 0.3f;
	enemyshot.life = 2100;
	enemyshot.speed.y = 10;
	enemyshot.size.x = 18;
	enemyshot.size.y = 18;
	
	//Explosion
	explosion.spritesheet = 1;
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
	hitspark.spritesheet = 1;
	hitspark.anim.PushBack({ 408, 41, 12, 12 });
	hitspark.anim.PushBack({ 424, 41, 12, 12 });
	hitspark.anim.PushBack({ 441, 37, 12, 12 });
	hitspark.anim.PushBack({ 457, 35, 12, 12 });
	hitspark.anim.loop = false;
	hitspark.anim.speed = 0.8f;
	hitspark.size.x = 12 * 3;
	hitspark.size.y = 12 * 3;

	//Bomb particles
	bomb.spritesheet = 1;

	bomb.anim.PushBack({ 395, 136, 8, 16 });
	bomb.anim.PushBack({ 404, 136, 8, 16 });
	bomb.anim.PushBack({ 395, 136, 8, 16 });
	bomb.anim.PushBack({ 404, 136, 8, 16 });
	bomb.anim.PushBack({ 395, 136, 8, 16 });
	bomb.anim.PushBack({ 404, 136, 8, 16 });
	bomb.anim.PushBack({ 395, 136, 8, 16 });
	bomb.anim.PushBack({ 404, 136, 8, 16 });

	bomb.anim.PushBack({ 413, 136, 8, 16 });
	bomb.anim.PushBack({ 422, 136, 8, 16 });
	bomb.anim.PushBack({ 413, 136, 8, 16 });
	bomb.anim.PushBack({ 422, 136, 8, 16 });

	bomb.anim.PushBack({ 431, 136, 8, 16 });
	bomb.anim.PushBack({ 440, 136, 8, 16 });
	bomb.anim.PushBack({ 431, 136, 8, 16 });
	bomb.anim.PushBack({ 440, 136, 8, 16 });

	bomb.anim.PushBack({ 449, 136, 8, 16 });
	bomb.anim.PushBack({ 458, 136, 8, 16 });
	bomb.anim.PushBack({ 449, 136, 8, 16 });
	bomb.anim.PushBack({ 458, 136, 8, 16 });

	bomb.speed.y = -4;
	bomb.anim.loop = false;
	bomb.anim.speed = 0.5f;
	bomb.size.x = 8 * 3;
	bomb.size.y = 15 * 3;
	bomb.life = 600;

	//Bomb explosion particles
	bombexplosion.spritesheet = 1;

	bombexplosion.anim.PushBack({ 2, 624, 168, 154 });
	bombexplosion.anim.PushBack({ 2, 624, 168, 154 });

	bombexplosion.anim.PushBack({ 173, 624, 168, 154 });
	bombexplosion.anim.PushBack({ 173, 624, 168, 154 });

	bombexplosion.anim.PushBack({ 344, 624, 168, 154 });
	bombexplosion.anim.PushBack({ 344, 624, 168, 154 });

	bombexplosion.anim.PushBack({ 515, 624, 168, 154 });
	bombexplosion.anim.PushBack({ 515, 624, 168, 154 });

	bombexplosion.anim.PushBack({ 2, 781, 168, 154 });
	bombexplosion.anim.PushBack({ 2, 781, 168, 154 });

	bombexplosion.anim.PushBack({ 173, 781, 168, 154 });
	bombexplosion.anim.PushBack({ 173, 781, 168, 154 });

	bombexplosion.anim.PushBack({ 344, 781, 168, 154 });
	bombexplosion.anim.PushBack({ 344, 781, 168, 154 });

	bombexplosion.anim.PushBack({ 515, 781, 168, 154 });
	bombexplosion.anim.PushBack({ 515, 781, 168, 154 });

	bombexplosion.anim.PushBack({ 2, 938, 168, 154 });
	bombexplosion.anim.PushBack({ 2, 938, 168, 154 });

	bombexplosion.anim.loop = false;
	bombexplosion.anim.speed = 0.6f;
	bombexplosion.size.x = 168 * 3;
	bombexplosion.size.y = 154 * 3;

	//Bomb explosion 2 particles
	bombexplosion2.spritesheet = 1;
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 344, 938, 168, 154 });

	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });
	bombexplosion2.anim.PushBack({ 515, 938, 168, 154 });

	bombexplosion2.anim.loop = false;
	bombexplosion2.anim.speed = 0.4f;
	bombexplosion2.size.x = 168 * 3;
	bombexplosion2.size.y = 154 * 3;

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
			if (p->bullettype == 47)
			{
				AddParticle(bombexplosion, p->position.x - ((168 * 3) / 2), p->position.y - ((154 * 3) / 2), COLLIDER_NONE, 37);
			}

			else if (p->bullettype == 37)
			{
				AddParticle(bombexplosion2, p->position.x, p->position.y, COLLIDER_NONE, 27);
			}

			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			if (p->spritesheet == 0)
			{ 
			if (p->collider != nullptr)
			{ 
			if ((p->collider->bullettype == 1 && (p->position.y > App->player->position.y)) || (p->collider->bullettype == 2 && (p->position.y  > App->player2->position.y))) // If player shots are behind player, they don't appear
			{
				p->active = false;
				if (p->collider->bullettype == 1)
				{
					p->position.x = App->player->position.x + 30;
				}
				if (p->collider->bullettype == 2)
				{
					p->position.x = App->player2->position.x + 30;
				}
			}

			  else
			  { 
			  p->active = true;
			  App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), p->size.x, p->size.y);
			  }
			}
			else
			{
				App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), p->size.x, p->size.y);
			}

			}

		if (p->spritesheet == 1)
		{
				if (p->collider != nullptr)
				{ 
 				if ((p->collider->bullettype == 1 && (p->position.y > App->player->position.y)) || (p->collider->bullettype == 2 && (p->position.y  > App->player2->position.y))) // If player shots are behind player, they don't appear
				{
					p->active = false;
					if (p->collider->bullettype == 1)
					{
						p->position.x = App->player->position.x + 30;
					}
					if (p->collider->bullettype == 2)
					{
						p->position.x = App->player2->position.x + 30;
					}
				}

				else
				  {
					p->active = true;
					App->render->Blit(graphics1, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), p->size.x, p->size.y);
				   }
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



void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, int bullettype, int speed_x, int speed_y, Uint32 delay, bool multipleshot, int damage, bool pactive)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->initialpos.x = x;
			p->initialpos.y = y;
			p->spritesheet = particle.spritesheet;
			p->bullettype = bullettype;
			p->active = pactive;
			if (speed_x != 0)
			{
				p->speed.x = speed_x;
			}
			if (speed_y != 0)
			{
				p->speed.y = speed_y;
			}
			p->size = particle.size;
			if (!multipleshot && bullettype != 47 && bullettype != 37 && bullettype != 27)
			{
				Mix_PlayChannel(-1, App->audio->fx_shoot, 0);
			}

			if (collider_type != COLLIDER_NONE)
			{ 
				p->collider = App->collision->AddCollider({ 59, 100, p->size.x, p->size.y}, collider_type, this, bullettype, damage);
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
void ModuleParticles::MoveParticlesRight(bool right)
{
	if (right == true)
	{
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			if (active[i] != nullptr)
			{
				active[i]->position.x += 6;
			}
		}
	}

	if (right == false)
	{
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			if (active[i] != nullptr)
			{
				active[i]->position.x -= 6;
			}
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
		{
			ret = false;
		}

	}
	else
		if (anim.Finished())
			ret = false;

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
    position.x += speed.x;
	position.y += speed.y;
	return ret;
}