#include "ModulePowerUps.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "PowerUp.h"
#include "RedUp.h"
#define SPAWN_MARGIN 50

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
		if (powerups[i] != nullptr) powerups[i]->Draw(sprites);

	return UPDATE_CONTINUE;
}

update_status ModulePowerUps::PostUpdate() 
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			if (powerups[i]->position.y * SCREEN_SIZE < (App->render->camera.y) - SPAWN_MARGIN)
			{
				LOG("DeSpawning powerup at %d", powerups[i]->position.y * SCREEN_SIZE);
				delete powerups[i];
				powerups[i] = nullptr;
			}
		}
	}

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
		}
	}
}

void ModulePowerUps::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr && powerups[i]->GetCollider() == c1)
		{
			powerups[i]->OnCollision(c2);
			delete powerups[i];
			powerups[i] = nullptr;
			break;
		}
	}
}