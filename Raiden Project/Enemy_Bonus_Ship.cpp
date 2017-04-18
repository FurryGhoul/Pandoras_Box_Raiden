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

	idle.PushBack({ 52, 181, 109, 106 });
	idle.PushBack({ 50, 50, 117, 100 });

	movement.PushBack({ -0.2f, 8.0f }, 50);
	movement.PushBack({ 0.0f, 0.0f }, 50);
	movement.PushBack({ -0.2f, -5.0f }, 600);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Bonus_Ship::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
}


