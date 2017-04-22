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
	hp = 1;
	points = 130;

	spriteshit = 2;
	animations = 2;
	// Tank animations
	downup.PushBack({ 2, 4, 24, 26 }); // done

	leftright.PushBack({ 30,5, 30, 16 }); // done


	neutraldiagonalleft.PushBack({ 61,1,31,30 }); // done


	downdiagonalleft.PushBack({ 126,2, 30, 29 }); // done


	updiagonalleft.PushBack({ 157, 4, 31, 25 }); // Not in usage


	neutraldiagonalright.PushBack({ 94, 2, 30, 28}); //in proces


	downdiagonalright.PushBack({222, 3, 30, 28}); // done


	updiagonalright.PushBack({ 189,5, 31, 26 }); // Not in usage

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

	//Paths (there should be more than one path and an integer to select what path to use
	/*Instructions for pathing the enemies:  
	0.0, 4.0 = down
	0.0, 0.0 = up
	-0.5, 2.0 = left
	-0.5, 2.0 = right
	-0.5, 3.0 = down diagonal left
	-0.5, -1.0 = up diagonal right
	-0.5, -1.0 = up diagonal left
	0.5, 3.0 =  down diagonal right
	1.0,-1.0 = Neutral diagonal up right
	-1.0, 3.0 =Neutral diagonal down left
	-1.0, 1.0 = Neutral diagonal up left
	1.0, 3.0 = Neutral diagonal down right
	*/
	movement.PushBack({  0.0f, 4.0f }, 100);
	movement.PushBack({  -1.0f, 1.0f }, 100);
	movement.PushBack({  0.0f, 0.0f }, 6000);


	collider = App->collision->AddCollider({ 0, 0, 24 * 3 - 5, 26 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->enemies);
	animation = &updiagonalleft;
}


