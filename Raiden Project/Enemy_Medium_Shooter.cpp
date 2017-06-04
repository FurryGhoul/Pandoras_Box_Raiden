#include "Enemy_Medium_Shooter.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"
#include "ModuleShadows.h"

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

	if (path == 0) // If the ship spawns at the left of the screen, it wil charge to the right
	{
		movement.PushBack({ 0.0f, 2.1f }, 50);
		movement.PushBack({ 0.0f, 2.0f }, 30);
		movement.PushBack({ 0.0f, 2.1f }, 170);
		movement.PushBack({ 0.0f, 2.0f }, 30);
		movement.PushBack({ 0.0f, 2.1f }, 70);
		movement.PushBack({ 3.0f, 4.0f }, 100);
		movement.PushBack({ 0.0f, -5.0f }, 500);
		movement.loop = false;
	}
	if (path == 1) // If the ship spawns at the rigth of the screen, it wil charge to the left
	{
		movement.PushBack({ 0.0f, 2.1f }, 50);
		movement.PushBack({ 0.0f, 2.0f }, 30);
		movement.PushBack({ 0.0f, 2.1f }, 170);
		movement.PushBack({ 0.0f, 2.0f }, 30);
		movement.PushBack({ 0.0f, 2.1f }, 70);
		movement.PushBack({ -3.0f, 4.0f }, 100);
		movement.PushBack({ 0.0f, -5.0f }, 500);
		movement.loop = false;
	}
	if (path == 2) // If the ship spawns at the middle of the screen, it wil charge vertically
	{
		movement.PushBack({ 0.0f, 2.1f }, 50);
		movement.PushBack({ 0.0f, 2.0f }, 30);
		movement.PushBack({ 0.0f, 2.1f }, 170);
		movement.PushBack({ 0.0f, 2.0f }, 30);
		movement.PushBack({ 0.0f, 2.1f }, 70);
		movement.PushBack({ 0.0f, 4.0f }, 100);
		movement.PushBack({ 0.0f, -5.0f }, 500);
		movement.loop = false;
	}

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

	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 2.1f)
	{
		animation = &flyi;
		if (shadowregulator % 2 == 0)
		{
			if (shadowdirection == 0)
				App->shadows->AddShadow(App->shadows->MediumFront, position.x, position.y, 50 * 3, 40 * 3);
		}
		shadowregulator++;

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
		if (shadowregulator % 2 == 0)
		{
			if (shadowdirection == 0)
				App->shadows->AddShadow(App->shadows->MediumFront, position.x, position.y, 50 * 3, 40 * 3);
		}
		shadowregulator++;
		if (ishit == true)
		{
			if (hp > 9)
				animation = &hitflys;
			else
				animation = &hitflys1;

			ishit = false;
		}
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 3.0f && movement.steps[movement.GetCurrentStep()].speed.y == 4.0f)
	{
		animation = &flycd;
		if (shadowregulator % 2 == 0)
		{
			if (shadowdirection == 0)
				App->shadows->AddShadow(App->shadows->MediumFront, position.x, position.y, 50 * 3, 40 * 3);
		}
		shadowregulator++;
		if (ishit == true)
		{
			if (hp > 9)
				animation = &hitflycd;
			else
				animation = &hitflycd1;

			ishit = false;
		}
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == -3.0f && movement.steps[movement.GetCurrentStep()].speed.y == 4.0f)
	{
		animation = &flycd;
		if (shadowregulator % 2 == 0)
		{
			if (shadowdirection == 0)
				App->shadows->AddShadow(App->shadows->MediumFront, position.x, position.y, 50 * 3, 40 * 3);
		}
		shadowregulator++;
		if (ishit == true)
		{
			if (hp > 9)
				animation = &hitflycd;
			else
				animation = &hitflycd1;

			ishit = false;
		}
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 4.0f)
	{
		animation = &flycd;
		if (shadowregulator % 2 == 0)
		{
			if (shadowdirection == 0)
				App->shadows->AddShadow(App->shadows->MediumFront, position.x, position.y, 50 * 3, 40 * 3);
		}
		shadowregulator++;
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
		if (shadowregulator % 2 == 0)
		{
			if (shadowdirection == 0)
				App->shadows->AddShadow(App->shadows->MediumBack, position.x, position.y, 50 * 3, 40 * 3);
		}
		shadowregulator++;
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
	distance1.x *= (10 / sqrtf(distance1.x*distance1.x + distance1.y*distance1.y));
	distance1.y *= (10 / sqrtf(distance1.x*distance1.x + distance1.y*distance1.y));
	
	if (shoot_time % 10 == 0 && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f && shooting == false)
	{
		shooting = true;
	}

	if (sqrtf(distance.x*distance.x + distance.y*distance.y) < 500 && shooting == true)
	{

		if (App->player->position.y < (position.y))
		{
			distance.y *= -1;
			distance1.y *= -1;
		}
		if (App->player->position.x < (position.x))
		{
			distance.x *= -1;
			distance1.x *= -1;
		}
		if (shoot_time % 5 == 0)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + 150, position.y + 110, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			App->particles->AddParticle(App->particles->enemyshot, position.x + 50, position.y + 110, COLLIDER_ENEMY_SHOT, 0, distance1.x, distance1.y);

			shots++;
		}

		if (shots >= 5)
		{
			shooting = false;
			shots = 0;
		}
	}

	// Burst
	if (shoot_time % 185 == 0 && movement.steps[movement.GetCurrentStep()].speed.y == -5.0f && singleburst == false)
	{
		burst = true;
		singleburst = true;
	}
	if (shoot_time % 215 == 0 && movement.steps[movement.GetCurrentStep()].speed.y == -5.0f && singleburst2 == false)
	{
		burst2 = true;
		singleburst2 = true;
	}

	if (burst == true)
	{
		App->particles->AddParticle(App->particles->enemyshot, position.x + 105, position.y + 80, COLLIDER_ENEMY_SHOT, 0, 0.5f, 7.0f);
		App->particles->AddParticle(App->particles->enemyshot, position.x + 105, position.y + 80, COLLIDER_ENEMY_SHOT, 0, -0.5f, 7.0f, false, true);
		App->particles->AddParticle(App->particles->enemyshot, position.x + 105, position.y + 65, COLLIDER_ENEMY_SHOT, 0, 1.0f, 7.0f, false, true);
		App->particles->AddParticle(App->particles->enemyshot, position.x + 105, position.y + 65, COLLIDER_ENEMY_SHOT, 0, -1.0f, 7.0f, false, true);
		App->particles->AddParticle(App->particles->enemyshot, position.x + 105, position.y + 50, COLLIDER_ENEMY_SHOT, 0, 2.0f, 7.0f, false, true);
		App->particles->AddParticle(App->particles->enemyshot, position.x + 105, position.y + 50, COLLIDER_ENEMY_SHOT, 0, -2.0f, 7.0f, false, true);
		App->particles->AddParticle(App->particles->enemyshot, position.x + 105, position.y + 30, COLLIDER_ENEMY_SHOT, 0, 3.0f, 7.0f, false, true);
		App->particles->AddParticle(App->particles->enemyshot, position.x + 105, position.y + 30, COLLIDER_ENEMY_SHOT, 0, -3.0f, 7.0f, false, true);

		burst = false;
	}
	if (burst2 == true)
	{
		App->particles->AddParticle(App->particles->enemyshot, position.x + 105, position.y + 80, COLLIDER_ENEMY_SHOT, 0, 1.0f, 7.0f);
		App->particles->AddParticle(App->particles->enemyshot, position.x + 105, position.y + 80, COLLIDER_ENEMY_SHOT, 0, -1.0f, 7.0f, false, true);
		App->particles->AddParticle(App->particles->enemyshot, position.x + 105, position.y + 50, COLLIDER_ENEMY_SHOT, 0, 2.0f, 7.0f, false, true);
		App->particles->AddParticle(App->particles->enemyshot, position.x + 105, position.y + 50, COLLIDER_ENEMY_SHOT, 0, -2.0f, 7.0f, false, true);
		
		burst2 = false;
	}
}