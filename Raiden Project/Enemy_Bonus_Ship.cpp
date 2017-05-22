#include "Enemy_Bonus_Ship.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "Enemy.h"
#include <Math.h>
#include "ModuleEnemies.h"



Enemy_Bonus_Ship::Enemy_Bonus_Ship(int x, int y, int path) : Enemy (x, y)
{
	hp = 17;
	points = 480;

	flydown.PushBack({ 6, 23, 59, 54 });

	stop.PushBack({ 67, 23, 59, 54 });
	stop.PushBack({ 262, 23, 59, 54 });
	stop.speed = 1.0f;
	stop.loop = false;

	flysides.PushBack({ 131, 23, 59, 54 });
	flysides.PushBack({ 197, 23, 59, 54 });
	flysides.speed = 0.5f;
	flysides.loop = true;

	none.PushBack({ 500, 500, 32, 14 });

	propeller.PushBack({ 143, 83, 32, 14 });
	propeller.PushBack({ 194, 83, 32, 14 });
	propeller.speed = 0.5f;
	propeller.loop = true;

	charge.PushBack({ 326, 23, 59, 54 });
	charge.PushBack({ 392, 23, 59, 54 });
	charge.PushBack({ 457, 23, 59, 54 });
	charge.PushBack({ 262, 23, 59, 54 }); 
	charge.speed = 0.1f;
	charge.loop = false;

	movement.PushBack({ 0.0f, 1.0f }, 300);
	movingsidetoside = true;
	movement.PushBack({ 0.0f, 0.0f }, 200);
	movement.PushBack({ -0.4f, 0.0f }, 300);
	movement.PushBack({ 0.4f, 0.0f }, 700);
	movement.PushBack({ -0.4f, 0.0f }, 700);
	movement.PushBack({ 0.4f, 0.0f }, 700);
	movement.PushBack({ 0.0f, 3.0f }, 600);
	
	hitsides.PushBack({ 262, 221, 59, 54 });
	hitsides.PushBack({ 262, 221, 59, 54 });
	hitsides.loop = false;
	hitsides.speed = 0.5f;

	hitdown.PushBack({ 6, 221, 59, 54 });
	hitdown.PushBack({ 6, 221, 59, 54 });
	hitdown.loop = false;
	hitdown.speed = 0.5f;

	bonusplane = true;// Bollean to detect if the enemy is a bonus plane and adapt the hitbox

	collider = App->collision->AddCollider({ 0, 0, 60, 60 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	spritesheet = 1;
	animations = 3;
	original_pos.x = x;
	original_pos.y = - 200;
	original_pos1.x = original_pos.x + 47;
	original_pos1.y = original_pos.y - 36;
	original_pos2.x = x + 4;
	original_pos2.y = -200;
	original_pos3.x = x + 4;
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

	w = 59 * 3;
	h = 54 * 3;
	w1 = 32 * 3;
	h1 = 14 * 3;
	w2 = 59 * 3;
	h2 = 54 * 3;
	w3 = 59 * 3;
	h3 = 54 * 3;

	++shoot_time;
	++charge_time;

	if (position.x < 410 || position.x > 410)
	{
		animation = &flysides;
		animation1 = &none;
		animation2 = &none;
		if (charge_time % 190 == 0) 
		{
			animation2 = &charge;
			charge.Reset();
			charge_time = 0;
		}
		if (ishit == true)
		{
			animation2 = &hitsides;
			hitsides.Reset();
			ishit = false;
		}
		side = true;
	
	}
	if (position.y > 70 && side == false)
	{
		animation = &stop;
		animation1 = &none;
		animation2 = &none;
		if (ishit == true)
		{
			animation2 = &hitsides;
			hitsides.Reset();
			ishit = false;
		}
	}
	if (position.y <= 70)
	{
		animation = &flydown;
		animation1 = &propeller;
		animation2 = &none;
		if (ishit2 == true)
		{
			animation2 = &hitdown;
			hitdown.Reset();
			ishit2 = false;
		}
	}
	

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


