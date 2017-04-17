#include "Enemy_Light_Shooter.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>

#define PI 3.14159265

Enemy_Light_Shooter::Enemy_Light_Shooter(int x, int y) : Enemy(x, y)
{
	flys.PushBack({ 180, 1, 22, 30 });
	flys.speed = 1.0f;
	flys.loop = false;

	flyse.PushBack({ 326, 1, 25, 30 });
	flyse.speed = 1.0f;
	flyse.loop = false;


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

	// Applying animation
	if ((se || sw) && angle < 30)
	{
		animation = &flys;
	}
	if (se && angle > 30)
	{
		animation = &flyse;
	}
	
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
