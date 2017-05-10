#include "Tank.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"
#define PI 3.14159265

Tank::Tank(int x, int y, int path) : Enemy(x, y)
{
	hp = 3;
	points = 130;

	spritesheet = 2;
	animations = 2;
	// Tank animations
	downup.PushBack({ 3, 4, 31, 29 }); // done

	downdiagonalright.PushBack({ 37, 4, 31, 29 }); // done

	neutraldiagonalright.PushBack({ 71, 4,31, 29 }); //in proces

	updiagonalright.PushBack({ 105, 4, 31, 29 }); // Not in usage

	leftright.PushBack({ 139 , 4, 31, 29 }); // done

	downdiagonalleft.PushBack({ 173, 4, 31, 29 }); // done

	neutraldiagonalleft.PushBack({ 207, 4, 31, 29 }); // done

	updiagonalleft.PushBack({ 241, 4, 31, 29 }); // Not in usage

	//Turret animations
	s.PushBack({ 3, 44, 38, 34 });
	
	se1.PushBack({ 44, 44, 38, 34 });

	se2.PushBack({ 85, 44, 38, 34 });

	se3.PushBack({ 126, 44, 38, 34 });

	e.PushBack({ 167, 44, 38, 34 });

	ne1.PushBack({ 208, 44, 38, 34 });

	ne2.PushBack({ 249, 44, 38, 34 });

	ne3.PushBack({ 290, 44, 38, 34 });

    n.PushBack({ 331, 44, 38, 34 });

	nw1.PushBack({ 372, 44, 38, 34 });

	nw2.PushBack({ 413, 44, 38, 34 });

	nw3.PushBack({ 454, 44, 38, 34 });

	w11.PushBack({ 495, 44, 38, 34 });

	sw1.PushBack({ 536, 44, 38, 34 });

	sw2.PushBack({ 577, 44, 38, 34 });

	sw3.PushBack({ 618, 44, 38, 34 });

	
	original_pos.x = x;
	original_pos.y = -50;

	//Paths (there should be more than one path and an integer to select what path to use
	/*Instructions for pathing the enemies:  
	0.0, 4.0 = down
	0.0, 0.0 = up
	-0.5, 2.0 = left
	0.5, 2.0 = right
	-0.5, 3.0 = down diagonal left
	-0.5, -1.0 = up diagonal right
	-0.5, -1.0 = up diagonal left
	0.5, 3.0 =  down diagonal right
	1.0,-1.0 = Neutral diagonal up right
	-1.0, 3.0 =Neutral diagonal down left
	-1.0, 1.0 = Neutral diagonal up left
	1.0, 3.0 = Neutral diagonal down right
	*/
	if (path == 0)
	{
		movement.PushBack({ 0.0f, 4.0f }, 100);
		movement.PushBack({ -1.0f, 1.0f }, 100);
		movement.PushBack({ 1.0f, 3.0f }, 100);
	}

	if (path == 1)
	{
		movement.PushBack({ 0.0f, 4.0f }, 30);
		movement.PushBack({ 0.5f, 3.0f }, 30);
		movement.PushBack({ 0.5f, 2.0f }, 70);
		movement.PushBack({ -1.0f, 3.0f }, 100);
	}

	if (path == 2)
	{
		movement.PushBack({ 0.0f, 4.0f }, 100);
		movement.PushBack({ -0.5f, -1.0f }, 100);
 		movement.PushBack({ 0.0f, 4.0f }, 100);
	}

	tank = true;
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
	
	w = 31 * 3;
	h = 29 * 3;
	collider->SetSize(w, h);

	// Down and up
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f)
	{
		animation = &downup;

	   position1.x = position.x + w / 2;
	   position1.y = position.y + h / 2 - 5;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 4.0f)
	{
		animation = &downup;

		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2 - 5;
	}

	// Left and right
     if (movement.steps[movement.GetCurrentStep()].speed.x == -0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f)
	{ 
	  animation = &leftright;

	 position1.x = position.x + w / 2 + 10;
	 position1.y = position.y + h / 2;
	}


	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f)
	{
		animation = &leftright;

		position1.x = position.x + w / 2 + 10;
		position1.y = position.y + h / 2;
	}

	// Down diagonal left and up diagonal right
	if (movement.steps[movement.GetCurrentStep()].speed.x == -0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 3.0f)
	{ 
	animation = &downdiagonalleft;

	position1.x = position.x + w / 2;
	position1.y = position.y + h / 2;
	}


   if (movement.steps[movement.GetCurrentStep()].speed.x == 0.5f && movement.steps[movement.GetCurrentStep()].speed.y == -1.0f)
	{
		animation = &downdiagonalleft;

		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}

   //Down diagonal right and up diagonal left
	if (movement.steps[movement.GetCurrentStep()].speed.x == -0.5f && movement.steps[movement.GetCurrentStep()].speed.y == -1.0f)
	{
		animation = &downdiagonalright;

		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	
	
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 3.0f)
	{
		animation = &downdiagonalright;

		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}

	// Neutral diagonal up right and neutral diagonal down left
	if (movement.steps[movement.GetCurrentStep()].speed.x == 1.0f && movement.steps[movement.GetCurrentStep()].speed.y == -1.0f)
	{
		animation = &neutraldiagonalleft;

		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == -1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 3.0f)
	{
		animation = &neutraldiagonalleft;

		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}



	// Neutral diagonal down left and neutral diagonal up right
	if (movement.steps[movement.GetCurrentStep()].speed.x == -1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f)
	{
		animation = &neutraldiagonalright;

		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 3.0f)
	{
		animation = &neutraldiagonalright;

		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	



	//Animation of the turret
	param = (fabs(distance.y) / (fabs(distance.x) + 0.1));
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

	w1 = 38 * 3;
	h1 = 34 * 3;
	position1.x -= 19 * 3;
	position1.y -= 17 * 3;

	// South to East
	if (se && angle >= 72 && angle <= 90) // Good
	{
		animation1 = &s;
	}
	if (se && angle >= 54 && angle <= 72) //Good
	{
		animation1 = &se1;
	}
	if (se && angle >= 36 && angle <= 54) // Good
	{
		animation1 = &se2;
	}
	
	if (se && angle >= 18 && angle <= 36) //Good
	{
		animation1 = &se3;
	}
	
	if (se && angle >= 0 && angle <= 18) // Good
	{
		animation1 = &e;
	}

	// East to North
	if (ne && angle >= 0 && angle <= 18) //Good
	{
		animation1 = &e;
	}
	if (ne && angle >= 18 && angle <= 36) // Good
	{
		animation1 = &ne1;
	}
	if (ne && angle >= 36 && angle <= 54) //Good
	{
		animation1 = &ne2;
	}
	if (ne && angle >= 54 && angle <= 72) //Good
	{
		animation1 = &ne3;
	}
	if (ne && angle >= 72 && angle <= 90) //Good
	{
		animation1 = &n;
	}

	// North to West
	if (nw && angle >= 72 && angle <= 90) //Good
	{
		animation1 = &n;
	}
	if (nw && angle >= 54 && angle <= 72) // Good
	{
		animation1 = &nw1;
	}
	if (nw && angle >= 36 && angle <= 54) //Good
	{
		animation1 = &nw2;
	}
	if (nw && angle >= 18 && angle <= 36) //Good
	{
		animation1 = &nw3;
	}
	if (nw && angle >= 0 && angle <= 18) // Good
	{
		animation1 = &w11;
	}

	// West to South
	if (sw && angle >= 0 && angle <= 18) //Good
	{
		animation1 = &w11;
	}
	if (sw && angle >= 18 && angle <= 36) // Good
	{
		animation1 = &sw1;
	}
	if (sw && angle >= 36 && angle <= 54) //Good
	{
		animation1 = &sw2;
	}
	
	if (sw && angle >= 54 && angle <= 72) //Good
	{
		animation1 = &sw3;
	}
	if (sw && angle >= 72 && angle <= 90) //Good
	{
		animation1 = &s;
	}



	distance.x = fabs(distance.x);
	distance.y = fabs(distance.y);
	// Shooting
	time_controll++;
	if (time_controll % 100 == 0)

{ 

	distance.x *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
	distance.y *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));

	if (sqrtf(distance.x*distance.x + distance.y*distance.y) < 500 && position.y <= 760)
	{
        if (App->player->position.y - 22 < (position.y - 22 * 3))
		{
			distance.y *= -1;
		}
		if (App->player->position.x < (position.x + 22))
		{
			distance.x *= -1;
		}
		App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
	}
}
}
