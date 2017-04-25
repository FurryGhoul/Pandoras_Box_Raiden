#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "Enemy_Light_Shooter.h"
#include "Enemy_Bonus_Ship.h"
#include "Tank.h"
#include "Turret.h"
#include "ModulePowerUps.h"
#define SPAWN_MARGIN 50

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
	sprites3 = App->textures->Load("assets/Tank.png"); 
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
		   if (enemies[i]->spriteshit == 0)
		   {
		       enemies[i]->Draw(sprites);
		   }
		   if (enemies[i]->spriteshit == 1)
		   {
			   enemies[i]->Draw(sprites2);
		   }
		   if (enemies[i]->spriteshit == 2)
		   {
			   enemies[i]->Draw(sprites3);
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
			if (enemies[i]->position.y * SCREEN_SIZE < (App->render->camera.y) - SPAWN_MARGIN)
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
			enemies[i] = new Enemy_Light_Shooter(info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::BONUS_SHIP:
			enemies[i] = new Enemy_Bonus_Ship(info.x, info.y, info._path);
			break;
		case ENEMY_TYPES::TANK:
			enemies[i] = new Tank(info.x, info.y, info._path);
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->hp--;
			if (enemies[i]->hp == 0)
			{
				if (c2->bullettype == 1)
				{
					App->player->score += enemies[i]->points;
				}

				if (c2->bullettype == 2)
				{
					App->player2->score += enemies[i]->points;
				}
				if (enemies[i]->lightshooter)
				{ 
				App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
                }
				if (enemies[i]->bonusplane)
				{
					App->powerups->AddPowerUp(POWERUP_TYPES::REDUP, enemies[i]->position.x, enemies[i]->position.y);
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
			if (enemies[i] != nullptr)
			{
				enemies[i]->left_right_mod += 6;
			}
		}
	}

	if (right == false)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr)
			{
				enemies[i]->left_right_mod-= 6;
			}
		}
	}
}