#include "Enemy_Kamikaze.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"

#define PI 3.14159265

Enemy_Kamikaze::Enemy_Kamikaze(int x, int y, int path) : Enemy(x, y)
{
	hp = 1;
	points = 130;
	kamikaze = true;
	w = 32 * 3;
	h = 32 * 3;

	//Animation

	turn.speed = 0.7f;

	// Anmiation pushback's

	//Coming from left
	turn.PushBack({ 1, 98, 32, 32 });
	turn.PushBack({ 34, 98, 32, 32 });
	turn.PushBack({ 67, 98, 32, 32 });
	turn.PushBack({ 100, 98, 32, 32 });
	turn.PushBack({ 133, 98, 32, 32 });

	if (path == 0)
	{
		movement.PushBack({ 0.0f, 4.0f }, 200);
	}

	//Coming from right
	turn1.PushBack({ 1, 138, 32, 32 });
	turn1.PushBack({ 34, 138, 32, 32 });
	turn1.PushBack({ 67, 138, 32, 32 });
	turn1.PushBack({ 100, 138, 32, 32 });
	turn1.PushBack({ 133, 138, 32, 32 });

	collider = App->collision->AddCollider({ 0, 0, 24 * 3 - 5, 24 * 3 + 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	spritesheet = 5;
	animations = 1;
	original_pos.x = x;
	original_pos.y = -50;
	animation = &turn;
}

void Enemy_Kamikaze::MoveShoot()
{
	if (!colliderrezise)
	{
		collider->SetSize(w, h);
		colliderrezise = true;
	}
	if (getvector)
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

	if (SDL_GetTicks() - time > 500)
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