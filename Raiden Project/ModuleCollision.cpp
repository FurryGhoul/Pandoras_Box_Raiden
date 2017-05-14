#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;
	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_WALL][COLLIDER_TANK] = false;
	matrix[COLLIDER_WALL][COLLIDER_GOD] = false;
	matrix[COLLIDER_WALL][COLLIDER_BOMB] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POWER_UP] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_TANK] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_BOMB] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_TANK] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_GOD] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_BOMB] = true;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_TANK] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BOMB] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_TANK] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_GOD] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BOMB] = true;

	matrix[COLLIDER_POWER_UP][COLLIDER_WALL] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_TANK] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_GOD] = true;
	matrix[COLLIDER_POWER_UP][COLLIDER_BOMB] = false;

	matrix[COLLIDER_TANK][COLLIDER_TANK] = false;
	matrix[COLLIDER_TANK][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_TANK][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_TANK][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_TANK][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_TANK][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_TANK][COLLIDER_WALL] = false;
	matrix[COLLIDER_TANK][COLLIDER_GOD] = false;
	matrix[COLLIDER_TANK][COLLIDER_BOMB] = true;

	matrix[COLLIDER_GOD][COLLIDER_GOD] = false;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_GOD][COLLIDER_POWER_UP] = true;
	matrix[COLLIDER_GOD][COLLIDER_WALL] = false;
	matrix[COLLIDER_GOD][COLLIDER_TANK] = false;
	matrix[COLLIDER_GOD][COLLIDER_BOMB] = false;

	matrix[COLLIDER_BOMB][COLLIDER_GOD] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BOMB][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_BOMB][COLLIDER_WALL] = false;
	matrix[COLLIDER_BOMB][COLLIDER_TANK] = false;
	matrix[COLLIDER_BOMB][COLLIDER_BOMB] = false;

}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
Collider* c1;
Collider* c2;

for (uint i = 0; i < MAX_COLLIDERS; ++i)
{
	// skip empty colliders
	if (colliders[i] == nullptr)
		continue;

	c1 = colliders[i];

	// avoid checking collisions already checked
	for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
	{
		// skip empty colliders
		if (colliders[k] == nullptr)
			continue;

		c2 = colliders[k];

		if (c1->CheckCollision(c2->rect) == true)
		{
			
			if (matrix[c1->type][c2->type] && c1->callback)
				c1->callback->OnCollision(c1, c2);
			
			
			if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			
		}
	}
}

DebugDraw();

return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if ((App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN && !App->input->gpad) || (App->input->gamepad[7] == KEY_DOWN && App->input->gpad))
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha,false);
			break;
		case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha, false);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha, false);
			break;
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha, false);
			break;
		case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha, false);
			break;
		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha,false);
			break;
		case COLLIDER_POWER_UP: // grey
			App->render->DrawQuad(colliders[i]->rect, 128, 128, 128, alpha, false);
			break;
		case COLLIDER_TANK: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha, false);
			break;
		case COLLIDER_GOD: // pink
			App->render->DrawQuad(colliders[i]->rect, 255, 20, 147, alpha, false);
			break;
		case COLLIDER_BOMB: // purple
			App->render->DrawQuad(colliders[i]->rect, 191, 5, 247, alpha, false);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback, int bullettype, int damage)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback, bullettype, damage);
			break;
		}
	}

	return ret;
}

void ModuleCollision::Erase_Non_Player_Colliders()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->type != COLLIDER_GOD && colliders[i]->type != COLLIDER_PLAYER)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	if (r.y + r.h > rect.y && r.y < rect.y + rect.h && r.x + r.w > rect.x && r.x < rect.x + rect.w)
	{
		return true;
	}

	else
	{
		return false;
	}
}