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
	points = 480;
	lightshooter = false;
	// Anmiation pushback's

	//Standing animation
	flys.PushBack({ 8, 47, 73, 54 });
	flyse1.PushBack({ 86, 47, 73, 53 });
	flyse2.PushBack({ 164, 47, 73, 54 });
	flyse3.PushBack({ 242, 47, 73, 53 });

	// Shooting animation
	flye.PushBack({ 8, 109, 73, 54 });
	flyne1.PushBack({ 86, 109, 73, 52 });
	flyne2.PushBack({ 164, 109, 73, 54 });
	flyne3.PushBack({ 242, 109, 73, 52 });

	if (path == 0)
	{
		movement.PushBack({ -0.2f, 8.0f }, 50);
		movement.PushBack({ 0.0f, 0.0f }, 100);
		movement.PushBack({ -0.2f, -5.0f }, 600);
	}

	if (path == 1)
	{
		movement.PushBack({ -0.2f, 8.0f }, 40);
		movement.PushBack({ 0.0f, 0.0f }, 100);
		movement.PushBack({ -0.2f, -5.0f }, 600);
	}

	collider = App->collision->AddCollider({ 0, 0, 35 * 3 - 5, 30 * 3 + 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	spriteshit = 3;
	animations = 1;
	original_pos.x = x;
	original_pos.y = -50;
}

void Enemy_Medium_Shooter::MoveShoot()
{

	position = original_pos + movement.GetCurrentPosition();


	//position = original_pos + movement1.GetCurrentPosition();

	position.x += left_right_mod;

	++shoot_time;

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
	if (sqrtf(distance.x*distance.x + distance.y*distance.y) < 500 && shooting == false)
	{
		if (shoot_time % 80 == 0 && position.y <= 760)
		{
			if (App->player->position.y - 22 < (position.y - 22 * 3))
			{
				distance.y *= -1;
			}
			if (App->player->position.x < (position.x + 22))
			{
				distance.x *= -1;
			}
			App->particles->AddParticle(App->particles->enemyshot, position.x + 10, position.y + 50, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y); //In theory, the speed should be distance.x and distance.y, but at the moment it doesn't work that way

			shooting = true;
		}
		shooting = false;
	}
}