#include "Enemy_Megatank.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"



Enemy_Megatank::Enemy_Megatank(int x, int y, int path) : Enemy(x, y)
{
	spritesheet = 10;
	animations = 1;
	megatank = true;

	idle.PushBack({ 71,10,56,53 });

	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.loop = true;
	spinning.speed = 0.5f;

	movement.PushBack({ 0.0f, 4.0f }, 10000);

	collider = App->collision->AddCollider({ 0, 0, 48 * 3, 45 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = 50;
}


void Enemy_Megatank::MoveShoot()
{
	w = 56 * 3;
	h = 53 * 3;


	position = original_pos + movement.GetCurrentPosition();
	position.x += left_right_mod;

	++charge;

	if (charge % 200 == 0)
	{
		animation = &spinning;
	}
	else
	{
		animation = &idle;
	}
}