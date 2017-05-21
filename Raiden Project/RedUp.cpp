#include "RedUp.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"


#define PI 3.14159265

RedUp::RedUp(int x, int y, double pcenterx, double pcentery, double pangle, bool first) : PowerUp(x, y, pcentery, pcenterx, pangle)
{
	//Red PowerUp animation sprite
	idle1.PushBack({ 2, 2, 16, 13 });
	idle1.PushBack({ 22, 2, 16, 13 });
	idle1.PushBack({ 41, 2, 16, 13 });
	idle1.speed = 0.1;
   
	redp = true;
	movement.PushBack({ 0.0f, 4.0f }, 100);
	movement.PushBack({ 4.0f, 0.0f }, 100);
	movement.PushBack({ 0.0f, -2.0f }, 100);
	movement.PushBack({ -4.0f,0.0f }, 100);

	collider = App->collision->AddCollider({ 0, 0, 16 * 3 - 5, 14 * 3 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->powerups, 10);

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


void RedUp::Move()
{
	pos_mod.x = sin(angle)* radius;
	pos_mod.y = cos(angle) * radius;

	
	angle-= 0.01;

	
 	position.x = center.x + pos_mod.x;
	position.y = center.y + pos_mod.y;

	//position.x += left_right_mod;
}