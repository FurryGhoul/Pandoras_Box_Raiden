#include "RedUp.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

RedUp::RedUp(int x, int y) : PowerUp(x, y)
{
	//Red PowerUp animation sprite
	idle1.PushBack({ 1, 1, 16, 14 });
	idle2.PushBack({ 21, 1, 16, 30 });
	idle3.PushBack({ 40, 1, 16, 30 });

	movement.PushBack({ -0.2f, 8.0f }, 50);
	movement.PushBack({ 0.0f, 0.0f }, 50);
	movement.PushBack({ -0.2f, -5.0f }, 600);

	collider = App->collision->AddCollider({ 0, 0, 16 * 3 - 5, 14 * 3 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->powerups);

	w = 16 * 3;
	h = 14 * 3;

	original_pos.x = x;
	original_pos.y = 100;
}
