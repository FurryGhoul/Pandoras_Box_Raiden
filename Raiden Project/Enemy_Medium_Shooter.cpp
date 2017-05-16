#include "Enemy_Medium_Shooter.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"

#define PI 3.14159265

Enemy_Medium_Shooter::Enemy_Medium_Shooter(int x, int y, int path) : Enemy(x, y)
{
	hp = 17;
	points = 980;
	
	// Anmiation pushback's

	// Idle
	flyi.PushBack({ 329, 47, 73, 54 });
	flyi.PushBack({ 407, 47, 73, 54 });
	flyi.speed = 0.2f;

	// Shooting animation
	flys.PushBack({ 8, 109, 73, 54 });
	flys.PushBack({ 86, 109, 73, 54 });
	flys.PushBack({ 164, 109, 73, 54 });
	flys.PushBack({ 242, 109, 73, 54 });
	flys.speed = 0.2f;

	// Charge downwards
	flycd.PushBack({ 8, 47, 73, 54 });
	flycd.PushBack({ 86, 47, 73, 54 });
	flycd.speed = 0.2f;

	// Charge upwards
	flycu.PushBack({ 163, 47, 73, 54 });
	flycu.PushBack({ 244, 46, 73, 54 });
	flycu.speed = 0.2;

	// Hit animations
	hitflyi.PushBack({ 8, 414, 73, 54 });
	hitflyi1.PushBack({ 8, 258, 73, 54 });

	hitflys.PushBack({ 8, 414, 73, 54 });
	hitflys1.PushBack({ 8, 258, 73, 54 });

	hitflycd.PushBack({ 8, 346, 73, 54 });
	hitflycd1.PushBack({ 8, 189, 73, 54 });

	hitflycu.PushBack({ 164, 346, 73, 54 });
	hitflycu1.PushBack({ 162, 190, 73, 54 });


	movement.PushBack({ 0.0f, 3.0f }, 100);
	movement.PushBack({ 0.0f, 2.0f }, 100);
	movement.PushBack({ 0.0f, 3.0f }, 70);
	movement.PushBack({ 0.0f, 4.0f }, 120);
	movement.PushBack({ 0.0f, -5.0f }, 500);
	movement.loop = false;

	mediumshooter = true;
	collider = App->collision->AddCollider({ 0, 0, 73 * 3 - 110, 54 * 3 - 110 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	spritesheet = 3;
	animations = 1;
	original_pos.x = x;
	original_pos.y = -200;
}

void Enemy_Medium_Shooter::MoveShoot()
{

	position = original_pos + movement.GetCurrentPosition();
	position.x += left_right_mod;

	++shoot_time;

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
	// Animation

	animation = &flyi;
	w = 73 * 3;
	h = 54 * 3;

	distance.x = fabs(distance.x);
	distance.y = fabs(distance.y);	

	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 3.0f)
	{
		animation = &flyi;

		if (ishit == true)
		{
			if (hp > 9)
				animation = &hitflyi;
			else
				animation = &hitflyi1;
			
			ishit = false;
		}
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f)
	{
		animation = &flys;
		
		if (ishit == true)
		{
			if (hp > 9)
				animation = &hitflys;
			else
				animation = &hitflys1;

			ishit = false;
		}
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 4.0f)
	{
		animation = &flycd;

		if (ishit == true)
		{
			if (hp > 9)
				animation = &hitflycd;
			else
				animation = &hitflycd1;

			ishit = false;
		}
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == -5.0f)
	{
		animation = &flycu;

		if (ishit == true)
		{
			if (hp > 9)
				animation = &hitflycu;
			else
				animation = &hitflycu1;

			ishit = false;
		}
	}

	// Shooting
	distance.x *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
	distance.y *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
	
	if (shoot_time % 50 == 0 && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f && shooting == false)
	{
		shooting = true;
	}

	if (sqrtf(distance.x*distance.x + distance.y*distance.y) < 500 && shooting == true)
	{

		if (App->player->position.y < (position.y))
		{
			distance.y *= -1;
		}
		if (App->player->position.x < (position.x))
		{
			distance.x *= -1;
		}
		if (shoot_time % 5 == 0)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + 60, position.y + 30, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			App->particles->AddParticle(App->particles->enemyshot, position.x + 150, position.y + 30, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);

			shots++;
		}

		if (shots >= 5)
		{
			shooting = false;
			shots = 0;
		}
	}
}