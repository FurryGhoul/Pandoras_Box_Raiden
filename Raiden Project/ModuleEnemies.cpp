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
#include "Enemy_Grey_Tank.h"
#include "Enemy_Boss_Main.h"
#include "Enemy_Boss_Left_Wing.h"
#include "Enemy_Boss_Right_Wing.h"
#include "Enemy_Boss_Cannon.h"
#include "Enemy_Mine.h"
#include "ModuleAudio_2.h"
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
	sprites2 = App->textures->Load("assets/Bonus Ship1.png");
	sprites3 = App->textures->Load("assets/Tank1.png");
	sprites4 = App->textures->Load("assets/Medium Shooter.png");
	sprites5 = App->textures->Load("assets/Boxes.png");
	sprites6 = App->textures->Load("assets/Kamikaze.png");
	sprites7 = App->textures->Load("assets/LongMegatank.png");
	sprites8 = App->textures->Load("assets/Ship.png");
	sprites9 = App->textures->Load("assets/Light Shooter Kamikaze.png");
	sprites11 = App->textures->Load("assets/Boss 2.png");
	sprites12 = App->textures->Load("assets/Mine.png");
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
				enemies[i]->Draw(sprites);
			else if (enemies[i]->spritesheet == 1) //Bonus Ship
				enemies[i]->Draw(sprites2);
			else if (enemies[i]->spritesheet == 2) //Tank & Ship_Tank
				enemies[i]->Draw(sprites3);
			else if (enemies[i]->spritesheet == 3) //Medium Shooter
				enemies[i]->Draw(sprites4);
			else if (enemies[i]->spritesheet == 4) //Box_Medal & Box_PowerUp
				enemies[i]->Draw(sprites5);
			else if (enemies[i]->spritesheet == 5) //Kamikaze
				enemies[i]->Draw(sprites6);
			else if (enemies[i]->spritesheet == 6) //Long Megatank
				enemies[i]->Draw(sprites7);
			else if (enemies[i]->spritesheet == 7) //Ship
				enemies[i]->Draw(sprites8);
			else if (enemies[i]->spritesheet == 8) //Light Shooter Kamikaze
				enemies[i]->Draw(sprites9);
			else if (enemies[i]->spritesheet == 10) //Boss
				enemies[i]->Draw(sprites11);
			else if (enemies[i]->spritesheet == 11) //Mine
				enemies[i]->Draw(sprites12);
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
			if (enemies[i]->position.y * SCREEN_SIZE < -500 || enemies[i]->position.y * SCREEN_SIZE > 1000 || enemies[i]->position.x * SCREEN_SIZE < -500 || enemies[i]->position.x * SCREEN_SIZE > 1300)
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
		case ENEMY_TYPES::BOSS_MAIN:
			enemies[i] = new Enemy_Boss_Main(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::BOSS_CANNON:
			enemies[i] = new Enemy_Boss_Cannon(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::BOSS_LEFT_WING:
			enemies[i] = new Enemy_Boss_Left_Wing(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::BOSS_RIGHT_WING:
			enemies[i] = new Enemy_Boss_Right_Wing(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::KAMIKAZE:
			enemies[i] = new Enemy_Kamikaze(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::BONUS_SHIP:
			enemies[i] = new Enemy_Bonus_Ship(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::MEDIUM_SHOOTER:
			enemies[i] = new Enemy_Medium_Shooter(App->map_1->xmap + info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::LIGHT_KAMIKAZE:
			bool come_right;
			if (info.x < 500)
			{
				come_right = true;
			}
			else
			{
				come_right = false;
			}
			enemies[i] = new Light_Shooter_Kamikaze(info.x, info.y, info._path, come_right);
			break;
		case ENEMY_TYPES::MINE:
			enemies[i] = new Enemy_Mine(info.x, info.y, info._path);
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
					App->player2->score += 20;
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
			else if (enemies[i]->mediumshooter)
			{
				enemies[i]->ishit = true;
			}
			else if (enemies[i]->ship)
			{
				enemies[i]->ishit = true;
			}
			else if (enemies[i]->shiptank)
			{
				enemies[i]->ishit = true;
			}
			else if (enemies[i]->tank)
			{
				enemies[i]->ishit = true;
				enemies[i]->ishit2 = true;
			}
			else if (enemies[i]->greytank)
			{
				enemies[i]->ishit = true;
				enemies[i]->ishit2 = true;
			}
			else if (enemies[i]->megatank)
			{
				enemies[i]->ishit = true;
				enemies[i]->ishit2 = true;
			}
			else if (enemies[i]->longmegatank)
			{
				enemies[i]->ishit = true;
				enemies[i]->ishit2 = true;
				enemies[i]->ishit3 = true;
				enemies[i]->ishit4 = true;
			}
			else if (enemies[i]->mine)
			{
				enemies[i]->ishit = true;
			}
			else if (enemies[i]->bossmain || enemies[i]->bossleftwing || enemies[i]->bossrightwing || enemies[i]->bosscannon)
				enemies[i]->ishit = true;
			

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

			if ((!enemies[i]->bossmain && !enemies[i]->bossleftwing && !enemies[i]->bossrightwing && !enemies[i]->bosscannon) && (c2->bullettype == 3 || c2->bullettype == 4))
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

				if (enemies[i]->bossleftwing)
					App->map_1->leftwingalive = false;

				if (enemies[i]->bossrightwing)
					App->map_1->rightwingalive = false;

				if (enemies[i]->bosscannon)
					App->map_1->cannonalive = false;

				if (enemies[i]->lightshooter || enemies[i]->kamikaze || enemies[i]->light_kamikaze)
				{ 
				  App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
				  //Mix_PlayChannel(-1, App->audio_2->fx_light_explosion, 0);
                }
				else if (enemies[i]->tank)
				{
					App->gexplosion->AddGroundExplosion(App->gexplosion->tank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
				}
				else if (enemies[i]->greytank)
				{
					App->gexplosion->AddGroundExplosion(App->gexplosion->tank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE, -1, 0, 1.5);
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
  					Mix_PlayChannel(-1, App->audio_2->fx_heavy_explosion, 0);
				}
				else if (enemies[i]->bossleftwing || enemies[i]->bossrightwing || enemies[i]->bosscannon)
				{
					App->particles->AddParticle(App->particles->bonusmedium_explosion, enemies[i]->position.x - 60, enemies[i]->position.y - 60, COLLIDER_NONE);
				}
				else if (enemies[i]->mediumshooter)
				{
					App->particles->AddParticle(App->particles->bonusmedium_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
 					Mix_PlayChannel(-1, App->audio_2->fx_heavy_explosion, 0);
				}
				
				else if (enemies[i]->medalbox)
				{
					App->powerups->AddPowerUp(POWERUP_TYPES::MEDAL, enemies[i]->position.x + 25, enemies[i]->position.y + 5);
					App->gexplosion->AddGroundExplosion(App->gexplosion->shiptank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
				}

				else if (enemies[i]->powerupbox)
				{
					App->powerups->AddPowerUp(POWERUP_TYPES::MISSILEUP, enemies[i]->position.x , enemies[i]->position.y);
					App->gexplosion->AddGroundExplosion(App->gexplosion->shiptank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
				}		
				else if (enemies[i]->mine)
				{
					App->gexplosion->AddGroundExplosion(App->gexplosion->shiptank_explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
					App->particles->AddParticle(App->particles->enemyshot, enemies[i]->position.x+ enemies[i]->w/2, enemies[i]->position.y + enemies[i]->h/2, COLLIDER_ENEMY_SHOT, 0,10,0 );


					App->particles->AddParticle(App->particles->enemyshot, enemies[i]->position.x + enemies[i]->w  / 2, enemies[i]->position.y + enemies[i]->h / 2, COLLIDER_ENEMY_SHOT, 0, 8, -5, false, true);
					App->particles->AddParticle(App->particles->enemyshot, enemies[i]->position.x + enemies[i]->w / 2, enemies[i]->position.y + enemies[i]->h / 2, COLLIDER_ENEMY_SHOT, 0, 5, -8, false, true);


					App->particles->AddParticle(App->particles->enemyshot, enemies[i]->position.x + enemies[i]->w / 2, enemies[i]->position.y + enemies[i]->h  / 2, COLLIDER_ENEMY_SHOT, 0,  0,10, false, true);


					App->particles->AddParticle(App->particles->enemyshot, enemies[i]->position.x + enemies[i]->w / 2, enemies[i]->position.y + enemies[i]->h / 2, COLLIDER_ENEMY_SHOT, 0, -8, 5, false, true);
					App->particles->AddParticle(App->particles->enemyshot, enemies[i]->position.x + enemies[i]->w  / 2, enemies[i]->position.y + enemies[i]->h / 2, COLLIDER_ENEMY_SHOT, 0, -5, 8, false, true);


					App->particles->AddParticle(App->particles->enemyshot, enemies[i]->position.x + enemies[i]->w / 2, enemies[i]->position.y + enemies[i]->h / 2, COLLIDER_ENEMY_SHOT, 0, 0, -10, false, true);


					App->particles->AddParticle(App->particles->enemyshot, enemies[i]->position.x + enemies[i]->w / 2, enemies[i]->position.y + enemies[i]->h  / 2, COLLIDER_ENEMY_SHOT, 0, 8, 5, false, true);
			     	App->particles->AddParticle(App->particles->enemyshot, enemies[i]->position.x + enemies[i]->w / 2, enemies[i]->position.y + enemies[i]->h  / 2, COLLIDER_ENEMY_SHOT, 0, 5, 8, false, true);


				    App->particles->AddParticle(App->particles->enemyshot, enemies[i]->position.x + enemies[i]->w / 2, enemies[i]->position.y + enemies[i]->h / 2, COLLIDER_ENEMY_SHOT, 0,-10 ,0, false, true);


					App->particles->AddParticle(App->particles->enemyshot, enemies[i]->position.x + enemies[i]->w / 2, enemies[i]->position.y + enemies[i]->h  / 2, COLLIDER_ENEMY_SHOT, 0, -8, -5, false, true);
					App->particles->AddParticle(App->particles->enemyshot, enemies[i]->position.x + enemies[i]->w / 2, enemies[i]->position.y + enemies[i]->h / 2, COLLIDER_ENEMY_SHOT, 0, -5, -8, false, true);
	        	}




				if (enemies[i]->bossmain)
				{
					DestroyBossParts();
					App->map_1->won = true;
				}

				if (!(enemies[i]->bossmain))
				{
					delete enemies[i];
					enemies[i] = nullptr;
					break;
				}
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

void ModuleEnemies::SetPos()
{
	//Identify main part
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->bossmain)
		{
			bossmain = i;
			break;
		}
	}
	//Set positions
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->bossleftwing)
		{
			enemies[i]->position.x = enemies[bossmain]->position.x - 32 * 3;
			enemies[i]->position.y = enemies[bossmain]->position.y + 32 * 3;
		}
		else if (enemies[i] != nullptr && enemies[i]->bossrightwing)
		{
			enemies[i]->position.x = enemies[bossmain]->position.x + 96 * 3;
			enemies[i]->position.y = enemies[bossmain]->position.y + 32 * 3;
		}
		else if (enemies[i] != nullptr && enemies[i]->bosscannon)
		{
			enemies[i]->position.x = enemies[bossmain]->position.x + 32 * 3;
			enemies[i]->position.y = enemies[bossmain]->position.y + 34 * 3;
		}
	}
}

void ModuleEnemies::DestroyBossParts()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::BOSS_CANNON || queue[i].type == ENEMY_TYPES::BOSS_RIGHT_WING || queue[i].type == ENEMY_TYPES::BOSS_LEFT_WING)
		{
			queue[i].type = ENEMY_TYPES::NO_TYPE;
		}
	}
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && (enemies[i]->bosscannon || enemies[i]->bossleftwing || enemies[i]->bossrightwing))
		{
			App->particles->AddParticle(App->particles->bonusmedium_explosion, enemies[i]->position.x - 60, enemies[i]->position.y - 60, COLLIDER_NONE);
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