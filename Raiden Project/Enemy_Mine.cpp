#include "Enemy_Mine.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleShadows.h"


Enemy_Mine::Enemy_Mine(int x, int y, int path) : Enemy(x, y)
{
	points = 180;
	mine = true;
	animations = 1;
	hp = 4;
	idle.PushBack({ 73,6,24,34 });
	idle.PushBack({ 97,6,24,34 });
	idle.PushBack({ 117,6,24,34 });
	idle.loop = true;
	idle.speed = 0.3f;
	hit.PushBack({ 163,6,24,34 });


	to_explode.PushBack({ 73,6,24,34 });
	to_explode.PushBack({ 192,6,24,34 });
	to_explode.PushBack({ 97,6,24,34 });
	to_explode.PushBack({ 216,6,24,34 });
	to_explode.PushBack({ 238,6,24,34 });
	to_explode.PushBack({ 117,6,24,34 });
	to_explode.loop = true;
	to_explode.speed = 0.6f;


	spritesheet = 11;

	w = 24 * 3;
	h = 34 * 3;
	movement.PushBack({ 0.0f,1.2f }, 100);
	collider = App->collision->AddCollider({ 0, 0, w, h }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_pos.x = x;
	original_pos.y = -100;

}


void Enemy_Mine::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();

	position.x += left_right_mod;
	animation = &idle;
	if (hp <= 2)
	{
		animation = &to_explode;
	}
	if (ishit)
	{
		animation = &hit;
		ishit = false;
	}
	
	if (shadowregulator % 2 == 0)
	{
		if (shadowdirection == 0)
			App->shadows->AddShadow(App->shadows->Mine, position.x, position.y, 30 * 3, 22 * 3);
	}
	shadowregulator++;

}
