#include "Enemy_Train_Locomotive.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"

#define PI 3.14159265

Enemy_Train_Locomotive::Enemy_Train_Locomotive(int x, int y, int path) : Enemy(x, y)
{
	hp = 17;
	points = 980;

	// Anmiation pushback's

	// Idle
	flyi.PushBack({ 329, 47, 73, 54 });
	flyi.PushBack({ 407, 47, 73, 54 });
	flyi.speed = 0.2f;

	movement.PushBack({ 3.0f, 4.0f }, 100);
	movement.PushBack({ 0.0f, -5.0f }, 500);
	movement.loop = false;

	//train = true;
	collider = App->collision->AddCollider({ 0, 0, 73 * 3 - 110, 54 * 3 - 110 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->genemies);
	spritesheet = 3;
	animations = 1;
	original_pos.x = x;
	original_pos.y = -200;
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

	animation = &flyi;
	w = 73 * 3;
	h = 54 * 3;

	distance.x = fabs(distance.x);
	distance.y = fabs(distance.y);
	distance1.x = fabs(distance1.x);
	distance1.y = fabs(distance1.y);

	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f)
	{
		animation = &flyi;
	}
}
