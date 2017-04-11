#include "Enemy_Light_Shooter.h"
#include "Application.h"

#include "ModuleCollision.h"


Enemy_Light_Shooter::Enemy_Light_Shooter(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 179,0,24,34 });
	fly.speed = 0.2f;
	fly.loop = false;
	animation = &fly;


	movement.PushBack({ -1.0f, -0.5f }, 100);
	movement.PushBack({ -1.0f, 0.5f }, 80);
	movement.PushBack({ -1.0f, 1.0f }, 80);
	collider = App->collision->AddCollider({ 0, 0, 24*3-5, 24*3+20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	w = 24*3;
	h = 34*3;
}

void Enemy_Light_Shooter::Move()
{
	position = original_pos + movement.GetCurrentPosition();
}
