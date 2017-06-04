#include "Enemy_Kamikaze.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"
#include "ModuleShadows.h"

#define PI 3.14159265

Enemy_Kamikaze::Enemy_Kamikaze(int x, int y, int path) : Enemy(x, y)
{
	hp = 1;
	points = 130;
	kamikaze = true;

	//Animation

	turn.speed = 0.7f;
	turn1.speed = 0.7f;
	deploying.speed = 0.1f;
	deploying1.speed = 0.1f;

	// Anmiation pushback's

	//Coming from left
	turn.PushBack({ 1, 98, 32, 32 });
	turn.PushBack({ 34, 98, 32, 32 });
	turn.PushBack({ 67, 98, 32, 32 });
	turn.PushBack({ 100, 98, 32, 32 });
	turn.PushBack({ 133, 98, 32, 32 });

	//Coming from left
	deploying.PushBack({ 2, 2, 32, 39 });
	deploying.PushBack({ 37, 2, 32, 39 });
	deploying.PushBack({ 72, 2, 32, 39 });
	deploying.PushBack({ 107, 2, 32, 39 });
	deploying.PushBack({ 142, 2, 32, 39 });
	deploying.PushBack({ 177, 2, 32, 39 });
	deploying.PushBack({ 212, 2, 32, 39 });

	//Coming from right
	deploying1.PushBack({ 2, 50, 32, 39 });
	deploying1.PushBack({ 37, 50, 32, 39 });
	deploying1.PushBack({ 72, 50, 32, 39 });
	deploying1.PushBack({ 107, 50, 32, 39 });
	deploying1.PushBack({ 142, 50, 32, 39 });
	deploying1.PushBack({ 177, 50, 32, 39 });
	deploying1.PushBack({ 212, 50, 32, 39 });

	//Coming from right
	turn1.PushBack({ 1, 138, 32, 32 });
	turn1.PushBack({ 34, 138, 32, 32 });
	turn1.PushBack({ 67, 138, 32, 32 });
	turn1.PushBack({ 100, 138, 32, 32 });
	turn1.PushBack({ 133, 138, 32, 32 });

	if (path == 0 || path == 9)
	{
		collider = App->collision->AddCollider({ 0, 0, 24 * 3 - 5, 24 * 3 + 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
		movement.PushBack({ 0.0f, 4.0f }, 200);
		w = 32 * 3;
		h = 32 * 3;
	}
	else if (path == 1)
	{
		movement.PushBack({ 3.0f, -1.5f }, 100);
		w = 32 * 3;
		h = 39 * 3;
		bosskamikaze = true;
	}
	else if (path == 2)
	{
		movement.PushBack({ 2.0f, -2.0f }, 100);
		w = 32 * 3;
		h = 39 * 3;
		bosskamikaze = true;
	}
	else if (path == 3)
	{
		movement.PushBack({ 2.5f, 1.0f }, 100);
		w = 32 * 3;
		h = 39 * 3;
		bosskamikaze = true;
	}
	else if (path == 4)
	{
		movement.PushBack({ 1.5f, 1.5f }, 100);
		w = 32 * 3;
		h = 39 * 3;
		bosskamikaze = true;
	}
	else if (path == 5)
	{
		movement.PushBack({ -3.0f, -1.5f }, 100);
		w = 32 * 3;
		h = 39 * 3;
		bosskamikaze = true;
	}
	else if (path == 6)
	{
		movement.PushBack({ -2.0f, -2.0f }, 100);
		w = 32 * 3;
		h = 39 * 3;
		bosskamikaze = true;
	}
	else if (path == 7)
	{
		movement.PushBack({ -2.5f, 1.0f }, 100);
		w = 32 * 3;
		h = 39 * 3;
		bosskamikaze = true;
	}
	else if (path == 8)
	{
		movement.PushBack({ -1.5f, 1.5f }, 100);
		w = 32 * 3;
		h = 39 * 3;
		bosskamikaze = true;
	}

	spritesheet = 5;
	animations = 1;
	original_pos.x = x;
	
	if (bosskamikaze)
	{
		delay = 0;
		original_pos.y = y;
	}
	else
	{
		delay = 500;
		original_pos.y = -50;
	}

	if (path == 0)
		animation = &turn;
	else if (path == 9)
		animation = &turn1;
	else if (path >= 1 && path <= 4)
		animation = &deploying;
	else if (path >= 5 && path <= 8)
		animation = &deploying1;

	time2 = SDL_GetTicks();
}

void Enemy_Kamikaze::MoveShoot()
{
	shadowregulator++;
	if (!bosskamikaze)
	{
		if (shadowregulator % 2 == 0)
		{
			if (shadowdirection == 0)
				App->shadows->AddShadow(App->shadows->Kamikazes, position.x, position.y, 40 * 3, 40 * 3);
		}
		if (!colliderrezise)
		{
			collider->SetSize(w, h);
			colliderrezise = true;
		}
		if (getvector && !deployed)
		{
			position = original_pos + movement.GetCurrentPosition();
			position.x += left_right_mod;
		}

		if (allowtime)
		{
			time = SDL_GetTicks();
			allowtime = false;
		}

		//Detecting distance
		if (sqrtf((distance.y = App->player->position.y - position.y)*(distance.y = App->player->position.y - position.y) + (distance.x = App->player->position.x - position.x)* (distance.x = App->player->position.x - position.x))
			< sqrtf((distance.y = App->player2->position.y - position.y)*(distance.y = App->player2->position.y - position.y) + (distance.x = App->player2->position.x - position.x)* (distance.x = App->player2->position.x - position.x)))
		{
			distance.y = App->player->position.y - position.y;
			distance.x = App->player->position.x - position.x;
		}

		else
		{
			distance.y = App->player2->position.y - position.y;
			distance.x = App->player2->position.x - position.x;
		}

		if (SDL_GetTicks() - time > delay)
		{
			if (getvector)
			{
				vector.x = distance.x * (13 / sqrtf(distance.x*distance.x + distance.y*distance.y));
				vector.y = distance.y * (13 / sqrtf(distance.x*distance.x + distance.y*distance.y));
				getvector = false;
			}

			position.x += vector.x;
			position.y += vector.y;
		}
	}
	else
	{
		if ((SDL_GetTicks() - time2) < 1150)
		{
			position = original_pos + movement.GetCurrentPosition();
			position.x += left_right_mod;
		}
		else
		{
			bosskamikaze = false;
			deployed = true;

			if (animation == &deploying)
			{
				animation = &turn;
			}
			else
			{
				animation = &turn1;
			}

			h = 32 * 3;
			position.y += (7 * 3);
			collider = App->collision->AddCollider({ 0, 0, 24 * 3 - 5, 24 * 3 + 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
		}
	}
}