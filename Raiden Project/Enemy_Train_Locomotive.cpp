#include "Enemy_Train_Locomotive.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleGroundEnemies.h"

#define PI 3.14159265

Enemy_Train_Locomotive::Enemy_Train_Locomotive(int x, int y, int path) : Enemy(x, y)
{
	hp = 8;
	points = 480;

	// Anmiation pushback's

	// Idle
	horizontal.PushBack({ 2, 15, 48, 24 });
	diagonal.PushBack({ 136, 3, 38, 37 });
	// Hit
	hithorizontal.PushBack({ 2, 55, 48, 24 });
	hitdiagonal.PushBack({ 136, 42, 38, 37 });
	
	// Paths
	if (path == 0)
	{
		movement.PushBack({ -2.3f, 1.5f }, 1000);
		movement.loop = false;

		collider = App->collision->AddCollider({ 0, 0, 48 * 3, 24 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->genemies);
		original_pos.y = 50;
	}
	if (path == 1)
	{
		movement.PushBack({ -1.5f, -0.1f }, 1000);
		movement.loop = false;

		collider = App->collision->AddCollider({ 0, 0, 38 * 3, 37 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->genemies);
		original_pos.y =  320;
	}

	//Parts info
	/*firstcoach.type = GENEMY_TYPES::TRAIN_COACH;
	firstcoach._path = 0;
	firstcoach.x = position.x + 48;
	firstcoach.y = position.y;*/

	trainlocomotive = true;
	
	spritesheet = 8;
	animations = 1;
	original_pos.x = x;
}


void Enemy_Train_Locomotive::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
	position.x += left_right_mod;
	

	//App->enemies->SetPos();

	//Train parts
	/*if (!parts)
	{
		App->genemies->SpawnGroundEnemy(firstcoach);
		parts = true;
	}*/

	// Animation
	animation = &horizontal;
	w = 48 * 3;
	h = 24 * 3;

	distance.x = fabs(distance.x);
	distance.y = fabs(distance.y);
	
	if (movement.steps[movement.GetCurrentStep()].speed.x == -2.3f && movement.steps[movement.GetCurrentStep()].speed.y == 1.5f)
	{
		animation = &horizontal;

		if (ishit == true)
		{
			animation = &hithorizontal;
			ishit = false;
		}

		w = 48 * 3;
		h = 24 * 3;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == -1.5f && movement.steps[movement.GetCurrentStep()].speed.y == -0.1f)
	{
		animation = &diagonal;

		if (ishit == true)
		{
			animation = &hitdiagonal;
			ishit = false;
		}

		w = 38 * 3;
		h = 37 * 3;
	}
}
