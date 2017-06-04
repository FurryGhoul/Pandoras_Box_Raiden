#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleGroundEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "Enemy_Light_Shooter.h"
#include "Enemy_Medium_Shooter.h"
#include "Enemy_Bonus_Ship.h"
#include "Tank.h"
#include "Turret.h"
#include "ModulePowerUps.h"
#include "Box_Medal.h"
#include "Box_PowerUp.h"
#include "ModuleMap1.h"
#include "Enemy_Kamikaze.h"
#include "Enemy_Ship_Tank.h"
#include "Enemy_Long_Megatank.h"
#include "Enemy_Ship.h"
#include "ModuleGroundExplosion.h"
#include "Enemy_Light_Shooter_Kamikaze.h"
#include "Enemy_Megatank.h"
#include "Enemy_Grey_Tank.h"
#include "Enemy_Boss_Main.h"
#include "Enemy_Boss_Left_Wing.h"
#include "Enemy_Boss_Right_Wing.h"
#include "Enemy_Boss_Cannon.h"
#include "Enemy_Train_Locomotive.h"
#include "Enemy_Train_Coach.h"
#include "ModuleAudio_2.h"

#define SPAWN_MARGIN 100

ModuleGroundEnemies::ModuleGroundEnemies()
{
	for (uint i = 0; i < MAX_GROUND_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleGroundEnemies::~ModuleGroundEnemies()
{
}

bool ModuleGroundEnemies::Init()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites3 = App->textures->Load("assets/Tank1.png");
	sprites5 = App->textures->Load("assets/Boxes.png");
	sprites7 = App->textures->Load("assets/LongMegatank.png");
	sprites8 = App->textures->Load("assets/Ship.png");
	sprites10 = App->textures->Load("assets/Megatank.png");
	sprites13 = App->textures->Load("assets/Train.png");

	return true;
}

update_status ModuleGroundEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_GROUND_ENEMIES; ++i)
	{
		if (queue[i].type != GENEMY_TYPES::GNO_TYPE)
		{
			if (queue[i].y * SCREEN_SIZE > App->render->camera.y - SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", queue[i].y* SCREEN_SIZE);
				SpawnGroundEnemy(queue[i]);
				queue[i].type = GENEMY_TYPES::GNO_TYPE;

			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleGroundEnemies::Update()
{
	for (uint i = 0; i < MAX_GROUND_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->MoveShoot();

	for (uint i = 0; i < MAX_GROUND_ENEMIES; ++i)
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->spritesheet == 9) //Megatank
				enemies[i]->Draw(sprites10);
			else if (enemies[i]->spritesheet == 1) //Bonus Ship
				enemies[i]->Draw(sprites2);
			else if (enemies[i]->spritesheet == 2) //Tank & Ship_Tank
				enemies[i]->Draw(sprites3);
			else if (enemies[i]->spritesheet == 4) //Box_Medal & Box_PowerUp
				enemies[i]->Draw(sprites5);
			else if (enemies[i]->spritesheet == 6) //Long Megatank
				enemies[i]->Draw(sprites7);
			else if (enemies[i]->spritesheet == 7) //Ship
				enemies[i]->Draw(sprites8);
			else if (enemies[i]->spritesheet == 8) //Train
				enemies[i]->Draw(sprites13);
			
		}
	return UPDATE_CONTINUE;
}

update_status ModuleGroundEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_GROUND_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.y * SCREEN_SIZE < -300 || enemies[i]->position.y * SCREEN_SIZE > 1000 || enemies[i]->position.x * SCREEN_SIZE < -500 || enemies[i]->position.x * SCREEN_SIZE > 1300)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.y * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleGroundEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_GROUND_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleGroundEnemies::AddGroundEnemy(int path, GENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_GROUND_ENEMIES; ++i)
	{
		if (queue[i].type == GENEMY_TYPES::GNO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i]._path = path;//assignes a path to the enemy
			ret = true;
			break;
		}
	}

	return ret;
}


