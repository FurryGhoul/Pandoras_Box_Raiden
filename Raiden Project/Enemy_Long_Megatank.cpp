#include "Enemy_Long_Megatank.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"


Enemy_Long_Megatank::Enemy_Long_Megatank(int x, int y, int path) : Enemy(x, y)
{
	spritesheet = 6;
	animations = 1;

	shellstart.PushBack({ 8, 7, 81, 53 });
	shellstart.PushBack({ 90, 7, 81, 53 });
	shellstart.PushBack({ 90, 65, 81, 53 });
	shellstart.PushBack({ 172, 65, 81, 53 });
	shellstart.PushBack({ 172, 7, 81, 53 });
	shellstart.PushBack({ 254, 7, 81, 53 });
	shellstart.PushBack({ 254, 65, 81, 53 });
	shellstart.PushBack({ 172, 65, 81, 53 });
	shellstart.PushBack({ 172, 7, 81, 53 });
	shellstart.PushBack({ 336, 7, 81, 53 });
	shellstart.PushBack({ 336, 65, 81, 53 });
	shellstart.PushBack({ 8, 65, 81, 53 });
	shellstart.loop = true;
	shellstart.speed = 0.1f;

	megatank = true;
	
	movement.PushBack({-0.3f, 1.0},500);
	collider = App->collision->AddCollider({ 0, 0, 24 * 3 - 5, 26 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->enemies);
	
	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Long_Megatank::MoveShoot()
{
	w = 81 * 3;
	h = 53 * 3;
	collider->SetSize(w, h);

	position = original_pos + movement.GetCurrentPosition();

	animation = &shellstart;
}


