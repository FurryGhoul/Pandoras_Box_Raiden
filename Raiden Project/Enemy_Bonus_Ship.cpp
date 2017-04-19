#include "Enemy_Bonus_Ship.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>



Enemy_Bonus_Ship::Enemy_Bonus_Ship(int x, int y) : Enemy (x, y)
{
	flydown.PushBack({ 316, 161, 114, 128 });
	flydown.PushBack({ 185, 161, 112, 118 });
	flydown.PushBack({ 52, 161, 109, 126 });
	flydown.PushBack({ 50, 26, 117, 126 });
	flydown.speed = 0.05f;

	flysides.PushBack({ 180, 26, 121, 126 });
	flysides.PushBack({ 312, 26, 121, 126 });
	flysides.PushBack({ 442, 26, 121, 126 });
	flysides.PushBack({ 566, 26, 121, 126 });
	flysides.speed = 0.05F;
	flysides.loop = true;


	movement.PushBack({ -0.2f, 8.0f }, 50);
	movement.PushBack({ 0.0f, 0.0f }, 50);
	movement.PushBack({ -0.5f, 0.0f }, 300);
	movement.PushBack({ 0.5f, 0.0f }, 600);
	movement.PushBack({ -0.5f, 0.0f }, 600);
	movement.PushBack({ 0.5f, 0.0f }, 600);


	collider = App->collision->AddCollider({ 20, 0, 120, 126 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	spriteshit = 1;
	original_pos.x = x;
	original_pos.y = - 150;
}

void Enemy_Bonus_Ship::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
	animation = &flydown;
	
	if (position.x < 300 || position.x > 300)
	{
		animation = &flysides;
	}
}


