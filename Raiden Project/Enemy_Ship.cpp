#include "Enemy_Ship.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"

#define PI 3.14159265

Enemy_Ship::Enemy_Ship(int x, int y, int path) : Enemy(x, y)
{
	hp = 13;
	points = 200;

	// Anmiation pushback's

	// Down
	down.PushBack({ 4, 1, 30, 48 });

	// Door
	semiopen.PushBack({ 40, 5, 17, 33 });
	open.PushBack({ 62, 5, 17, 33 });
	nodoor.PushBack({ 110, 5, 17, 10 });

	// Water
	water1.PushBack({ 85, 31, 18, 15 });
	water2.PushBack({ 109, 32, 20, 16 });
	water3.PushBack({ 131, 32, 16, 16 });

	// Movement
	movement.PushBack({ 0.0f, 3.0f }, 100);
	movement.loop = false;

	collider = App->collision->AddCollider({ 0, 0, 73 * 3 - 110, 54 * 3 - 110 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->enemies);

	spritesheet = 7;
	animations = 2;
	original_pos.x = x;
	original_pos.y = -200;	
}

void Enemy_Ship::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
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
	animation = &down;
	w = 30 * 3;
	h = 48 * 3;
	

	distance.x = fabs(distance.x);
	distance.y = fabs(distance.y);

	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 3.0f)
	{
		animation = &down;
	}

	// Shooting animation
	animation1 = &nodoor;
	w1 = 17 * 3;
	h1 = 33 * 3;
	position1.x = position.x + 15;
	position1.y = position.y + 21;

	if (shooting == true)
	{
		if (shotphase <= 7)
		{
			animation1 = &semiopen;
			
			shotphase++;
		}
		else if (shotphase <= 14)
		{
			animation1 = &open;
			


			shotphase++;
		}
		else if (shotphase > 14)
		{
			animation1 = &semiopen;			

			shotphase++;

			if (shotphase == 21)
			{
				shotphase = 0;
				shooting = false;
			}
		}
	}

	if (shoot_time % 100 == 0)
	{
		shooting = true;
	}
}