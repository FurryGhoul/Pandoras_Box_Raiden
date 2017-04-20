#include "Tank.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>


Tank::Tank(int x, int y) : Enemy(x, y)
{
	
	spriteshit = 2;
	animations = 1;
	downup.PushBack({ 2, 4, 24, 26 });
	leftright.PushBack({ 30,5, 30, 16 });
	neutraldiagonalleft.PushBack({ 61,1,31,30 });
	downdiagonalleft.PushBack({ 126,2, 30, 29 });
	updiagonalleft.PushBack({ 157, 4, 31, 25 });
	neutraldiagonalright.PushBack({ 94, 2, 30, 28});
	downdiagonalright.PushBack({222, 3, 30, 28});
	updiagonalright.PushBack({ 189,5, 31, 26 });

	w = 24 * 3;
	h = 26 * 3;


	original_pos.x = x;
	original_pos.y = -50;


	movement.PushBack({ -0.5f, 4.0f }, 100);
	movement.PushBack({ -0.5f, 2.0f }, 600);


	collider = App->collision->AddCollider({ 0, 0, 24 * 3 - 5, 26 * 3 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}


void Tank::MoveShoot()
{

	position = original_pos + movement.GetCurrentPosition();
	animation = &updiagonalleft;
	w = 34 * 3;
	h = 25 * 3;
	collider->SetSize(w, h);
	if (movement.steps[movement.GetCurrentStep()].speed.x == -0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 4.0f)
	{ 
	animation = &updiagonalleft;
	w = 34 * 3;
	h = 25 * 3;
	collider->SetSize(w, h);
	}
	
	if (movement.steps[movement.GetCurrentStep()].speed.x == -0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f)
	{ 
	  animation = &leftright;

	  w = 30 * 3;
	  h = 16 * 3;
	 collider->SetSize(w, h);
	}
}