void ModuleGroundEnemies::SpawnGroundEnemy(const GroundEnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_GROUND_ENEMIES; ++i);

	if (i != MAX_GROUND_ENEMIES)
	{
		switch (info.type)
		{
			
		case GENEMY_TYPES::TANK:
			enemies[i] = new Tank(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case GENEMY_TYPES::GREY_TANK:
			enemies[i] = new Enemy_Grey_Tank(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case GENEMY_TYPES::SHIP_TANK:
			enemies[i] = new Enemy_Ship_Tank(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case GENEMY_TYPES::SHIP:
			enemies[i] = new Enemy_Ship(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case GENEMY_TYPES::LONG_MEGATANK:
			enemies[i] = new Enemy_Long_Megatank(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case GENEMY_TYPES::MEGATANK:
			enemies[i] = new Enemy_Megatank(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case GENEMY_TYPES::BOX_MEDAL:
			enemies[i] = new Box_Medal(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case GENEMY_TYPES::BOX_POWERUP:
			enemies[i] = new Box_PowerUp(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case GENEMY_TYPES::TRAIN_LOCOMOTIVE:
			enemies[i] = new Enemy_Train_Locomotive(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case GENEMY_TYPES::TRAIN_COACH:
			enemies[i] = new Enemy_Train_Coach(App->map_1->xmap + info.x, info.y, info._path);
			break;
		}
	}
}

void ModuleGroundEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_GROUND_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			if (c2->bullettype == 27)
			{
				if (SDL_GetTicks() - enemies[i]->btime >= 120)
					enemies[i]->bombimmunity = false;

				if (!enemies[i]->bombimmunity)
				{
					enemies[i]->hp -= c2->damage;
					enemies[i]->bombimmunity = true;
					enemies[i]->btime = SDL_GetTicks();
					App->player->score += 20;
				}
			}
			else if (c2->bullettype == 28)
			{
				if (SDL_GetTicks() - enemies[i]->btime2 >= 120)
					enemies[i]->bombimmunity = false;

				if (!enemies[i]->bombimmunity)
				{
					enemies[i]->hp -= c2->damage;
					enemies[i]->bombimmunity = true;
					enemies[i]->btime2 = SDL_GetTicks();
					App->player->score += 20;
				}
			}
			else
			{
				enemies[i]->hp -= c2->damage;
			}

			if (enemies[i]->trainlocomotive)
			{
				enemies[i]->ishit = true;
			}
			if (enemies[i]->traincoach)
			{
				enemies[i]->ishit = true;
			}
			if (enemies[i]->ship)
			{
				enemies[i]->ishit = true;
			}
			if (enemies[i]->shiptank)
			{
				enemies[i]->ishit = true;
			}
			if (enemies[i]->tank)
			{
				enemies[i]->ishit = true;
				enemies[i]->ishit2 = true;
			}
			if (enemies[i]->greytank)
			{
				enemies[i]->ishit = true;
				enemies[i]->ishit2 = true;
			}
			if (enemies[i]->megatank)
			{
  				enemies[i]->ishit = true;
				enemies[i]->ishit2 = true;
			}
			if (enemies[i]->longmegatank)
			{
				enemies[i]->ishit = true;
				enemies[i]->ishit2 = true;
				enemies[i]->ishit3 = true;
				enemies[i]->ishit4 = true;
			}


			if (enemies[i]->hp < 0)
				enemies[i]->hp = 0;

			if (c2->bullettype == 1 || c2->bullettype == 2)
			{
				App->particles->AddParticle(App->particles->hitspark, c2->rect.x, c2->rect.y, COLLIDER_NONE);
			}
			if (c2->bullettype == -1)
			{
				App->particles->AddParticle(App->particles->explosion, c2->rect.x, c2->rect.y, COLLIDER_NONE);
			}

			if (c2->bullettype == 3 || c2->bullettype == 4)
			{
				enemies[i]->hp = 0;
			}

			if (enemies[i]->hp == 1)
			{
				if (enemies[i]->tank && enemies[i]->turretexploded == false)
				{
					App->particles->AddParticle(App->particles->shiptank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
					enemies[i]->turretexploded == true;
				}
				else if (enemies[i]->shiptank && enemies[i]->turretexploded == false)
				{
					App->particles->AddParticle(App->particles->shiptank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
					enemies[i]->turretexploded == true;
				}
				else if (enemies[i]->greytank && enemies[i]->turretexploded == false)
				{
					App->particles->AddParticle(App->particles->shiptank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
					enemies[i]->turretexploded == true;
				}
			}

			if (enemies[i]->hp <= 0)
			{
				if (c2->bullettype == 1 || c2->bullettype == 27)
				{
					App->player->score += enemies[i]->points;
				}

				else if (c2->bullettype == 2 || c2->bullettype == 28)
				{
					App->player2->score += enemies[i]->points;
				}


				
				if (enemies[i]->tank)
				{
					App->gexplosion->AddGroundExplosion(App->gexplosion->tank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
					Mix_PlayChannel(-1, App->audio_2->fx_light_ground_explosion, 0);
				}
				else if (enemies[i]->greytank)
				{
					App->gexplosion->AddGroundExplosion(App->gexplosion->tank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE, -1, 0, 1.5);
					Mix_PlayChannel(-1, App->audio_2->fx_light_ground_explosion, 0);
				}
				else if (enemies[i]->megatank)
				{
					App->gexplosion->AddGroundExplosion(App->gexplosion->ship_explosion, enemies[i]->position.x - 30, enemies[i]->position.y - 20, COLLIDER_NONE);
					Mix_PlayChannel(-1, App->audio_2->fx_heavy_ground_explosion, 0);
				}
				else if (enemies[i]->longmegatank)
				{
					App->gexplosion->AddGroundExplosion(App->gexplosion->ship_explosion, enemies[i]->position.x - 50, enemies[i]->position.y - 20, COLLIDER_NONE);
					Mix_PlayChannel(-1, App->audio_2->fx_heavy_ground_explosion, 0);
				}
				else if (enemies[i]->shiptank)
				{
					App->gexplosion->AddGroundExplosion(App->gexplosion->shiptank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
					Mix_PlayChannel(-1, App->audio_2->fx_light_ground_explosion, 0);
				}
				else if (enemies[i]->ship)
				{
					App->gexplosion->AddGroundExplosion(App->gexplosion->ship_explosion, enemies[i]->position.x - 70, enemies[i]->position.y, COLLIDER_NONE);
					App->powerups->AddPowerUp(POWERUP_TYPES::REDUP, enemies[i]->position.x - 70, enemies[i]->position.y);
					Mix_PlayChannel(-1, App->audio_2->fx_heavy_ground_explosion, 0);
				}
				else if (enemies[i]->trainlocomotive)
				{
					App->gexplosion->AddGroundExplosion(App->gexplosion->ship_explosion, enemies[i]->position.x - 70, enemies[i]->position.y -70, COLLIDER_NONE);
					Mix_PlayChannel(-1, App->audio_2->fx_heavy_ground_explosion, 0);
				}
				else if (enemies[i]->traincoach)
				{
					App->gexplosion->AddGroundExplosion(App->gexplosion->ship_explosion, enemies[i]->position.x - 70, enemies[i]->position.y - 70, COLLIDER_NONE);
					Mix_PlayChannel(-1, App->audio_2->fx_heavy_ground_explosion, 0);
				}
				
				else if (enemies[i]->medalbox)
				{
					App->powerups->AddPowerUp(POWERUP_TYPES::MEDAL, enemies[i]->position.x + 25, enemies[i]->position.y + 5);
					App->gexplosion->AddGroundExplosion(App->gexplosion->shiptank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
					Mix_PlayChannel(-1, App->audio_2->fx_light_ground_explosion, 0);
				}

				else if (enemies[i]->powerupbox)
				{
					App->powerups->AddPowerUp(POWERUP_TYPES::MISSILEUP, enemies[i]->position.x, enemies[i]->position.y);
					App->gexplosion->AddGroundExplosion(App->gexplosion->shiptank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
					Mix_PlayChannel(-1, App->audio_2->fx_light_ground_explosion, 0);
				}

				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}
	}
}

void ModuleGroundEnemies::EraseGroundEnemies()
{
	for (uint i = 0; i < MAX_GROUND_ENEMIES; ++i)
	{
		if (queue[i].type != GENEMY_TYPES::GNO_TYPE)
		{
			queue[i].type = GENEMY_TYPES::GNO_TYPE;
		}
	}
	for (uint i = 0; i < MAX_GROUND_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}
}


void ModuleGroundEnemies::MoveGroundEnemiesRight(bool right)
{
	if (right == true)
	{
		for (uint i = 0; i < MAX_GROUND_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->getvector)
			{
				enemies[i]->left_right_mod += App->map_1->xscrollspeed;
			}
			else if (enemies[i] != nullptr && !enemies[i]->getvector)
			{
				enemies[i]->position.x += App->map_1->xscrollspeed;
			}
		}
	}

	if (right == false)
	{
		for (uint i = 0; i < MAX_GROUND_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->getvector)
			{
				enemies[i]->left_right_mod -= App->map_1->xscrollspeed;
			}
			else if (enemies[i] != nullptr && !enemies[i]->getvector)
			{
				enemies[i]->position.x -= App->map_1->xscrollspeed;
			}
		}
	}
}