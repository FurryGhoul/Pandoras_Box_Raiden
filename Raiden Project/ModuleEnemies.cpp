#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
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
#include "Enemy_Boss_Kamikaze.h"
#define SPAWN_MARGIN 100

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Init()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("assets/Light Shooter.png");
	sprites2 = App->textures->Load("assets/Bonus Ship.png");
	sprites3 = App->textures->Load("assets/Tank1.png");
	sprites4 = App->textures->Load("assets/Medium Shooter.png");
	sprites5 = App->textures->Load("assets/Boxes.png");
	sprites6 = App->textures->Load("assets/Kamikaze.png");
	sprites7 = App->textures->Load("assets/LongMegatank.png");
	sprites8 = App->textures->Load("assets/Ship.png");
	sprites9 = App->textures->Load("assets/Light Shooter Kamikaze.png");
	sprites10 = App->textures->Load("assets/Megatank.png");
	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (queue[i].y * SCREEN_SIZE > App->render->camera.y - SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", queue[i].y* SCREEN_SIZE);
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->MoveShoot();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) 
		{ 
		   if (enemies[i]->spritesheet == 0) //Light Shooter
		   {
		       enemies[i]->Draw(sprites);
		   }
		   if (enemies[i]->spritesheet == 1) //Bonus Ship
		   {
			   enemies[i]->Draw(sprites2);
		   }
		   if (enemies[i]->spritesheet == 2) //Tank & Ship_Tank
		   {
			   enemies[i]->Draw(sprites3);
		   }
		   if (enemies[i]->spritesheet == 3) //Medium Shooter
		   {
			   enemies[i]->Draw(sprites4);
		   }
		   if (enemies[i]->spritesheet == 4) //Box_Medal & Box_PowerUp
		   {
			   enemies[i]->Draw(sprites5);
		   }
		   if (enemies[i]->spritesheet == 5) //Kamikaze
		   {
			   enemies[i]->Draw(sprites6);
		   }
		   if (enemies[i]->spritesheet == 6) //Long Megatank
		   {
			   enemies[i]->Draw(sprites7);
		   }
		   if (enemies[i]->spritesheet == 7) //Ship
		   {
			   enemies[i]->Draw(sprites8);
		   }
		   if (enemies[i]->spritesheet == 8) //Light Shooter Kamikaze
		   {
			   enemies[i]->Draw(sprites9);
		   }
		   if (enemies[i]->spritesheet == 9) //Megatank
		   {
			   enemies[i]->Draw(sprites10);
		   }
        }
	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.y * SCREEN_SIZE < -300 || enemies[i]->position.y * SCREEN_SIZE > 1000)
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
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(int path, ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
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


void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::LIGHT_SHOOTER:
			enemies[i] = new Enemy_Light_Shooter(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::KAMIKAZE:
			enemies[i] = new Enemy_Kamikaze(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::BOSSKAMIKAZE:
			enemies[i] = new Enemy_Boss_Kamikaze(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::BONUS_SHIP:
			enemies[i] = new Enemy_Bonus_Ship(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::TANK:
			enemies[i] = new Tank(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::SHIP_TANK:
			enemies[i] = new Enemy_Ship_Tank(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::SHIP:
			enemies[i] = new Enemy_Ship(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::MEDIUM_SHOOTER:
			enemies[i] = new Enemy_Medium_Shooter(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::LONG_MEGATANK:
			enemies[i] = new Enemy_Long_Megatank(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::MEGATANK:
			enemies[i] = new Enemy_Megatank(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::BOX_MEDAL:
			enemies[i] = new Box_Medal(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::BOX_POWERUP:
			enemies[i] = new Box_PowerUp(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::LIGHT_KAMIKAZE:
			enemies[i] = new Light_Shooter_Kamikaze(App->map_1->xmap + info.x, info.y, info._path);
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			if (c2->bullettype == 27)
			{
				if (SDL_GetTicks() - time >= 250)
					enemies[i]->bombimmunity = false;
					
				if (!enemies[i]->bombimmunity)
				{
					enemies[i]->hp -= c2->damage;
					enemies[i]->bombimmunity = true;
					time = SDL_GetTicks();
				}


			}
			else
			{
				enemies[i]->hp -= c2->damage;
			}

			if (enemies[i]->bonusplane)
			{
				enemies[i]->ishit = true;
				enemies[i]->ishit2 = true;
			}
			if (enemies[i]->mediumshooter)
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
					App->gexplosion->AddGroundExplosion(App->gexplosion->shiptank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
					enemies[i]->turretexploded == true;
				}
				else if (enemies[i]->shiptank && enemies[i]->turretexploded == false)
				{
					App->gexplosion->AddGroundExplosion(App->gexplosion->shiptank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
					enemies[i]->turretexploded == true;
				}
			}

			if (enemies[i]->hp <= 0)
			{
				if (c2->bullettype == 1)
				{
					App->player->score += enemies[i]->points;
				}

				else if (c2->bullettype == 2)
				{
					App->player2->score += enemies[i]->points;
				}

				if (enemies[i]->lightshooter)
				{ 
				  App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
                }
				else if (enemies[i]->tank)
				{
					App->gexplosion->AddGroundExplosion(App->gexplosion->tank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
				}
				else if (enemies[i]->shiptank)
				{
					App->gexplosion->AddGroundExplosion(App->gexplosion->shiptank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
				}
				else if (enemies[i]->ship)
				{
					App->gexplosion->AddGroundExplosion(App->gexplosion->ship_explosion, enemies[i]->position.x - 70, enemies[i]->position.y, COLLIDER_NONE);
					App->powerups->AddPowerUp(POWERUP_TYPES::REDUP, enemies[i]->position.x - 70, enemies[i]->position.y);
				}
				else if (enemies[i]->bonusplane)
				{
					App->powerups->AddPowerUp(POWERUP_TYPES::REDUP, enemies[i]->position.x, enemies[i]->position.y);
					App->particles->AddParticle(App->particles->bonusmedium_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
				}
				else if (enemies[i]->mediumshooter)
				{
					App->particles->AddParticle(App->particles->bonusmedium_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
				}
				
				else if (enemies[i]->medalbox)
				{
					App->powerups->AddPowerUp(POWERUP_TYPES::MEDAL, enemies[i]->position.x, enemies[i]->position.y);
				}

				else if (enemies[i]->powerupbox)
				{
					App->powerups->AddPowerUp(POWERUP_TYPES::MISSILEUP, enemies[i]->position.x - 120, enemies[i]->position.y - 110);
				}				

				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}
	}
}

void ModuleEnemies::EraseEnemies()
{
	
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = ENEMY_TYPES::NO_TYPE;
		}
	}
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}
}

void ModuleEnemies::MoveEnemiesRight(bool right)
{
	if (right == true)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
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
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->getvector)
			{
				enemies[i]->left_right_mod-= App->map_1->xscrollspeed;
			}
			else if (enemies[i] != nullptr && !enemies[i]->getvector)
			{
				enemies[i]->position.x -= App->map_1->xscrollspeed;
			}
		}
	}
}