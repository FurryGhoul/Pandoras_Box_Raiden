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

	hp = 120;
	points = 880;

	shellstart.PushBack({ 8, 7, 81, 53 });
	shellstart.PushBack({ 8, 7, 81, 53 });
	shellstart.PushBack({ 90, 7, 81, 53 });
	shellstart.PushBack({ 90, 7, 81, 53 });
	shellstart.PushBack({ 90, 65, 81, 53 });
	shellstart.PushBack({ 90, 65, 81, 53 });
	shellstart.PushBack({ 172, 65, 81, 53 });
	shellstart.PushBack({ 172, 65, 81, 53 });
	shellstart.PushBack({ 172, 7, 81, 53 });
	shellstart.PushBack({ 172, 7, 81, 53 });
	shellstart.PushBack({ 254, 7, 81, 53 });
	shellstart.PushBack({ 254, 7, 81, 53 });
	shellstart.PushBack({ 254, 65, 81, 53 });
	shellstart.PushBack({ 254, 65, 81, 53 });
	shellstart.PushBack({ 172, 65, 81, 53 });
	shellstart.PushBack({ 172, 65, 81, 53 });
	shellstart.PushBack({ 172, 7, 81, 53 });
	shellstart.PushBack({ 172, 7, 81, 53 });
	shellstart.PushBack({ 336, 7, 81, 53 });
	shellstart.PushBack({ 336, 7, 81, 53 });
	shellstart.PushBack({ 336, 65, 81, 53 });
	shellstart.PushBack({ 336, 65, 81, 53 });
	shellstart.PushBack({ 8, 65, 81, 53 });
	shellstart.PushBack({ 8, 65, 81, 53 });
	shellstart.loop = true;
	shellstart.speed = 0.9f;

	transformation.PushBack({ 90, 123, 81, 53 });
	transformation.PushBack({ 90, 123, 81, 53 });
	transformation.PushBack({ 172, 123, 81, 53 });
	transformation.PushBack({ 172, 123, 81, 53 });
	transformation.PushBack({ 254, 123, 81, 53 });
	transformation.PushBack({ 254, 181, 81, 53 });
	transformation.PushBack({ 172, 181, 81, 53 });
	transformation.PushBack({ 172, 181, 81, 53 });
	transformation.PushBack({ 336, 181, 81, 53 });
	transformation.PushBack({ 336, 181, 81, 53 });
	transformation.PushBack({ 8, 239, 81, 53 });
	transformation.PushBack({ 8, 239, 81, 53 });
	transformation.PushBack({ 8, 239, 81, 53 });
	transformation.PushBack({ 90, 297, 81, 53 });
	transformation.PushBack({ 90, 297, 81, 53 });
	transformation.PushBack({ 172, 297, 81, 53 });
	transformation.PushBack({ 172, 297, 81, 53 });
	transformation.PushBack({ 254, 297, 81, 53 });
	transformation.PushBack({ 254, 355, 81, 53 });
	transformation.PushBack({ 172, 355, 81, 53 });
	transformation.PushBack({ 172, 355, 81, 53 });
	transformation.PushBack({ 336, 355, 81, 53 });
	transformation.PushBack({ 336, 355, 81, 53 });
	transformation.PushBack({ 8, 413, 81, 53 });
	transformation.PushBack({ 8, 413, 81, 53 });
	transformation.PushBack({ 90, 413, 81, 53 });
	transformation.PushBack({ 90, 413, 81, 53 });
	transformation.PushBack({ 172, 413, 81, 53 });
	transformation.PushBack({ 172, 413, 81, 53 });
	transformation.PushBack({ 254, 413, 81, 53 });
	transformation.PushBack({ 254, 413, 81, 53 });
	transformation.loop = false;
	transformation.speed = 0.5f;

	finalform.PushBack({ 336, 413, 81, 53 });
	finalform.PushBack({ 336, 413, 81, 53 });
	finalform.PushBack({ 8, 471, 81, 53 });
	finalform.PushBack({ 8, 471, 81, 53 });
	finalform.PushBack({ 90, 471, 81, 53 });
	finalform.PushBack({ 90, 471, 81, 53 });
	finalform.PushBack({ 172, 471, 81, 53 });
	finalform.PushBack({ 172, 471, 81, 53 });
	finalform.PushBack({ 254, 471, 81, 53 });
	finalform.PushBack({ 254, 471, 81, 53 });
	finalform.PushBack({ 336, 471, 81, 53 });
	finalform.PushBack({ 336, 471, 81, 53 });

	stop.PushBack({ 336, 471, 81, 53 });


	megatank = true;
	
	movement.PushBack({-1.0f, 1.0f}, 250);
	movement.PushBack({ 0.0f, 0.01f}, 70);
	movement.PushBack({ 0.0f, -1.0f}, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 400);
	movement.PushBack({ 0.0f, 1.0f }, 100);
	movement.PushBack({ 0.0f, 4.0f }, 1000);
	
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

	position.x += left_right_mod;



	if (movement.steps[movement.GetCurrentStep()].speed.x == -1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f)
	{
		animation = &shellstart;
	}

	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.01f)
	{
		animation = &transformation;
	}

	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == -1.0f
		|| movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 4.0f)
	{
		animation = &finalform;
		shooting = true;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f)
	{
		animation = &stop;
		shooting = true;
	}

	if (shooting == true)
	{
		++shoot_time;
		if (shoot_time % 140 == 0)
		{
			App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 30 * 3, position.y + 11 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
		}
		if (shoot_time % 145 == 0)
		{
			App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 38 * 3, position.y + 11 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
		}
		if (shoot_time % 150 == 0)
		{
			App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 44 * 3, position.y + 16 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
		}
		if (shoot_time % 155 == 0)
		{
			App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 44 * 3, position.y + 23 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
		}
		if (shoot_time % 160 == 0)
		{
			App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 38 * 3, position.y + 29 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
		}
		if (shoot_time % 165 == 0)
		{
			App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 30 * 3, position.y + 29 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
		}
		if (shoot_time % 170 == 0)
		{
			App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 24 * 3, position.y + 23 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
		}
		if (shoot_time % 175 == 0)
		{
			App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 24 * 3, position.y + 16 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
		}
		if (shoot_time == 200)
		{
			shoot_time = 100;
			++shoot_time;
		}
		shooting = false;

	}
}