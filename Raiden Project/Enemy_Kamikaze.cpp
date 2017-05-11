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
		movement.PushBack({ 0.0f, 6.0f }, 200);
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
	if (getvector)
	{
		position = original_pos + movement.GetCurrentPosition();
	}

	if (allowtime)
	{
		time = SDL_GetTicks();
		allowtime = false;
	}


	//Detecting distance
	if (sqrtf((distance.y = App->player->position.y - 22 - position.y - 22 * 3)*(distance.y = App->player->position.y - 22 - position.y - 22 * 3) + (distance.x = App->player->position.x - position.x + 22)* (distance.x = App->player->position.x - position.x + 22))
		< sqrtf((distance.y = App->player2->position.y - 22 - position.y - 22 * 3)*(distance.y = App->player2->position.y - 22 - position.y - 22 * 3) + (distance.x = App->player2->position.x - position.x + 22)* (distance.x = App->player2->position.x - position.x + 22)))
	{
		distance.y = App->player->position.y - 22 - position.y - 22 * 3;
		distance.x = App->player->position.x - position.x + 22;
	}

	else
	{
		distance.y = App->player2->position.y - 22 - position.y - 22 * 3;
		distance.x = App->player2->position.x - position.x + 22;
	}

	if (SDL_GetTicks() - time > 500)
	{
		if (getvector)
		{
			vector.x = distance.x;
			vector.y = distance.y;
			vector.x *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
			vector.y *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
			getvector = false;
		}


		position.x += vector.x;
		position.y += vector.y;
	}
}