#include "Enemy_Bonus_Ship.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "Enemy.h"
#include <Math.h>
#include "ModuleEnemies.h"
#include "ModuleShadows.h"


Enemy_Bonus_Ship::Enemy_Bonus_Ship(int x, int y, int path) : Enemy (x, y)
{
	hp = 17;
	points = 480;

	flydown.PushBack({ 5, 20, 58, 57 });

	dmgdown.PushBack({ 5, 20, 58, 57 });
	dmgdown.PushBack({ 5, 20, 58, 57 });
	dmgdown.PushBack({ 5, 135, 58, 57 });
	dmgdown.PushBack({ 5, 135, 58, 57 });
	dmgdown.loop = true;
	dmgdown.speed = 0.5f;

	stop.PushBack({ 64, 20, 59, 54 });
	stop.PushBack({ 241, 20, 59, 54 });
	stop.speed = 0.5f;
	stop.loop = false;

	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });
	flysides.PushBack({ 123, 20, 59, 54 });
	flysides.PushBack({ 182, 20, 59, 54 });

	flysides.speed = 0.5f;
	flysides.loop = true;

	dmgsides.PushBack({ 123, 135, 59, 54 });
	dmgsides.PushBack({ 182, 135, 59, 54 });
	dmgsides.PushBack({ 123, 20, 59, 54 });
	dmgsides.PushBack({ 182, 20, 59, 54 });
	dmgsides.PushBack({ 123, 135, 59, 54 });
	dmgsides.PushBack({ 182, 135, 59, 54 });
	dmgsides.PushBack({ 123, 20, 59, 54 });
	dmgsides.PushBack({ 182, 20, 59, 54 });
	dmgsides.PushBack({ 123, 135, 59, 54 });
	dmgsides.PushBack({ 182, 135, 59, 54 });
	dmgsides.PushBack({ 123, 20, 59, 54 });
	dmgsides.PushBack({ 182, 20, 59, 54 });
	dmgsides.PushBack({ 123, 135, 59, 54 });
	dmgsides.PushBack({ 182, 135, 59, 54 });
	dmgsides.PushBack({ 123, 20, 59, 54 });
	dmgsides.PushBack({ 182, 20, 59, 54 });
	dmgsides.PushBack({ 123, 135, 59, 54 });
	dmgsides.PushBack({ 182, 135, 59, 54 });
	dmgsides.PushBack({ 123, 20, 59, 54 });
	dmgsides.PushBack({ 182, 20, 59, 54 });
	dmgsides.PushBack({ 123, 135, 59, 54 });
	dmgsides.PushBack({ 182, 135, 59, 54 });
	dmgsides.PushBack({ 123, 20, 59, 54 });
	dmgsides.PushBack({ 182, 20, 59, 54 });
	dmgsides.PushBack({ 123, 135, 59, 54 });
	dmgsides.PushBack({ 182, 135, 59, 54 });
	dmgsides.PushBack({ 123, 20, 59, 54 });
	dmgsides.PushBack({ 182, 20, 59, 54 });
	dmgsides.PushBack({ 123, 135, 59, 54 });
	dmgsides.PushBack({ 182, 135, 59, 54 });
	dmgsides.PushBack({ 123, 20, 59, 54 });
	dmgsides.PushBack({ 182, 20, 59, 54 });
	dmgsides.PushBack({ 123, 135, 59, 54 });
	dmgsides.PushBack({ 182, 135, 59, 54 });
	dmgsides.PushBack({ 123, 20, 59, 54 });
	dmgsides.PushBack({ 182, 20, 59, 54 });
	dmgsides.PushBack({ 123, 135, 59, 54 });
	dmgsides.PushBack({ 182, 135, 59, 54 });
	dmgsides.PushBack({ 123, 20, 59, 54 });
	dmgsides.PushBack({ 182, 20, 59, 54 });
	dmgsides.PushBack({ 123, 135, 59, 54 });
	dmgsides.PushBack({ 182, 135, 59, 54 });
	dmgsides.PushBack({ 123, 20, 59, 54 });
	dmgsides.PushBack({ 182, 20, 59, 54 });
	dmgsides.PushBack({ 123, 135, 59, 54 });
	dmgsides.PushBack({ 182, 135, 59, 54 });
	dmgsides.PushBack({ 123, 20, 59, 54 });
	dmgsides.PushBack({ 182, 20, 59, 54 });

	dmgsides.speed = 0.5f;
	dmgsides.loop = true;

	none.PushBack({ 500, 500, 32, 14 });

	propeller.PushBack({ 143, 83, 32, 14 });
	propeller.PushBack({ 194, 83, 32, 14 });
	propeller.speed = 0.5f;
	propeller.loop = true;

	charge.PushBack({ 477, 20, 59, 54 });
	charge.PushBack({ 536, 20, 59, 54 });
	charge.PushBack({ 477, 20, 59, 54 });
	charge.PushBack({ 536, 20, 59, 54 });
	charge.PushBack({ 595, 20, 59, 54 });
	charge.PushBack({ 654, 20, 59, 54 });
	charge.PushBack({ 595, 20, 59, 54 });
	charge.PushBack({ 654, 20, 59, 54 });
	charge.PushBack({ 713, 20, 59, 54 });
	charge.PushBack({ 772, 20, 59, 54 });
	charge.PushBack({ 713, 20, 59, 54 });
	charge.PushBack({ 772, 20, 59, 54 });
	charge.PushBack({ 595, 20, 59, 54 });
	charge.PushBack({ 654, 20, 59, 54 });
	charge.PushBack({ 595, 20, 59, 54 });
	charge.PushBack({ 654, 20, 59, 54 });
	charge.PushBack({ 477, 20, 59, 54 });
	charge.PushBack({ 536, 20, 59, 54 });
	charge.PushBack({ 477, 20, 59, 54 });
	charge.PushBack({ 536, 20, 59, 54 });
	charge.speed = 0.5f;
	charge.loop = false;

	dmgcharge.PushBack({ 477, 135, 59, 54 });
	dmgcharge.PushBack({ 536, 135, 59, 54 });
	dmgcharge.PushBack({ 477, 20, 59, 54 });
	dmgcharge.PushBack({ 536, 20, 59, 54 });
	dmgcharge.PushBack({ 595, 135, 59, 54 });
	dmgcharge.PushBack({ 654, 135, 59, 54 });
	dmgcharge.PushBack({ 595, 20, 59, 54 });
	dmgcharge.PushBack({ 654, 20, 59, 54 });
	dmgcharge.PushBack({ 713, 135, 59, 54 });
	dmgcharge.PushBack({ 772, 135, 59, 54 });
	dmgcharge.PushBack({ 713, 20, 59, 54 });
	dmgcharge.PushBack({ 772, 20, 59, 54 });
	dmgcharge.PushBack({ 595, 135, 59, 54 });
	dmgcharge.PushBack({ 654, 135, 59, 54 });
	dmgcharge.PushBack({ 595, 20, 59, 54 });
	dmgcharge.PushBack({ 654, 20, 59, 54 });
	dmgcharge.PushBack({ 477, 135, 59, 54 });
	dmgcharge.PushBack({ 536, 135, 59, 54 });
	dmgcharge.PushBack({ 477, 20, 59, 54 });
	dmgcharge.PushBack({ 536, 20, 59, 54 });
	dmgcharge.speed = 0.5f;
	dmgcharge.loop = false;

	movingsidetoside = true;
	movement.PushBack({ 0.0f, 0.5f }, 800);
	movement.PushBack({ 0.0f, 0.0f }, 300);
	movement.PushBack({ -0.4f, 0.2f }, 300);
	movement.PushBack({ 0.4f, -0.2f }, 700);
	movement.PushBack({ -0.4f, 0.2f }, 700);
	movement.PushBack({ 0.4f, -0.2f }, 700);
	movement.PushBack({ 0.0f, 1.5f }, 600);
	
	hitsides.PushBack({ 123, 193, 59, 54 });
	hitsides.PushBack({ 123, 193, 59, 54 });
	hitsides.loop = false;
	hitsides.speed = 0.5f;

	hitdown.PushBack({ 5, 193, 59, 54 });
	hitdown.PushBack({ 5, 193, 59, 54 });
	hitdown.loop = false;
	hitdown.speed = 0.5f;

	bonusplane = true;// Bollean to detect if the enemy is a bonus plane and adapt the hitbox

	collider = App->collision->AddCollider({ 0, 0, 60, 120 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	spritesheet = 1;
	animations = 2;
	original_pos.x = x;
	original_pos.y = - 200;
	original_pos1.x = original_pos.x + 50;
	original_pos1.y = original_pos.y - 27;
	original_pos2.x = x;
	original_pos2.y = -200;
	original_pos3.x = x;
	original_pos3.y = -200;
}

void Enemy_Bonus_Ship::MoveShoot()
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

	position = original_pos + movement.GetCurrentPosition();
	position1 = original_pos1 + movement.GetCurrentPosition();
	position2 = original_pos2 + movement.GetCurrentPosition();
	position3 = original_pos3 + movement.GetCurrentPosition();
	
	position.x += left_right_mod;
	position1.x += left_right_mod;
	position2.x += left_right_mod;
	position3.x += left_right_mod;

	w = 58 * 3;
	h = 57 * 3;
	w1 = 32 * 3;
	h1 = 14 * 3;
	w2 = 58 * 3;
	h2 = 57 * 3;
	w3 = 58 * 3;
	h3 = 57 * 3;

	++shoot_time;

	if (position.x < 410 || position.x > 410)
	{
		if (hp >= 10)
		{
			if (change == false)
			{
				animation = &flysides;
				animation1 = &none;
				charge.Reset();
				if (flysides.Finished())
				{
					change = true;
				}
				if (ishit == true)
				{
					animation = &hitsides;
					hitsides.Reset();
					ishit = false;
				}
			}
			if (change == true)
			{
				animation = &charge;
				animation1 = &none;
				flysides.Reset();
				side = true;
				if (charge.Finished())
				{
					change = false;
				}
				if (ishit == true)
				{
					animation = &hitsides;
					hitsides.Reset();
					ishit = false;
				}
			}
		}
		if (hp < 10)
		{
			if (change == false)
			{
				animation = &dmgsides;
				animation1 = &none;
				dmgcharge.Reset();
				if (dmgsides.Finished())
				{
					change = true;
				}
				if (ishit == true)
				{
					animation = &hitsides;
					hitsides.Reset();
					ishit = false;
				}
			}
			if (change == true)
			{
				animation = &dmgcharge;
				animation1 = &none;
				dmgsides.Reset();
				side = true;
				if (dmgcharge.Finished())
				{
					change = false;
				}
				if (ishit == true)
				{
					animation = &hitsides;
					hitsides.Reset();
					ishit = false;
				}
			}
		}
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f && side == false)
	{
		if (hp >= 10)
		{
			animation = &stop;
			animation1 = &none;
			if (ishit2 == true)
			{
				animation = &hitsides;
				hitsides.Reset();
				ishit2 = false;
			}
		}
		if (hp < 10)
		{
			animation = &dmgsides;
			animation1 = &none;
			if (ishit2 == true)
			{
				animation = &hitsides;
				hitsides.Reset();
				ishit2 = false;
			}
		}
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.5f)
	{
		if (hp >= 10)
		{
			animation = &flydown;
			animation1 = &propeller;
			if (ishit2 == true)
			{
				animation = &hitdown;
				hitdown.Reset();
				ishit2 = false;
			}
		}
		if (hp < 10)
		{
			animation = &dmgdown;
			animation1 = &propeller;
			if (ishit2 == true)
			{
				animation = &hitdown;
				hitdown.Reset();
				ishit2 = false;
			}
		}
	}
	
	if (shadowregulator % 2 == 0)
	{
		if (shadowdirection == 0)
			App->shadows->AddShadow(App->shadows->Bonusship, position.x, position.y, 50 * 3, 35 * 3);
	}
	shadowregulator++;

	if (shooting == false && movingsidetoside)
	{
		distance.x *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
		distance.y *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));

		if (shoot_time % 200 == 0 && position.y <= 760)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + 78, position.y + 60, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			App->particles->AddParticle(App->particles->enemyshot, position.x + 78, position.y + 60, COLLIDER_ENEMY_SHOT, 0, distance.x - 4, distance.y, 0, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + 78, position.y + 60, COLLIDER_ENEMY_SHOT, 0, distance.x + 4, distance.y, 0, true);

			shooting = true;
		}
		shooting = false;
	}
		
	
}


