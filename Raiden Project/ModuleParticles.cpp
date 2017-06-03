#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
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
	// player quadriple shot particles right 1
	quad_shot_right1.spritesheet = 0;
	quad_shot_right1.anim.PushBack({ 107, 98, 16, 8 });
	quad_shot_right1.anim.loop = false;
	quad_shot_right1.anim.speed = 0.1f;
	quad_shot_right1.life = 2100;
	quad_shot_right1.speed.y = -15;
	quad_shot_right1.size.x = 48;
	quad_shot_right1.size.y = 24;
	// player quadriple shot particles right 2
	quad_shot_right2.spritesheet = 0;
	quad_shot_right2.anim.PushBack({ 175, 98, 16, 9 });
	quad_shot_right2.anim.loop = false;
	quad_shot_right2.anim.speed = 0.1f;
	quad_shot_right2.life = 2100;
	quad_shot_right2.speed.y = -15;
	quad_shot_right2.size.x = 48;
	quad_shot_right2.size.y = 27;
	// player quadriple shot particles left 1
	quad_shot_left1.spritesheet = 0;
	quad_shot_left1.anim.PushBack({ 129, 98, 16, 8});
	quad_shot_left1.anim.loop = false;
	quad_shot_left1.anim.speed = 0.1f;
	quad_shot_left1.life = 2100;
	quad_shot_left1.speed.y = -15;
	quad_shot_left1.size.x = 48;
	quad_shot_left1.size.y = 24;
	// player quadriple shot particles left 2
	quad_shot_left2.spritesheet = 0;
	quad_shot_left2.anim.PushBack({ 155, 97, 16, 9 });
	quad_shot_left2.anim.loop = false;
	quad_shot_left2.anim.speed = 0.1f;
	quad_shot_left2.life = 2100;
	quad_shot_left2.speed.y = -15;
	quad_shot_left2.size.x = 48;
	quad_shot_left2.size.y = 27;
	// Player laser particles
	laser.spritesheet = 0;
	laser.anim.PushBack({ 51, 89, 1, 16 });
	laser.anim.loop = false;
	laser.anim.speed = 0.1f;
	laser.life = 2100;
	laser.speed.y = -20;
	laser.size.x = 6;
	laser.size.y = 48;

	// Player laser 2 particles
	laser2.spritesheet = 0;
	laser2.anim.PushBack({ 235, 92, 4, 13 });
	laser2.anim.loop = false;
	laser2.anim.speed = 0.1f;
	laser2.life = 2100;
	laser2.speed.y = -20;
	laser2.size.x = 12;
	laser2.size.y = 39;

	//Player final laser particle
	final_laser.spritesheet = 0;
	final_laser.anim.PushBack({ 26, 90, 18, 16 });
	final_laser.anim.loop = false;
	final_laser.anim.speed = 0.1f;
	final_laser.life = 2100;
	final_laser.speed.y = -20;
	final_laser.size.x = 54;
	final_laser.size.y = 48;

	//Player missile
	player_light_missile.spritesheet = 1;
	player_light_missile.anim.PushBack({ 277,39,4,11 });
	player_light_missile.anim.PushBack({ 294,39,4,11 });
	player_light_missile.life = 2100;
	player_light_missile.anim.loop = true;
	player_light_missile.anim.speed = 1.0f;
	player_light_missile.speed.y = -20;
	player_light_missile.size.x = 4 * 3;
	player_light_missile.size.y = 11 * 3;

	// Player missile mid
	player_mid_missiles.spritesheet = 1;
	player_mid_missiles.anim.PushBack({ 392,35,6,15 });
	player_mid_missiles.anim.PushBack({ 375,35,6,15 });
	player_mid_missiles.life = 2100;
	player_mid_missiles.anim.loop = true;
	player_mid_missiles.anim.speed = 1.0f;
	player_mid_missiles.speed.y = -20;
	player_mid_missiles.size.x = 6 * 3;
	player_mid_missiles.size.y = 20 * 3;

	// Player missile heavy
	heavy_missiles.spritesheet = 1;
	heavy_missiles.anim.PushBack({ 575,34,13,16 });
	heavy_missiles.anim.PushBack({ 592,34,13,16 });
	heavy_missiles.anim.PushBack({ 609,34,13,16 });
	heavy_missiles.anim.PushBack({ 626,34,13,16 });
	heavy_missiles.anim.PushBack({ 643,34,13,16 });
	heavy_missiles.anim.PushBack({ 660,34,13,16 });

	heavy_missiles.life = 2100;
	heavy_missiles.anim.loop = true;
	heavy_missiles.anim.speed = 0.3f;
	heavy_missiles.speed.y = -20;
	heavy_missiles.size.x = 13 * 3;
	heavy_missiles.size.y = 16 * 3;

	//Player explosion
	player_explosion.spritesheet = 1;
	player_explosion.anim.PushBack({ 8,203,24,27 });
	player_explosion.anim.PushBack({ 41,203,28,28 });
	player_explosion.anim.PushBack({ 77,203,31,30 });
	player_explosion.anim.PushBack({ 117,203,32,30 });
	player_explosion.anim.PushBack({ 163,203,31,30 });
	


	player_explosion.anim.loop = false;
	player_explosion.anim.speed = 0.15f;
	player_explosion.size.x = 30 * 3;
	player_explosion.size.y = 30 * 3; 
	//Enemy normal shot
	enemyshot.spritesheet = 1;
	enemyshot.anim.PushBack({ 22, 41, 6, 5});
	enemyshot.anim.PushBack({ 39, 41, 6, 5 });
	enemyshot.anim.PushBack({ 56, 41, 6, 5 });
	enemyshot.anim.loop = true;
	enemyshot.anim.speed = 0.3f;
	enemyshot.life = 2100;
	enemyshot.speed.y = 0;
	enemyshot.size.x = 18;
	enemyshot.size.y = 18;

	//Long megatank shot
	longmegatank_laser.spritesheet = 1;
	longmegatank_laser.anim.PushBack({ 474, 37, 12, 10 });
	longmegatank_laser.anim.PushBack({ 491, 37, 12, 10 });
	longmegatank_laser.anim.PushBack({ 508, 37, 12, 10 });
	longmegatank_laser.anim.loop = true;
	longmegatank_laser.anim.speed = 0.5f;
	longmegatank_laser.life = 2000;
	longmegatank_laser.speed.y = 10;
	longmegatank_laser.size.x = 36;
	longmegatank_laser.size.y = 30;
	
	//Explosion (has to be redone)
	explosion.spritesheet = 1;
	explosion.anim.PushBack({ 26, 339, 10, 8 });
	explosion.anim.PushBack({ 41, 337, 14, 12 });
	explosion.anim.PushBack({ 88, 334, 20, 18});
	explosion.anim.PushBack({ 122, 333, 22, 19 });
	explosion.anim.PushBack({ 165, 333, 24, 22 });
	explosion.anim.PushBack({ 214, 332, 26, 24 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;
	explosion.size.x = 25 * 3;
	explosion.size.y = 25 * 3;

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
	bombexplosion.anim.speed = 0.8f;
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

	bombexplosion2.anim.PushBack({ 2, 1095, 168, 154 });
	bombexplosion2.anim.PushBack({ 173, 1095, 168, 154 });

	bombexplosion2.anim.loop = false;
	bombexplosion2.anim.speed = 0.4f;
	bombexplosion2.size.x = 168 * 3;
	bombexplosion2.size.y = 154 * 3;
	bombexplosion2.life = 1000;


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


	//Player explosion

	bonusmedium_explosion.spritesheet = 1;
	bonusmedium_explosion.anim.PushBack({ 130,462,76,66});
	bonusmedium_explosion.anim.PushBack({ 193,462,76,66 });
	bonusmedium_explosion.anim.PushBack({ 267,462,76,66 });
	bonusmedium_explosion.anim.PushBack({ 346,462,76,66 });
	bonusmedium_explosion.anim.PushBack({ 439,468,76,66 });
	bonusmedium_explosion.anim.PushBack({ 525,468,76,66 });
	bonusmedium_explosion.anim.PushBack({ 614,462,76,66 });
	bonusmedium_explosion.anim.PushBack({ 16,533,76,66 });
	bonusmedium_explosion.anim.PushBack({ 108,533,76,66 });

	bonusmedium_explosion.anim.loop = false;
	bonusmedium_explosion.anim.speed = 0.2f;
	bonusmedium_explosion.size.x = 80 * 3;
	bonusmedium_explosion.size.y = 71 * 3;

	

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
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
				Mix_PlayChannel(-1, App->audio_2->fx_bomb_explosion, 0);
			}
			else if (p->bullettype == 48)
			{
				AddParticle(bombexplosion, p->position.x - ((168 * 3) / 2), p->position.y - ((154 * 3) / 2), COLLIDER_NONE, 38);
				Mix_PlayChannel(-1, App->audio_2->fx_bomb_explosion, 0);
			}
			else if (p->bullettype == 37)
			{
				AddParticle(bombexplosion2, p->position.x, p->position.y, COLLIDER_BOMB, 27, 0, 0, false, false, 3);
			}
			else if (p->bullettype == 38)
			{
				AddParticle(bombexplosion2, p->position.x, p->position.y, COLLIDER_BOMB, 28, 0, 0, false, false, 3);
			}

			delete p;
			active[i] = nullptr;
			continue;
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
					if (App->player->powerup_level < 3) // just 1 and 2 level particles should come out from the middle of the player
					p->position.x = App->player->position.x + 30;
					else
						p->position.x = App->player->position.x + p->position_respect_player;
				}
				if (p->collider->bullettype == 2)
				{
					if (App->player2->powerup_level < 3) // just 1 and 2 level particles should come out from the middle of the player 2
						p->position.x = App->player2->position.x + 30;
					else
						p->position.x = App->player2->position.x + p->position_respect_player;
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
						if (App->player->powerup_level < 3) // just 1 and 2 level particles should come out from the middle of the player
							p->position.x = App->player->position.x + 30;
						else// provisional (while powerups are added has to change)
							p->position.x = App->player->position.x + p->position_respect_player;
					}
					if (p->collider->bullettype == 2)
					{
						if (App->player2->powerup_level < 3) // just 1 and 2 level particles should come out from the middle of the player 2
							p->position.x = App->player2->position.x + 30;
						else // provisional (while powerups are added has to change)
							p->position.x = App->player2->position.x + p->position_respect_player;
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
		
		}	
		// Always destroy out of screen particles
  		if (p->position.y < -400 && p->position.y >1000 )
		{
			delete active[i];
			active[i] = nullptr;
			
		}
	}

	
	return UPDATE_CONTINUE;
}



void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, int bullettype, int speed_x, int speed_y, bool delay, bool multipleshot, int damage, bool pactive, int position_respect_player)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
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
				p->collider = App->collision->AddCollider({ 10000, 10000, p->size.x, p->size.y}, collider_type, this, bullettype, damage);
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
void ModuleParticles::EraseParticles()
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

	if (bullettype == 37 || bullettype == 27 || bullettype == 38 || bullettype == 28)
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
		if (SDL_GetTicks()- initial_time > 300)
		{ 
		position.x += speed.x;
		position.y += speed.y;
		}
		else
		{
			position.x += speed.x*0.25;
			position.y += speed.y*0.25;
		}
	}
	return ret;
}

