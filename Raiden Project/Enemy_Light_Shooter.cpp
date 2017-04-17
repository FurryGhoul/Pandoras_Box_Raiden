#include "Enemy_Light_Shooter.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>

#define PI 3.14159265

Enemy_Light_Shooter::Enemy_Light_Shooter(int x, int y) : Enemy(x, y)
{
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

	movement.PushBack({ -0.2f, 8.0f }, 50);
	movement.PushBack({ 0.0f, 0.0f }, 50);
	movement.PushBack({ -0.2f, -5.0f }, 600);

	collider = App->collision->AddCollider({ 0, 0, 24*3-5, 24*3+20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = -50;
	w = 24*3;
	h = 34*3;
}

void Enemy_Light_Shooter::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
	distance.y = App->player->position.y - 22 - position.y - 22 * 3;
	distance.x = App->player->position.x - position.y + 22 ;

	// Animation

	// South-East position
	if (distance.y > 0 && distance.x > 0)
	{
		se = true;
		param = (abs(distance.x) / (abs(distance.y) + 0.1));
		angle = atan(param) * 180 / PI;
	}
	else
	{
		se = false;
	}

	// South-West position
	if (distance.y > 0 && distance.x < 0)
	{
		sw = true;
		param = (abs(distance.x) / (abs(distance.y) + 0.1));
		angle = atan(param) * 180 / PI;
	}
	else
	{
		sw = false;
	}

	// North-East position
	if (distance.y < 0 && distance.x > 0)
	{
		ne = true;
		param = (abs(distance.y) / (abs(distance.x) + 0.1));
		angle = atan(param) * 180 / PI;
	}
	else
	{
		ne = false;
	}

	// North-West position
	if (distance.y < 0 && distance.x < 0)
	{
		nw = true;
		param = (abs(distance.y) / (abs(distance.x) + 0.1));
		angle = atan(param) * 180 / PI;
	}
	else
	{
		nw = false;
	}
	/*
	// Applying animation

	// South to East
	if ((se || sw) && angle < 18)
	{
		animation = &flys;
	}
	if (se && angle > 18)
	{
		animation = &flyse1;
	}
	if (se && angle > 36)
	{
		animation = &flyse2;
	}
	if (se && angle > 54)
	{
		animation = &flyse3;
	}
	if (se && angle > 72)
	{
		animation = &flyse3;
	}

	// East to North
	if ((se || nw) && angle < 18)
	{
		animation = &flys;
	}
	if (se && angle > 18)
	{
		animation = &flyse1;
	}
	if (se && angle > 36)
	{
		animation = &flyse2;
	}
	if (se && angle > 54)
	{
		animation = &flyse3;
	}
	if (se && angle > 72)
	{
		animation = &flyse3;
	}
	*/
	
	// Shooting
	if (distance.y <= 400 && shooting == false)
	{

		
		while (sqrtf(distance.x*distance.x + distance.y*distance.y) > 15) //I'm trying to convert the distance at which the player is from the enemy in a vector that represents the speed of the bullet, which shouldn't be bigger that 10
		{
			
			distance.x -= distance.x*0.1;
			distance.y -= distance.y*0.1;
		}
		
	
		App->particles->AddParticle(App->particles->enemyshot, position.x+10, position.y + 50, COLLIDER_ENEMY_SHOT,distance.x, distance.y); //In theory, the speed should be distance.x and distance.y, but at the moment it doesn't work that way
		shooting = true;
	}
}
