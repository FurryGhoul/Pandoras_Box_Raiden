#include "Enemy_Bonus_Ship.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "Enemy.h"
#include <Math.h>



Enemy_Bonus_Ship::Enemy_Bonus_Ship(int x, int y) : Enemy (x, y)
{
	flydown.PushBack({ 6, 23, 54, 52 });

	stop.PushBack({ 67, 23, 54, 52 });
	stop.PushBack({ 262, 23, 54, 52 });
	//stop.speed = 0.04;

	flysides.PushBack({ 131, 23, 59, 54 });
	flysides.PushBack({ 197, 23, 59, 54 });
	//flysides.speed = 0.2f;
	//flysides.loop = true;

	propeller.PushBack({ 143, 83, 32, 14 });
	propeller.PushBack({ 194, 83, 32, 14 });
	propeller.speed = 0.5f;
	propeller.loop = true;

	movement.PushBack({ 0.0f, 1.5f }, 300);
	movement.PushBack({ 0.0f, 0.0f }, 50);
	movement.PushBack({ -0.5f, 0.0f }, 300);
	movement.PushBack({ 0.5f, 0.0f }, 600);
	movement.PushBack({ -0.5f, 0.0f }, 600);
	movement.PushBack({ 0.5f, 0.0f }, 600);

	bonusplane = true;// Bollean to detect if the enemy is a bonus plane and adapt the hitbox

	collider = App->collision->AddCollider({ 0, 0, 60, 60 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	spriteshit = 1;
	animations = 2;
	original_pos.x = x;
	original_pos.y = - 200;
	original_pos1.x = + 455;
	original_pos1.y = - 236;
}

void Enemy_Bonus_Ship::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
	position1 = original_pos1 + movement.GetCurrentPosition();
	w = 54 * 3;
	h = 52 * 3;
	w1 = 32 * 3;
	h1 = 14 * 3;
	if (position.x < 410 || position.x > 410)
	{
		animation = &flysides;
		side = true;
	}
	if (position.y > 234 && side == false)
	{
		animation = &stop;
	}
	if (position.y <= 234 && position1.y <= 270)
	{
		animation1 = &propeller;
		animation = &flydown;
	}
	
	
}


