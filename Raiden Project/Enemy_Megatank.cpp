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
	hp = 30;
	points = 1120;

	spritesheet = 9;
	animations = 1;
	megatank = true;

	idle.PushBack({ 71,10,56,53 });

	hit.PushBack({ 242, 10, 56, 53 });

	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });

	spinning.loop = true;
	spinning.speed = 1.0f;
	//DECELERATION
	decelaration.PushBack({ 14,10,56,53 });
	decelaration.PushBack({ 14,10,56,53 });
	decelaration.PushBack({ 14,10,56,53 });
	decelaration.PushBack({ 14,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 128,10,56,53 });
	decelaration.PushBack({ 128,10,56,53 });
	decelaration.PushBack({ 128,10,56,53 });
	decelaration.PushBack({ 128,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });

	
	decelaration.loop = false;
	decelaration.speed = 0.5f;
	
	

	movement.PushBack({ 0.0f, 1.0f }, 10000);

	collider = App->collision->AddCollider({ 0, 0, 48 * 3, 45 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = 50;
}


void Enemy_Megatank::MoveShoot()
{
	w = 56 * 3;
	h = 53 * 3;

	collider->SetSize(w, h);

	position = original_pos + movement.GetCurrentPosition();
	position.x += left_right_mod;

	++charge;

	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f)
	{
		animation = &spinning;
		/*if (slow == false)
		{
			animation = &spinning;
			if (spinning.Finished() == true)
			{
				spinning.Reset();
				slow = true;
			}
		}

		if (slow == true)
		{
			animation = &decelaration;
			if (decelaration.Finished() == true)
			{
				animation = &spinning;
				
			}
		}*/
		
		/*animation = &spinning;
		if (spinning.Finished() == true)
		{
			animation = &decelaration;
			spinning.Reset();
			if (decelaration.Finished() == true)
			{
				animation = &spinning;
				decelaration.Reset();
				if (spinning.Finished() == true)
				{
					animation = &decelaration;
				}
			}
		}*/
	

	}
	

	if (ishit == true)
	{
		animation = &hit;
		ishit = false;
	}
	
}