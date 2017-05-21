#include "BlueUp.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#define PI 3.14159265

BlueUp::BlueUp(int x, int y, double pcenterx, double pcentery, double pangle, bool first) : PowerUp(x, y, pcentery, pcenterx, pangle)
{
	//Blue PowerUp animation sprite
	idle1.PushBack({ 59, 2, 16, 13 });
	idle1.PushBack({ 78, 2, 16, 13 });
	idle1.PushBack({ 96, 2, 16, 13 });
	idle1.speed = 0.1;

	bluep = true;

	collider = App->collision->AddCollider({ 0, 0, 16 * 3 - 5, 14 * 3 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->powerups, 15);

	w = 15 * 3;
	h = 13 * 3;


	radius = 150;
	position.x = original_pos.x = x;
	position.y = original_pos.y = y;
	animation = &idle1;
	if (first)
	{
		center.y = position.y + radius;
		center.x = position.x;
		angle = PI / 2;
	}
	else
	{
		center.y = pcentery;
		center.x = pcenterx;
		angle = pangle;
	}
}


void BlueUp::Move()
{
	pos_mod.x = sin(angle)* radius;
	pos_mod.y = cos(angle) * radius;


	angle -= 0.01;


	position.x = center.x + pos_mod.x;
	position.y = center.y + pos_mod.y;
}
