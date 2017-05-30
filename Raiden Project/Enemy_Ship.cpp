#include "Enemy_Ship.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleGroundEnemies.h"

#define PI 3.14159265

Enemy_Ship::Enemy_Ship(int x, int y, int path) : Enemy(x, y)
{
	hp = 13;
	points = 200;
	ship = true;

	// Anmiation pushback's

	// Down
	down.PushBack({ 4, 1, 30, 48 });

	// Animation hitspark

	hitdown.PushBack({ 4, 53, 30, 48 });
	hitdown1.PushBack({ 40, 53, 30, 48 });
	
	// Door
	semiopen.PushBack({ 40, 5, 17, 33 });
	open.PushBack({ 62, 5, 17, 33 });
	nodoor.PushBack({ 110, 5, 17, 10 });

	hitsemiopen.PushBack({ 75, 48, 17, 33 });
	hitopen.PushBack({ 97, 48, 17, 33 });

	hitsemiopen1.PushBack({ 75, 82, 17, 33 });
	hitopen1.PushBack({ 97, 82, 17, 33 });

	// Water
	waterdown1.PushBack({ 85, 31, 18, 15 });
	waterdown2.PushBack({ 109, 32, 20, 16 });
	waterdown3.PushBack({ 131, 32, 16, 16 });
	
	// Movement
	movement.PushBack({ 0.0f, 1.0f }, 1300);
	movement.loop = false;

	collider = App->collision->AddCollider({ 0, 0, 30 * 3 , 48 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->genemies);

	spritesheet = 7;
	animations = 3;
	original_pos.x = x;
	original_pos.y = -200;
}

void Enemy_Ship::MoveShoot()
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

	// Animation of the ship and water
	animation = &down;
	w = 30 * 3;
	h = 48 * 3;
	w2 = 20 * 3;
	h2 = 16 * 3;	

	distance.x = fabs(distance.x);
	distance.y = fabs(distance.y);
	
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f)
	{
		animation = &down;

		if (ishit == true)
		{
			if (hp < 7)
				animation = &hitdown;
			else
				animation = &hitdown1;
			
			ishit = false;
		}

		if (water == 0)
		{
			animation2 = &waterdown1;
			position2.x = position.x + 12;
			position2.y = position.y - 45;

			if (waterrepeat == 10)
			{
				water++;
				waterrepeat = 0;
			}
			else
				waterrepeat++;
		}
		else if (water == 1)
		{
			animation2 = &waterdown2;
			position2.x = position.x + 12;
			position2.y = position.y - 36;

			if (waterrepeat == 10)
			{
				water++;
				waterrepeat = 0;
			}
			else
				waterrepeat++;
		}
		else if (water == 2)
		{
			animation2 = &waterdown3;
			position2.x = position.x + 11;
			position2.y = position.y - 39;

			if (waterrepeat == 10)
			{
				water = 0;
				waterrepeat = 0;
			}
			else
				waterrepeat++;
		}
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

			if (ishit == true)
			{
				if (hp < 7)
					animation = &hitsemiopen;
				else
					animation = &hitsemiopen1;

				ishit = false;
			}
			
			shotphase++;
		}
		else if (shotphase <= 14)
		{
			animation1 = &open;

			if (ishit == true)
			{
				if (hp < 7)
					animation = &hitopen;
				else
					animation = &hitopen1;

				ishit = false;
			}
			
			shotphase++;
		}
		else if (shotphase > 14)
		{
			animation1 = &semiopen;	

			if (ishit == true)
			{
				if (hp < 7)
					animation = &hitsemiopen;
				else
					animation = &hitsemiopen1;

				ishit = false;
			}

			shotphase++;

			if (shotphase == 21)
			{
				shotphase = 0;
				shooting = false;
			}
		}
		if (shotphase == 15) //Only in this phase the ship shoots
		{
			shoot = true;
		}
	}

	if (shoot_time % 120 == 0 && sqrtf(distance.x*distance.x + distance.y*distance.y) < 760)
	{
		shooting = true;
	}


	distance.x = fabs(distance.x);
	distance.y = fabs(distance.y);

	// Shooting
	distance.x *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
	distance.y *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
	if (shoot == true)
	{
		if (App->player->position.y < (position.y))
		{
			distance.y *= -1;
		}
		if (App->player->position.x < (position.x))
		{
			distance.x *= -1;
		}
		App->particles->AddParticle(App->particles->enemyshot, position.x + 20, position.y + 80, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);

		shoot = false;
	}
}