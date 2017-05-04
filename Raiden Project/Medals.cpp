#include "Medals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

Medals::Medals(int x, int y) : PowerUp(x, y)
{
	//Red PowerUp animation sprite
	idle1.PushBack({ 118, 1, 10, 16 });

	collider = App->collision->AddCollider({ 0, 0, 10 * 3 - 5, 16 * 3 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->powerups);

	w = 16 * 3;
	h = 14 * 3;

	position.x = original_pos.x = x;
	position.y = original_pos.y = 100;
	animation = &idle1;
}