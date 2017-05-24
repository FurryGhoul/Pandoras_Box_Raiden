#include "Enemy_Light_Shooter_Kamikaze.h"
#include "Enemy_Light_Shooter.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"
#define PI 3.14159265


Light_Shooter_Kamikaze::Light_Shooter_Kamikaze(int x, int y, int path, bool pcome_right) : Enemy(x, y)
{
	hp = 1;
	points = 130;
	light_kamikaze = true;
	// Anmiation pushback's

	//South to East
	flys.PushBack({ 16, 58, 27, 20 });
	flyse1.PushBack({ 291, 23, 26, 21 });
	flyse2.PushBack({ 250, 19, 26, 25 });
	flyse3.PushBack({ 211, 18, 22, 25 });

	// East to North
	flye.PushBack({ 178, 20, 20, 23 });
	flyne1.PushBack({ 136, 19, 24, 24 });
	flyne2.PushBack({ 100, 18, 26, 24 });
	flyne3.PushBack({ 58, 18, 27, 22 });

	//North to West
	flyn.PushBack({ 16, 18, 27, 20}); 
	flynw1.PushBack({ 205, 56, 27, 23 });
	flynw2.PushBack({ 243, 53, 27, 25 });
	flynw3.PushBack({ 291, 54, 24, 24 });

	//West to South
	flyw.PushBack({ 174, 55, 20, 23 });
	flysw1.PushBack({ 137, 54, 22, 25 });
	flysw2.PushBack({ 96, 53, 25, 25 });
	flysw3.PushBack({ 56, 56, 26, 20 });
	collider = App->collision->AddCollider({ 0, 0, 25 * 3 - 5, 25 * 3 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	spritesheet = 8;
	animations = 1;


	come_right = pcome_right;
	position.x =original_pos.x = x;

	position.y= original_pos.y = 100;
	if (path == 0)
	{
	position.y = original_pos.y = 100;
	}
	if (path == 1)
	{
		position.y = original_pos.y = 150;
	}
	if (path == 2)
	{
		position.y = original_pos.y = 200;
	}
}


void Light_Shooter_Kamikaze::MoveShoot()
{
	if (!time_got)
	{
		time = SDL_GetTicks();
		time_got = true;
	}

if (!close)
{ 
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
		w = 27 * 3;
		h = 20 * 3;
	}
	if (se && angle > 54 && angle < 72)
	{
		animation = &flyse1;
		w = 26 * 3;
		h = 21 * 3;
	}
	if (se && angle > 36 && angle < 54)
	{
		animation = &flyse2;
		w = 26 * 3;
		h = 25 * 3;
	}
	if (se && angle > 18 && angle < 36)
	{
		animation = &flyse3;
		w = 22 * 3;
		h = 25 * 3;
	}
	if (se && angle > 0 && angle < 18)
	{
		animation = &flye;
		w = 20 * 3;
		h = 23 * 3;
	}

	// East to North
	if (ne && angle > 0 && angle < 18)
	{
		animation = &flye;
		w = 20 * 3;
		h = 23 * 3;
	}
	if (ne && angle > 18 && angle < 36)
	{
		animation = &flyne1;
		w = 24 * 3;
		h = 24 * 3;
	}
	if (ne && angle > 36 && angle < 54)
	{
		animation = &flyne2;
		w = 26 * 3;
		h = 24 * 3;
	}
	if (ne && angle > 54 && angle < 72)
	{
		animation = &flyne3;
		w = 27 * 3;
		h = 22 * 3;
	}
	if (ne && angle > 72 && angle < 90)
	{
		animation = &flyn;
		w = 27 * 3;
		h = 20 * 3;
	}

	// North to West
	if (nw && angle > 72 && angle < 90)
	{
		animation = &flyn;
		w = 27 * 3;
		h = 20 * 3;
	}
	if (nw && angle > 54 && angle < 72)
	{
		animation = &flynw1;
	
		w = 27 * 3;
		h = 23 * 3;
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
	
		w = 24 * 3;
		h = 24 * 3;
	}
	if (nw && angle > 0 && angle < 18)
	{
		animation = &flyw;
		w = 20 * 3;
		h = 23 * 3;
	}

	// West to South
	if (sw && angle > 0 && angle < 18)
	{
		animation = &flyw;
		w = 20 * 3;
		h = 23 * 3;
	}
	if (sw && angle > 18 && angle < 36)
	{
		animation = &flysw1;
		w = 22 * 3;
		h = 25 * 3;
	}
	if (sw && angle > 36 && angle < 54)
	{
		animation = &flysw2;
		w = 25 * 3;
		h = 25 * 3;
	}
	if (sw && angle > 54 && angle < 72)
	{
		animation = &flysw3;
		w = 26 * 3;
		h = 20 * 3;
	}
	if (sw && angle > 72 && angle < 90)
	{
		animation = &flys;
		w = 27 * 3;
		h = 20 * 3;
	}
}
   //Movement
	if (SDL_GetTicks() - time < 1600)
	{
		if (come_right)
		{ 
		position.x += 3;
		animation = &flye;
		}
		else
		{
		position.x -= 3;
		animation = &flyw;
		}
		
		w = 20 * 3;
		h = 23 * 3;
	
	}
	else
	{
		
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

		
		
		if(sqrtf(distance.y* distance.y + distance.x*distance.x)> 150 && !close)
		{ 
		    vector.x = distance.x * (5 / sqrtf(distance.x*distance.x + distance.y*distance.y));
	        vector.y = distance.y * (5 / sqrtf(distance.x*distance.x + distance.y*distance.y));
		
		}
		else
		{
			close = true;
			
		}
			


			position.x += vector.x;
			position.y += vector.y;
			
			
	   //Shoot
			if (!close)
			{ 
			distance.x *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
			distance.y *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
			if (sqrtf(distance.x*distance.x + distance.y*distance.y) < 500 && shooting == false)
			{
				if (shoot_time % 40 == 0 && position.y <= 760)
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
	}
	++shoot_time;
	
	}

	

