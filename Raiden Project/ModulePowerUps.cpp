#include "ModulePowerUps.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "PowerUp.h"
#include "RedUp.h"
#include "BlueUp.h"
#include "Medals.h"
#include "MissileUp.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleMap1.h"
#include "ModuleAudio_2.h"

#define SPAWN_MARGIN 50
#define MAX_POWERUP_LVL 8
#define MAX_MISSILE_LEVEL 4

ModulePowerUps::ModulePowerUps()
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
		powerups[i] = nullptr;
}

ModulePowerUps::~ModulePowerUps()
{
}

bool ModulePowerUps::Init()
{
	sprites = App->textures->Load("Assets/Powerups and Bonuses.png");

	return true;
}

update_status ModulePowerUps::PreUpdate()
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (queue[i].type != POWERUP_TYPES::NO_TYPE)
		{
			if (queue[i].y * SCREEN_SIZE > App->render->camera.y - SPAWN_MARGIN)
			{
				LOG("Spawning powerup at %d", queue[i].y* SCREEN_SIZE);
				SpawnPowerUp(queue[i]);
				queue[i].type = POWERUP_TYPES::NO_TYPE;

			}
		}
	}

	return UPDATE_CONTINUE;
}

update_status ModulePowerUps::Update()
{

	for (uint i = 0; i < MAX_POWERUPS; ++i)

		if (powerups[i] != nullptr) powerups[i]->Move();


	for (uint i = 0; i < MAX_POWERUPS; ++i)
		if (powerups[i] != nullptr) powerups[i]->Draw(sprites);


	time_swich++;
	if (time_swich % 300 == 0)
	{
		Switch();
	}

	return UPDATE_CONTINUE;
}

update_status ModulePowerUps::PostUpdate()
{


	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePowerUps::CleanUp()
{
	LOG("Freeing all powerups");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			delete powerups[i];
			powerups[i] = nullptr;
		}
	}

	return true;
}

bool ModulePowerUps::AddPowerUp(POWERUP_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (queue[i].type == POWERUP_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModulePowerUps::SpawnPowerUp(const PowerUpInfo& info)
{
	// find room for the new powerup
	uint i = 0;
	for (; powerups[i] != nullptr && i < MAX_POWERUPS; ++i);

	if (i != MAX_POWERUPS)
	{
		switch (info.type)
		{
		case POWERUP_TYPES::REDUP:
			powerups[i] = new RedUp(info.x, info.y);
			break;
		case POWERUP_TYPES::MEDAL:
			powerups[i] = new Medals(info.x, info.y);
			break;
		case POWERUP_TYPES::BLUEUP:
			powerups[i] = new BlueUp(info.x, info.y);
			break;
		case POWERUP_TYPES::MISSILEUP:
			powerups[i] = new MissileUp(info.x, info.y);
			break;
		}
	}
}

void ModulePowerUps::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr && powerups[i]->GetCollider() == c1)
		{
			if (c2->bullettype == 3) //Collider player 1
			{
				if (powerups[i]->redp == true) //Collider RedUp
				{
					App->player->red = true;
					if (App->player->powerup_level < MAX_POWERUP_LVL)
					{
						App->player->powerup_level++;
					}

					else if (App->player->powerup_level >= MAX_POWERUP_LVL)
					{
						App->player->score += 5000;
					}
				}
				if (powerups[i]->bluep == true) // Collider BlueUp
				{
					App->player->red = false;
					if (App->player->powerup_level < MAX_POWERUP_LVL)
					{
						App->player->powerup_level++;
					}

					else if (App->player->powerup_level >= MAX_POWERUP_LVL)
					{
						App->player->score += 5000;
					}
				}
				if (powerups[i]->medal == true) //Collider Medal
				{
					App->player->score += 100;
					Mix_PlayChannel(-1, App->audio_2->fx_medal, 0);
				}

				if (powerups[i]->missilep == true) //Collider Missile
				{
					if (App->player->missile_powerup_level < MAX_MISSILE_LEVEL)
					{
     					App->player->missile_powerup_level++;
					}

					else if (App->player->missile_powerup_level >= MAX_MISSILE_LEVEL)
					{
						App->player->score += 5000;
					}
				}
			}


			if (c2->bullettype == 4) //Collider player 2
			{
				App->player2->red = true;
				if (powerups[i]->redp == true) //Collider RedUp
				{
					if (App->player2->powerup_level < MAX_POWERUP_LVL)
					{
						App->player2->powerup_level++;
					}

					else if (App->player2->powerup_level >= MAX_POWERUP_LVL)
					{
						App->player2->score += 5000;
					}
				}

				if (powerups[i]->bluep == true) // Collider BlueUp
				{
					App->player2->red = false;
					if (App->player2->powerup_level < MAX_POWERUP_LVL)
					{
						App->player2->powerup_level++;
					}

					else if (App->player2->powerup_level >= MAX_POWERUP_LVL)
					{
						App->player2->score += 5000;
					}
				}

				if (powerups[i]->medal == true) //Collider Medal
				{
					App->player2->score += 100;
					Mix_PlayChannel(-1, App->audio_2->fx_medal, 0);
				}
				if (powerups[i]->missilep == true) //Collider Missile
				{
					if (App->player2->missile_powerup_level < MAX_MISSILE_LEVEL)
					{
						App->player2->missile_powerup_level++;
					}

					else if (App->player2->missile_powerup_level >= MAX_MISSILE_LEVEL)
					{
						App->player2->score += 5000;
					}
				}
			}
			powerups[i]->OnCollision(c2);
			delete powerups[i];
			powerups[i] = nullptr;
			break;
		}
	}
}
void ModulePowerUps::ErasePowerUps()
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			delete powerups[i];
			powerups[i] = nullptr;
		}
	}
}

void ModulePowerUps::MovePowerUpsRight(bool right)
{
	if (right == true)
	{
		for (uint i = 0; i < MAX_POWERUPS; ++i)
		{
			if (powerups[i] != nullptr)
			{
				if (!powerups[i]->medal)
				{ 
				powerups[i]->position.x += App->map_1->xscrollspeed;
				}
				else
				{
					powerups[i]->left_right_mod += App->map_1->xscrollspeed;
				}
			}
		}
	}

	if (right == false)
	{
		for (uint i = 0; i < MAX_POWERUPS; ++i)
		{
			if (powerups[i] != nullptr)
			{
				if (!powerups[i]->medal)
				{
					powerups[i]->position.x -= App->map_1->xscrollspeed;
				}
				else
				{
					powerups[i]->left_right_mod -= App->map_1->xscrollspeed;
				}
			}
		}
	}
}

void ModulePowerUps::Switch()
{
	PowerUpInfo info;
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr && powerups[i]->missilep != true && powerups[i]->medal != true)
		{
			info.x = powerups[i]->position.x;
			info.y = powerups[i]->position.y;
			info.centerx = powerups[i]->center.x;
			info.centery = powerups[i]->center.y;
			info.angle = powerups[i]->angle;
			if (powerups[i]->bluep == true)
			{
				info.type = POWERUP_TYPES::REDUP;
			}
			if (powerups[i]->redp == true)
			{
				info.type = POWERUP_TYPES::BLUEUP;
			}
			
			delete powerups[i];
			powerups[i] = nullptr;

			switch (info.type)
			{
			case POWERUP_TYPES::REDUP:
				powerups[i] = new RedUp(info.x, info.y, info.centerx, info.centery, info.angle, false);
				break;
			case POWERUP_TYPES::BLUEUP:
				powerups[i] = new BlueUp(info.x, info.y, info.centerx, info.centery, info.angle, false);
				break;
			}
		}
	}
}