void Tank::MoveShoot()
{	
	// Calculation between tank and player and movement of the tank
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
	
	// Down and up
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f)
	{
		animation = &downup;

		w = 24 * 3;
		h = 26 * 3;
		collider->SetSize(w, h);

	   position1.x = position.x + w / 2;
	   position1.y = position.y + h / 2 - 5;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 4.0f)
	{
		animation = &downup;

		w = 24 * 3;
		h = 26 * 3;
		collider->SetSize(w, h);

		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2 - 5;
	}

	// Left and right
     if (movement.steps[movement.GetCurrentStep()].speed.x == -0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f)
	{ 
	  animation = &leftright;

	  w = 30 * 3;
	  h = 20 * 3;
	 collider->SetSize(w, h);
	 position1.x = position.x + w / 2 + 10;
	 position1.y = position.y + h / 2;
	}


	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f)
	{
		animation = &leftright;

		w = 30 * 3;
		h = 20 * 3;
		collider->SetSize(w, h);
		position1.x = position.x + w / 2 + 10;
		position1.y = position.y + h / 2;
	}

	// Down diagonal left and up diagonal right
	if (movement.steps[movement.GetCurrentStep()].speed.x == -0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 3.0f)
	{ 
	animation = &downdiagonalleft;
    w = 30 * 3;
	h = 29 * 3;
	collider->SetSize(w, h);
	position1.x = position.x + w / 2;
	position1.y = position.y + h / 2;
	}


   if (movement.steps[movement.GetCurrentStep()].speed.x == 0.5f && movement.steps[movement.GetCurrentStep()].speed.y == -1.0f)
	{
		animation = &downdiagonalleft;
		w = 30 * 3;
		h = 29 * 3;
		collider->SetSize(w, h);
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}

   //Down diagonal right and up diagonal left
	if (movement.steps[movement.GetCurrentStep()].speed.x == -0.5f && movement.steps[movement.GetCurrentStep()].speed.y == -1.0f)
	{
		animation = &downdiagonalright;
		w = 30 * 3;
		h = 28 * 3;
		collider->SetSize(w, h);
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	
	
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 3.0f)
	{
		animation = &downdiagonalright;
		w = 30 * 3;
		h = 28 * 3;
		collider->SetSize(w, h);
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}

	// Neutral diagonal up right and neutral diagonal down left
	if (movement.steps[movement.GetCurrentStep()].speed.x == 1.0f && movement.steps[movement.GetCurrentStep()].speed.y == -1.0f)
	{
		animation = &neutraldiagonalleft;
		w = 31 * 3;
		h = 30 * 3;
		collider->SetSize(w, h);
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == -1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 3.0f)
	{
		animation = &neutraldiagonalleft;
		w = 31 * 3;
		h = 30 * 3;
		collider->SetSize(w, h);
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}



	// Neutral diagonal down left and neutral diagonal up right
	if (movement.steps[movement.GetCurrentStep()].speed.x == -1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f)
	{
		animation = &neutraldiagonalright;
		w = 30 * 3;
		h = 28 * 3;
		collider->SetSize(w, h);
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 3.0f)
	{
		animation = &neutraldiagonalright;
		w = 30 * 3;
		h = 28 * 3;
		collider->SetSize(w, h);
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	



	//Animation of the turret
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
	if (se && angle >= 72 && angle <= 90) // Good
	{
		animation1 = &s;
		w1 = 17 * 3;
		h1 = 24 * 3;
		position1.y -= 20;
		position1.x -= (w1 / 2)+10;

	}
	if (se && angle >= 54 && angle <= 72) //Good
	{
		animation1 = &se1;
		w1 = 16 * 3;
		h1 = 23 * 3;
		position1.y -= 20;
		position1.x -= w1 / 2;
	}
	if (se && angle >= 36 && angle <= 54) // Good
	{
		animation1 = &se2;
		w1 = 21 * 3;
		h1 = 20 * 3;
		position1.y -= 20;
		position1.x -= w1 / 2 - 10;
	}
	
	if (se && angle >= 18 && angle <= 36) //Good
	{
		animation1 = &se3;
		w1 = 26 * 3;
		h1 = 18 * 3;
		position1.y -= 20;
		position1.x -= w1 / 3 ;
	}
	
	if (se && angle >= 0 && angle <= 18) // Good
	{
		animation1 = &e;
		w1 = 27 * 3;
		h1 = 13 * 3;
		position1.y -= h1 / 2;
		position1.x -= 20;
	}

	// East to North
	if (ne && angle >= 0 && angle <= 18) //Good
	{
		animation1 = &e;
		w1 = 27 * 3;
		h1 = 13 * 3;
		position1.y -= h1/2;
		position1.x -= 20;
	}
	if (ne && angle >= 18 && angle <= 36) // Good
	{
		animation1 = &ne1;
		w1 = 25 * 3;
		h1 = 18 * 3;
		position1.y -= (h1 / 2)+10;
		position1.x -= 20;
	}
	if (ne && angle >= 36 && angle <= 54) //Good
	{
		animation1 = &ne2;
		w1 = 20 * 3;
		h1 = 21 * 3;
		position1.y -=( h1 / 2) + 15;
		position1.x -= 20;
	}
	if (ne && angle >= 54 && angle <= 72) //Good
	{
		animation1 = &ne3;
		w1 = 15 * 3;
		h1 = 24 * 3;
		position1.y -= h1 / 2 + 20;
		position1.x -= 20;
	}
	if (ne && angle >= 72 && angle <= 90) //Good
	{
		animation1 = &n;
		w1 = 15 * 3;
		h1 = 26 * 3;
		position1.y -= h1-20;
		position1.x -= w1 / 2;
	}

	// North to West
	if (nw && angle >= 72 && angle <= 90) //Good
	{
		animation1 = &n;
		w1 = 15 * 3;
		h1 = 26 * 3;
		position1.y -= h1 - 20;
		position1.x -= w1 / 2;
	}
	if (nw && angle >= 54 && angle <= 72) // Good
	{
		animation1 = &nw1;
		w1 = 16 * 3;
		h1 = 24 * 3;
		position1.y -= h1 - 20;
		position1.x -= w1 / 2 +10;
	}
	if (nw && angle >= 36 && angle <= 54) //Good
	{
		animation1 = &nw2;
		w1 = 21 * 3;
		h1 = 20 * 3;
		position1.y -= h1 - 15;
		position1.x -= w1 / 2 +10;
	}
	if (nw && angle >= 18 && angle <= 36) //Good
	{
		animation1 = &nw3;
		w1 = 25 * 3;
		h1 = 17 * 3;
		position1.y -= h1 - 20;
		position1.x -= w1 / 2 + 10;
	}
	if (nw && angle >= 0 && angle <= 18) // Good
	{
		animation1 = &w11;
		w1 = 27 * 3;
		h1 = 14 * 3;
		position1.y -= 25;
		position1.x -= (w/2) + 10;
	}

	// West to South
	if (sw && angle >= 0 && angle <= 18) //Good
	{
		animation1 = &w11;
		w1 = 27 * 3;
		h1 = 14 * 3;
		position1.y -= 25;
		position1.x -= (w/2) + 10;
	}
	if (sw && angle >= 18 && angle <= 36) // Good
	{
		animation1 = &sw1;
		w1 = 24 * 3;
		h1 = 16 * 3;
		position1.y -= 20;
		position1.x -= (w/2) + 5;
	}
	if (sw && angle >= 36 && angle <= 54) //Good
	{
		animation1 = &sw2;
		w1 = 21 * 3;
		h1 = 20 * 3;
		position1.y -= 20;
		position1.x -= (w/2);
	}
	
	if (sw && angle >= 54 && angle <= 72) //Good
	{
		animation1 = &sw3;
		w1 = 14 * 3;
		h1 = 23 * 3;
		position1.y -= 25;
		position1.x -= (w/2)- 15;
	}
	if (sw && angle >= 72 && angle <= 90) //Good
	{
		animation1 = &s;
		w1 = 17 * 3;
		h1 = 24 * 3;
		position1.y -= 20;
		position1.x -= (w1 / 2) + 10;
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
		App->particles->AddParticle(App->particles->enemyshot, position.x+ w/2, position.y +h/2, COLLIDER_ENEMY_SHOT, 0, distance.x * 0.03, distance.y * 0.03); 

		shooting = true;
	}
}
