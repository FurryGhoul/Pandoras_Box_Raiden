#include "Enemy_Ship_Tank.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"
#define PI 3.14159265

Enemy_Ship_Tank::Enemy_Ship_Tank(int x, int y, int path) : Enemy(x, y)
{
	hp = 3;
	points = 130;

	spritesheet = 2;
	animations = 3;

	// Tank animations	
	up.PushBack({ 20, 99, 23, 30 });
	down.PushBack({ 71, 100, 23, 30 });
	left.PushBack({ 117, 104, 32, 21 });
	right.PushBack({ 162, 104, 32, 21 });

	// Water animation
	waterup1.PushBack({ 38, 141, 33, 29 });
	waterup2.PushBack({ 85, 141, 33, 29 });
	waterup3.PushBack({ 138, 142, 33, 29 });

	waterdown1.PushBack({ 38, 181, 33, 29 });
	waterdown2.PushBack({ 85, 181, 33, 29 });
	waterdown3.PushBack({ 138, 181, 33, 29 });

	//Turret animations
	s.PushBack({ 3, 44, 38, 34 });
	hits.PushBack({ 4, 135, 38, 34 });

	se1.PushBack({ 44, 44, 38, 34 });
	hitse1.PushBack({ 45, 135, 38, 34 });

	se2.PushBack({ 85, 44, 38, 34 });
	hitse2.PushBack({ 86, 135, 38, 34 });

	se3.PushBack({ 126, 44, 38, 34 });
	hitse3.PushBack({ 127, 135, 38, 34 });

	e.PushBack({ 167, 44, 38, 34 });
	hite.PushBack({ 168, 135, 38, 34 });

	ne1.PushBack({ 208, 44, 38, 34 });
	hitne1.PushBack({ 209, 135, 38, 34 });

	ne2.PushBack({ 249, 44, 38, 34 });
	hitne2.PushBack({ 250, 135, 38, 34 });

	ne3.PushBack({ 290, 44, 38, 34 });
	hitne3.PushBack({ 291, 135, 38, 34 });

	n.PushBack({ 331, 44, 38, 34 });
	hitn.PushBack({ 332, 135, 38, 34 });

	nw1.PushBack({ 372, 44, 38, 34 });
	hitnw1.PushBack({ 373, 135, 38, 34 });

	nw2.PushBack({ 413, 44, 38, 34 });
	hitnw2.PushBack({ 414, 135, 38, 34 });

	nw3.PushBack({ 454, 44, 38, 34 });
	hitnw3.PushBack({ 455, 135, 38, 34 });

	w11.PushBack({ 495, 44, 38, 34 });
	hitw11.PushBack({ 496, 135, 38, 34 });

	sw1.PushBack({ 536, 44, 38, 34 });
	hitsw1.PushBack({ 537, 135, 38, 34 });

	sw2.PushBack({ 577, 44, 38, 34 });
	hitsw2.PushBack({ 578, 135, 38, 34 });

	sw3.PushBack({ 618, 44, 38, 34 });
	hitsw3.PushBack({ 619, 135, 38, 34 });


	// Movement
	movement.PushBack({ 0.0f, 3.0f }, 100);
	//movement.PushBack({ 0.0f, 0.0f }, 100);

	original_pos.x = x;
	original_pos.y = -50;

	//tank = true;
	collider = App->collision->AddCollider({ 0, 0, 23 * 3 - 5, 30 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->enemies);
	animation = &up;
}

void Enemy_Ship_Tank::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
	position.x += left_right_mod;

	if (sqrtf((distance.y = App->player->position.y - 22 - position.y - 22 * 3)*(distance.y = App->player->position.y - 22 - position.y - 22 * 3) + (distance.x = App->player->position.x - position.x + 22)* (distance.x = App->player->position.x - position.x + 22))
		< sqrtf((distance.y = App->player2->position.y - 22 - position.y - 22 * 3)*(distance.y = App->player2->position.y - 22 - position.y - 22 * 3) + (distance.x = App->player2->position.x - position.x + 22)* (distance.x = App->player2->position.x - position.x + 22)))
	{
		distance.y = App->player->position.y - 22 - position.y - 22 * 3;
		distance.x = App->player->position.x - position.x + 22;
	}
	else
	{
		distance.y = App->player2->position.y - 22 - position.y - 22 * 3;
		distance.x = App->player2->position.x - position.x + 22;
	}

	// Animation of the tank	
	w = 23 * 3;
	h = 30 * 3;
	collider->SetSize(w, h);

	// Down
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 3.0f)
	{
		animation = &down;

		//position1.x = position.x + w / 2;
		//position1.y = position.y + h / 2 - 5;
	}

	// Up
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == -3.0f)
	{
		animation = &up;
	}
}