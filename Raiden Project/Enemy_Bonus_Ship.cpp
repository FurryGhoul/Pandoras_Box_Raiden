#include "Enemy_Bonus_Ship.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "Enemy.h"
#include <Math.h>



Enemy_Bonus_Ship::Enemy_Bonus_Ship(int x, int y) : Enemy (x, y)
{
	hp = 17;
	points = 480;

	flydown.PushBack({ 6, 23, 59, 54 });

	stop.PushBack({ 67, 23, 59, 54 });
	stop.PushBack({ 262, 23, 59, 54 });

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
	charge.speed = 2.0f;
	charge.loop = true;

	movement.PushBack({ 0.0f, 1.5f }, 300);
	movement.PushBack({ 0.0f, 0.0f }, 200);
	movement.PushBack({ -0.5f, 0.0f }, 300);
	movement.PushBack({ 0.5f, 0.0f }, 600);
	movement.PushBack({ -0.5f, 0.0f }, 600);
	movement.PushBack({ 0.5f, 0.0f }, 600);
	movement.PushBack({ -0.5f, 0.0f }, 600);
	movement.PushBack({ 0.5f, 0.0f }, 600);
	movement.PushBack({ -0.5f, 0.0f }, 600);
	movement.PushBack({ 0.5f, 0.0f }, 600);
	movement.PushBack({ -0.5f, 0.0f }, 600);
	movement.PushBack({ 0.5f, 0.0f }, 600);
	movement.PushBack({ -0.5f, 0.0f }, 600);
	movement.PushBack({ 0.5f, 0.0f }, 600);


	bonusplane = true;// Bollean to detect if the enemy is a bonus plane and adapt the hitbox

	collider = App->collision->AddCollider({ 0, 0, 60, 60 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	spriteshit = 1;
	animations = 2;
	original_pos.x = x;
	original_pos.y = - 200;
	original_pos1.x = + 457;
	original_pos1.y = - 238;
	/*original_pos2.x = x + 4;
	original_pos2.y = -200;*/
}

void Enemy_Bonus_Ship::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
	position1 = original_pos1 + movement.GetCurrentPosition();
	position2 = original_pos2 + movement.GetCurrentPosition();
	position.x += left_right_mod;
	position1.x += left_right_mod;
	position2.x += left_right_mod;

	w = 59 * 3;
	h = 54 * 3;
	w1 = 32 * 3;
	h1 = 14 * 3;
	/*w2 = 59 * 3;
	h2 = 54 * 3;*/
	if (position.x < 410 || position.x > 410)
	{
		animation = &flysides;
		animation1 = &none;
		//animation2 = &charge;
		side = true;
	}
	if (position.y > 234 && side == false)
	{
		animation = &stop;
		animation1 = &none;
		//animation2 = &none;
	}
	if (position.y <= 234)
	{
		//animation2 = &none;
		animation1 = &propeller;
		animation = &flydown;
	}
	
	if (shooting == false && movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f)
	{
	
		App->particles->AddParticle(App->particles->enemyshot, position.x + 78, position.y + 60, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y + 4);
		App->particles->AddParticle(App->particles->enemyshot, position.x + 78, position.y + 60, COLLIDER_ENEMY_SHOT, 0, distance.x - 1, distance.y + 4);
		App->particles->AddParticle(App->particles->enemyshot, position.x + 78, position.y + 60, COLLIDER_ENEMY_SHOT, 0, distance.x + 1, distance.y + 4);

		shooting = true;
	}
}


