#include "Medals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

Medals::Medals(int x, int y) : PowerUp(x, y)
{

	idle1.PushBack({ 118, 1, 10, 16 });

	movement.PushBack({ 0.0f, 1.0f }, 100);

	medal = true;
	collider = App->collision->AddCollider({ 3, 0, 11 * 3 - 5, 16 * 3 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->powerups, 12);

	w = 10 * 3;
	h = 16 * 3;

	position.x = original_pos.x = x;
	position.y = original_pos.y = y;
	animation = &idle1;
}

void Medals::Move()
{
	position = original_pos + movement.GetCurrentPosition();
	position.x += left_right_mod;
}