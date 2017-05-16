#include "Enemy_Light_Shooter.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"

#define PI 3.14159265

Enemy_Light_Shooter::Enemy_Light_Shooter(int x, int y, int path) : Enemy(x, y)
{
	hp = 1;
	points = 130;
	lightshooter = true;
	// Anmiation pushback's

	//South to East
	flys.PushBack({ 1, 1, 22, 30 });
	flyse1.PushBack({ 25, 1, 25, 30 });
	flyse2.PushBack({ 53, 1, 27, 25 });
	flyse3.PushBack({ 81, 1, 31, 23 });

	// East to North
	flye.PushBack({ 114, 1, 32, 30 });
	flyne1.PushBack({ 147, 1, 31, 23 });
	flyne2.PushBack({ 182, 1, 27, 26 });
	flyne3.PushBack({ 212, 1, 25, 30 });

	//North to West
	flyn.PushBack({ 241, 1, 22, 30 });
	flynw1.PushBack({ 266, 1, 25, 30 });
	flynw2.PushBack({ 294, 1, 27, 25 });
	flynw3.PushBack({ 322, 1, 31, 23 });

	//West to South
	flyw.PushBack({ 356, 1, 32, 28 });
	flysw1.PushBack({ 392, 1, 31, 23 });
	flysw2.PushBack({ 426, 1, 27, 26 });
	flysw3.PushBack({ 458, 1, 24, 30 });

	if (path == 0)
	{
		movement.PushBack({ -0.2f, 8.0f }, 50);
		movement.PushBack({ 0.0f, 0.0f }, 100);
		movement.PushBack({ -0.2f, -5.0f }, 200);
	}
	
	if (path == 1)
	{
		movement.PushBack({ -0.2f, 8.0f }, 40);
		movement.PushBack({ 0.0f, 0.0f }, 100);
		movement.PushBack({ -0.2f, -5.0f }, 200);
	}
	if (path == 2)
	{
		movement.PushBack({ -0.2f, 8.0f }, 30);
		movement.PushBack({ 0.0f, 0.0f }, 100);
		movement.PushBack({ -0.2f, -5.0f }, 200);
	}

	collider = App->collision->AddCollider({ 0, 0, 24*3-5, 24*3+20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	spritesheet = 0;
	animations = 1;
	original_pos.x = x;
	original_pos.y = -50;
}

void Enemy_Light_Shooter::MoveShoot()
{
	
	position = original_pos + movement.GetCurrentPosition();
	
	
	//position = original_pos + movement1.GetCurrentPosition();
	
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

	// Setting angle
	param = (fabs(distance.y) / (fabs(distance.x) + 0.1));
	angle = atan(param) * 180 / PI;

	// South-East position
	if (distance.y > 0 && distance.x > 0)
	{
		se = true;
	}
	else
	{
		se = false;
	}

	// South-West position
	if (distance.y > 0 && distance.x < 0)
	{
		sw = true;
	}
	else
	{
		sw = false;
	}

	// North-East position
	if (distance.y < 0 && distance.x > 0)
	{
		ne = true;
	}
	else
	{
		ne = false;
	}

	// North-West position
	if (distance.y < 0 && distance.x < 0)
	{
		nw = true;
	}
	else
	{
		nw = false;
	}

	// Applying animation

	// South to East
	if (se && angle > 72 && angle < 90)
	{
		animation = &flys;
		w = 22 * 3;
		h = 30 * 3;
	}
	if (se && angle > 54 && angle < 72)
	{
		animation = &flyse1;
		w = 25 * 3;
		h = 30 * 3;
	}
	if (se && angle > 36 && angle < 54)
	{
		animation = &flyse2;
		w = 27 * 3;
		h = 25 * 3;
	}
	if (se && angle > 18 && angle < 36)
	{
		animation = &flyse3;
		w = 31 * 3;
		h = 23 * 3;
	}
	if (se && angle > 0 && angle < 18)
	{
		animation = &flye;
		w = 32 * 3;
		h = 30 * 3;
	}

	// East to North
	if (ne && angle > 0 && angle < 18)
	{
		animation = &flye;
		w = 32 * 3;
		h = 30 * 3;
	}
	if (ne && angle > 18 && angle < 36)
	{
		animation = &flyne1;
		w = 31 * 3;
		h = 23 * 3;
	}
	if (ne && angle > 36 && angle < 54)
	{
		animation = &flyne2;
		w = 27 * 3;
		h = 26 * 3;
	}
	if (ne && angle > 54 && angle < 72)
	{
		animation = &flyne3;
		w = 25 * 3;
		h = 30 * 3;
	}
	if (ne && angle > 72 && angle < 90)
	{
		animation = &flyn;
		w = 22 * 3;
		h = 30 * 3;
	}

	// North to West
	if (nw && angle > 72 && angle < 90)
	{
		animation = &flyn;
		w = 22 * 3;
		h = 30 * 3;
	}
	if (nw && angle > 54 && angle < 72)
	{
		animation = &flynw1;
		w = 25 * 3;
		h = 30 * 3;
	}
	if (nw && angle > 36 && angle < 54)
	{
		animation = &flynw2;
		w = 27 * 3;
		h = 25 * 3;
	}
	if (nw && angle > 18 && angle < 36)
	{
		animation = &flynw3;
		w = 31 * 3;
		h = 23 * 3;
	}
	if (nw && angle > 0 && angle < 18)
	{
		animation = &flyw;
		w = 32 * 3;
		h = 28 * 3;
	}

	// West to South
	if (sw && angle > 0 && angle < 18)
	{
		animation = &flyw;
		w = 32 * 3;
		h = 28 * 3;
	}
	if (sw && angle > 18 && angle < 36)
	{
		animation = &flysw1;
		w = 31 * 3;
		h = 23 * 3;
	}
	if (sw && angle > 36 && angle < 54)
	{
		animation = &flysw2;
		w = 27 * 3;
		h = 26 * 3;
	}
	if (sw && angle > 54 && angle < 72)
	{
		animation = &flysw3;
		w = 24 * 3;
		h = 30 * 3;
	}
	if (sw && angle > 72 && angle < 90)
	{
		animation = &flys;
		w = 22 * 3;
		h = 30 * 3;
	}

	distance.x = fabs(distance.x);
	distance.y = fabs(distance.y);

	// Shooting
	distance.x *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
	distance.y *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
	if (sqrtf(distance.x*distance.x + distance.y*distance.y) < 500 && shooting == false )
	{
		if (shoot_time % 80 == 0 && position.y <= 760)
		{
			if (App->player->position.y < (position.y))
			{
				distance.y *= -1;
			}
			if (App->player->position.x < (position.x))
			{
				distance.x *= -1;
			}
			App->particles->AddParticle(App->particles->enemyshot, position.x + 10, position.y + 50, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y); //In theory, the speed should be distance.x and distance.y, but at the moment it doesn't work that way

			shooting = true;
		}
		shooting = false;
	}
}
