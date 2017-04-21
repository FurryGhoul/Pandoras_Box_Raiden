#include "Tank.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#define PI 3.14159265

Tank::Tank(int x, int y) : Enemy(x, y)
{
	
	spriteshit = 2;
	animations = 2;
	// Tank animations
	downup.PushBack({ 2, 4, 24, 26 });

	leftright.PushBack({ 30,5, 30, 16 });


	neutraldiagonalleft.PushBack({ 61,1,31,30 });


	downdiagonalleft.PushBack({ 126,2, 30, 29 });


	updiagonalleft.PushBack({ 157, 4, 31, 25 });


	neutraldiagonalright.PushBack({ 94, 2, 30, 28});


	downdiagonalright.PushBack({222, 3, 30, 28});


	updiagonalright.PushBack({ 189,5, 31, 26 });

	//Turret animations
	s.PushBack({ 2,49,17,24 });

	se1.PushBack({ 446,46,16,23 });

	se2.PushBack({ 206,48, 21,20 });

	se3.PushBack({ 414,47,26,18 });

	e.PushBack({ 86,51, 27, 13 });

	ne1.PushBack({379,48,25,18});

	ne2.PushBack({175,47,20,21});

	ne3.PushBack({351,45,15,24});

    n.PushBack({ 61,43,15,26 });

	nw1.PushBack({323,44,16,24});

	nw2.PushBack({147,48, 21,20});

	nw3.PushBack({289,49, 25, 17});

	w11.PushBack({ 26,54,27,14 });

	sw1.PushBack({259,49, 24, 16});

	sw2.PushBack({116,51,21, 20});

	sw3.PushBack({238,45,14,23});

	
	original_pos.x = x;
	original_pos.y = -50;


	movement.PushBack({  0.5f, 3.0f }, 100);
	movement.PushBack({  0.5f, 2.0f }, 600);


	collider = App->collision->AddCollider({ 0, 0, 24 * 3 - 5, 26 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->enemies);
	animation = &updiagonalleft;
}


void Tank::MoveShoot()
{
	// Movement of the tank
	position1 = position = original_pos + movement.GetCurrentPosition();

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
	animation = &updiagonalleft;
	animation1 = &s;
	w = 34 * 3;
	h = 25 * 3;
	collider->SetSize(w, h);
	if (movement.steps[movement.GetCurrentStep()].speed.x == -0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 3.0f)
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
	  h = 20 * 3;
	 collider->SetSize(w, h);
	}

	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f)
	{
		animation = &leftright;

		w = 30 * 3;
		h = 20 * 3;
		collider->SetSize(w, h);
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 3.0f)
	{
		animation = &updiagonalright;

		w = 30 * 3;
		h = 28 * 3;
		collider->SetSize(w, h);
	}

	//Movement of the turret
	param = (abs(distance.y) / (abs(distance.x) + 0.1));
	angle = atan(param) * 180 / PI;

	// South-East position
	if (distance.y > 0 && distance.x > 0)
	{
		se = true;
	}
	else
	{
		se = false;
	}

	// South-West position
	if (distance.y > 0 && distance.x < 0)
	{
		sw = true;
	}
	else
	{
		sw = false;
	}

	// North-East position
	if (distance.y < 0 && distance.x > 0)
	{
		ne = true;
	}
	else
	{
		ne = false;
	}

	// North-West position
	if (distance.y < 0 && distance.x < 0)
	{
		nw = true;
	}
	else
	{
		nw = false;
	}

	// Applying animation

	// South to East
	if (se && angle > 72 && angle < 90)
	{
		animation1 = &s;
		w1 = 22 * 3;
		h1 = 30 * 3;
	}
	if (se && angle > 54 && angle < 72)
	{
		animation1 = &se1;
		w1 = 25 * 3;
		h1 = 30 * 3;
	}
	if (se && angle > 36 && angle < 54)
	{
		animation1 = &se2;
		w1 = 27 * 3;
		h1 = 25 * 3;
	}
	if (se && angle > 18 && angle < 36)
	{
		animation1 = &se3;
		w1 = 31 * 3;
		h1 = 23 * 3;
	}
	if (se && angle > 0 && angle < 18)
	{
		animation1 = &e;
		w1 = 32 * 3;
		h1 = 30 * 3;
	}

	// East to North
	if (ne && angle > 0 && angle < 18)
	{
		animation1 = &e;
		w1 = 32 * 3;
		h1 = 30 * 3;
	}
	if (ne && angle > 18 && angle < 36)
	{
		animation1 = &ne1;
		w1 = 31 * 3;
		h1 = 23 * 3;
	}
	if (ne && angle > 36 && angle < 54)
	{
		animation1 = &ne2;
		w1 = 27 * 3;
		h1 = 26 * 3;
	}
	if (ne && angle > 54 && angle < 72)
	{
		animation1 = &ne3;
		w1 = 25 * 3;
		h1 = 30 * 3;
	}
	if (ne && angle > 72 && angle < 90)
	{
		animation1 = &n;
		w1 = 22 * 3;
		h1 = 30 * 3;
	}

	// North to West
	if (nw && angle > 72 && angle < 90)
	{
		animation1 = &n;
		w1 = 22 * 3;
		h1 = 30 * 3;
	}
	if (nw && angle > 54 && angle < 72)
	{
		animation1 = &nw1;
		w1 = 25 * 3;
		h1 = 30 * 3;
	}
	if (nw && angle > 36 && angle < 54)
	{
		animation1 = &nw2;
		w1 = 27 * 3;
		h1 = 25 * 3;
	}
	if (nw && angle > 18 && angle < 36)
	{
		animation1 = &nw3;
		w1 = 31 * 3;
		h1 = 23 * 3;
	}
	if (nw && angle > 0 && angle < 18)
	{
		animation1 = &w11;
		w1 = 32 * 3;
		h1 = 28 * 3;
	}

	// West to South
	if (sw && angle > 0 && angle < 18)
	{
		animation1 = &w11;
		w1 = 32 * 3;
		h1 = 28 * 3;
	}
	if (sw && angle > 18 && angle < 36)
	{
		animation1 = &sw1;
		w1 = 31 * 3;
		h1 = 23 * 3;
	}
	if (sw && angle > 36 && angle < 54)
	{
		animation1 = &sw2;
		w1 = 27 * 3;
		h1 = 26 * 3;
	}
	if (sw && angle > 54 && angle < 72)
	{
		animation1 = &sw3;
		w1 = 24 * 3;
		h1 = 30 * 3;
	}
	if (sw && angle > 72 && angle < 90)
	{
		animation1 = &s;
		w1 = 22 * 3;
		h1 = 30 * 3;
	}
	distance.x = abs(distance.x);
	distance.y = abs(distance.y);
	// Shooting
	if (sqrtf(distance.x*distance.x + distance.y*distance.y) < 500 && shooting == false)
	{
		if (App->player->position.y - 22 < (position.y - 22 * 3))
		{
			distance.y *= -1;
		}
		if (App->player->position.x < (position.x + 22))
		{
			distance.x *= -1;
		}
		App->particles->AddParticle(App->particles->enemyshot, position.x + 10, position.y + 50, COLLIDER_ENEMY_SHOT, 0, distance.x * 0.03, distance.y * 0.03); //In theory, the speed should be distance.x and distance.y, but at the moment it doesn't work that way

		shooting = true;
	}
}
