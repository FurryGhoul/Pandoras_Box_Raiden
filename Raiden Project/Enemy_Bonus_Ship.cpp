#include "Enemy_Bonus_Ship.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>



Enemy_Bonus_Ship::Enemy_Bonus_Ship(int x, int y) : Enemy (x, y)
{
	flydown.PushBack({ 316, 158, 114, 128 });
	flydown.PushBack({ 185, 166, 112, 118 });
	flydown.PushBack({ 52, 181, 109, 106 });
	flydown.PushBack({ 50, 50, 117, 100 });
	flydown.speed = 0.05f;

	movement.PushBack({ -0.2f, 8.0f }, 50);
	movement.PushBack({ 0.0f, 0.0f }, 50);
	movement.PushBack({ -0.5f, 0.0f }, 300);
	movement.PushBack({ 0.5f, 0.0f }, 600);

	collider = App->collision->AddCollider({ 0, 0, 120, 110 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	spriteshit = 2;
	original_pos.x = x;
	original_pos.y = - 150;
}

void Enemy_Bonus_Ship::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
	animation = &flydown;
	
}


