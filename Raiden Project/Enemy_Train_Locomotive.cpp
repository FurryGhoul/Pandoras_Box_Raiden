#include "Enemy_Train_Locomotive.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleGroundEnemies.h"

#define PI 3.14159265

Enemy_Train_Locomotive::Enemy_Train_Locomotive(int x, int y, int path) : Enemy(x, y)
{
	hp = 8;
	points = 480;

	// Anmiation pushback's

	// Idle
	horizontal.PushBack({ 2, 15, 48, 24 });
	diagonal.PushBack({ 136, 3, 38, 37 });
	// Hit
	hithorizontal.PushBack({ 2, 55, 48, 24 });
	hitdiagonal.PushBack({ 136, 42, 38, 37 });
	
	// Paths
	if (path == 0)
	{
		movement.PushBack({ -1.5f, 1.0f }, 1000);
		movement.loop = false;

		collider = App->collision->AddCollider({ 0, 0, 48 * 3, 24 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->genemies);
		original_pos.y = -200;
	}
	if (path == 1)
	{
		movement.PushBack({ -1.0f, -1.0f }, 1000);
		movement.loop = false;

		collider = App->collision->AddCollider({ 0, 0, 38 * 3, 37 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->genemies);
		original_pos.y =  820;
	}
		

	train = true;
	
	spritesheet = 8;
	animations = 1;
	original_pos.x = x;
}


void Enemy_Train_Locomotive::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
	position.x += left_right_mod;

	++shoot_time;

	if (sqrtf((distance.y = App->player->position.y - position.y)*(distance.y = App->player->position.y - position.y) + (distance.x = App->player->position.x - position.x)* (distance.x = App->player->position.x - position.x))
		< sqrtf((distance.y = App->player2->position.y - position.y)*(distance.y = App->player2->position.y - position.y) + (distance.x = App->player2->position.x - position.x)* (distance.x = App->player2->position.x - position.x)))
	{
		distance.y = App->player->position.y - position.y;
		distance.x = App->player->position.x - position.x;
		distance1.y = App->player->position.y - position.y;
		distance1.x = App->player->position.x - position.x + 100;
	}
	else
	{
		distance.y = App->player2->position.y - position.y;
		distance.x = App->player2->position.x - position.x;
		distance1.y = App->player2->position.y - position.y;
		distance1.x = App->player2->position.x - position.x + 100;
	}

	// Animation

	animation = &horizontal;
	w = 48 * 3;
	h = 24 * 3;

	distance.x = fabs(distance.x);
	distance.y = fabs(distance.y);
	
	if (movement.steps[movement.GetCurrentStep()].speed.x == -1.5f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f)
	{
		animation = &horizontal;

		if (ishit == true)
		{
			animation = &hithorizontal;
			ishit = false;
		}

		w = 48 * 3;
		h = 24 * 3;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == -1.0f && movement.steps[movement.GetCurrentStep()].speed.y == -1.0f)
	{
		animation = &diagonal;

		if (ishit == true)
		{
			animation = &hitdiagonal;
			ishit = false;
		}

		w = 38 * 3;
		h = 37 * 3;
	}
}
