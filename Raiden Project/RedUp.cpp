#include "RedUp.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

RedUp::RedUp(int x, int y) : PowerUp(x, y)
{
	//Red PowerUp animation sprite
	idle1.PushBack({ 2, 2, 15, 13 });
	idle1.PushBack({ 22, 2, 15, 13 });
	idle1.PushBack({ 41, 2, 15, 13 });
	idle1.speed = 0.1;
   

	movement.PushBack({ 0.0f, 4.0f }, 100);
	movement.PushBack({ 4.0f, 0.0f }, 100);
	movement.PushBack({ 0.0f, -2.0f }, 100);
	movement.PushBack({ -4.0f,0.0f }, 100);

	collider = App->collision->AddCollider({ 0, 0, 16 * 3 - 5, 14 * 3 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->powerups, 10);

	w = 15 * 3;
	h = 13 * 3;

	position.x = original_pos.x = x;
    position.y = original_pos.y = 100;
	animation = &idle1;
}


void RedUp::Move()
{
	position = original_pos + movement.GetCurrentPosition();
}