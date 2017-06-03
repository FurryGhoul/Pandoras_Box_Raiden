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
	downup.PushBack({ 3, 4, 31, 29 });
	downup.PushBack({ 275, 4, 31, 29 });
	downup.PushBack({ 547, 4, 31, 29 });
	downup.speed = 0.5f;
	downup.loop = true;
	hitdownup.PushBack({ 4, 95, 31, 29 });

	downdiagonalright.PushBack({ 37, 4, 31, 29 });
	downdiagonalright.PushBack({ 309, 4, 31, 29 });
	downdiagonalright.PushBack({ 581, 4, 31, 29 });
	downdiagonalright.speed = 0.5f;
	downdiagonalright.loop = true;
	hitdowndiagonalright.PushBack({ 38, 95,31,29 });

	neutraldiagonalright.PushBack({ 71, 4, 31, 29 });
	neutraldiagonalright.PushBack({ 343, 4, 31, 29 });
	neutraldiagonalright.PushBack({ 615, 4, 31, 29 });
	neutraldiagonalright.speed = 0.5f;
	neutraldiagonalright.loop = true;
	hitneutraldiagonalright.PushBack({ 72, 95, 31, 29 });

	updiagonalright.PushBack({ 105, 4, 31, 29 });
	updiagonalright.PushBack({ 377, 4, 31, 29 });
	updiagonalright.PushBack({ 649, 4, 31, 29 });
	updiagonalright.speed = 0.5f;
	updiagonalright.loop = true;
	hitupdiagonalright.PushBack({ 106, 95, 31, 29 });

	leftright.PushBack({ 139, 4, 31, 29 });
	leftright.PushBack({ 411, 4, 31, 29 });
	leftright.PushBack({ 683, 4, 31, 29 });
	leftright.speed = 0.5f;
	leftright.loop = true;
	hitleftright.PushBack({ 140 , 95, 31, 29 });

	downdiagonalleft.PushBack({ 173, 4, 31, 29 });
	downdiagonalleft.PushBack({ 445, 4, 31, 29 });
	downdiagonalleft.PushBack({ 717, 4, 31, 29 });
	downdiagonalleft.speed = 0.5f;
	downdiagonalleft.loop = true;
	hitdowndiagonalleft.PushBack({ 174, 95, 31, 29 });

	neutraldiagonalleft.PushBack({ 207, 4, 31, 29 });
	neutraldiagonalleft.PushBack({ 479, 4, 31, 29 });
	neutraldiagonalleft.PushBack({ 751, 4, 31, 29 });
	neutraldiagonalleft.speed = 0.5f;
	neutraldiagonalleft.loop = true;
	hitneutraldiagonalleft.PushBack({ 208, 95, 31, 29 });

	updiagonalleft.PushBack({ 241, 4, 31, 29 });
	updiagonalleft.PushBack({ 513, 4, 31, 29 });
	updiagonalleft.PushBack({ 785, 4, 31, 29 });
	updiagonalleft.speed = 0.5f;
	updiagonalleft.loop = true;
	hitupdiagonalleft.PushBack({ 242, 95, 31, 29 });

	_downup.PushBack({ 3, 4, 31, 29 });

	_downdiagonalright.PushBack({ 37, 4, 31, 29 });

	_neutraldiagonalright.PushBack({ 71, 4,31, 29 });

	_updiagonalright.PushBack({ 105, 4, 31, 29 });

	_leftright.PushBack({ 139 , 4, 31, 29 });

	_downdiagonalleft.PushBack({ 173, 4, 31, 29 });

	_neutraldiagonalleft.PushBack({ 207, 4, 31, 29 });

	_updiagonalleft.PushBack({ 241, 4, 31, 29 });

	//Turret animations
	noturret.PushBack({ 1, 1, 1, 1 });

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


	original_pos.x = x;
	original_pos.y = -100;

	//Paths (there should be more than one path and an integer to select what path to use
	/*Instructions for pathing the enemies:
	0.0, 4.0 = S
	0.0, -1.0 = N
	-2.0, 1.0 = W
	2.0, 1.0 = E
	-0.5, 1.5 = SW3
	0.5, 0.0 = SE1
	-2.0, 0.5 = NW3
	2.0, 1.5 = SE3
	-0.5, 0.0 = NW1
	0.5, 2.0 =  SE1
	1.0, 0.0 = NE2
	-1.0, 2.0 = SW2
	-1.0, 0.0 = NW2
	1.0, 2.0 = SE2
	-2,0,1.5 = SW1
	0.5,0.0 = NE3
	2.0, 0.5 = NE1
	*/

	//east-stop
	if (path == 0)
	{
		movement.PushBack({ 2.0f, 1.0f }, 300);
		movement.PushBack({ 0.0f, 1.0f }, 1000);
	}
	//1
	if (path == 8)
	{
		original_pos.y = 350;
		movement.PushBack({ 2.0f, 1.0f }, 280);
		movement.PushBack({ 0.0f, 1.0f }, 1000);
	}
	//2
	if (path == 9)
	{
		original_pos.y = 300;
		movement.PushBack({ 2.0f, 1.0f }, 350);
		movement.PushBack({ 0.0f, 1.0f }, 1000);
	}
	//3
	if (path == 10)
	{
		original_pos.y = 400;
		movement.PushBack({ 2.0f, 1.0f }, 120);
		movement.PushBack({ 0.0f, 1.0f }, 1000);
	}
	//east-north-south
	//1
	if (path == 18)
	{
		original_pos.y = 300;
		movement.PushBack({ 2.0f, 1.0f }, 120);
		movement.PushBack({ 2.0f, 0.5f }, 10);
		movement.PushBack({ 1.0f, 0.0f }, 10);
		movement.PushBack({ 0.5f, 0.0f }, 10);
		movement.PushBack({ 0.0f, -1.0f }, 150);
		movement.PushBack({ 0.0f, 4.0f }, 100);
		movement.PushBack({ 0.0f, 1.0f }, 1000);

	}


	//east-south
	//1
	if (path == 11)
	{
		original_pos.y = 200;
		movement.PushBack({ 2.0f, 1.0f }, 140);
		movement.PushBack({ 2.0f, 1.5f }, 10);
		movement.PushBack({ 1.0f, 2.0f }, 10);
		movement.PushBack({ 0.5f, 2.0f }, 10);
		movement.PushBack({ 0.0f, 4.0f }, 1000);
	}
	//2
	if (path == 12)
	{
		original_pos.y = 100;
		movement.PushBack({ 2.0f, 1.0f }, 350);
		movement.PushBack({ 2.0f, 1.5f }, 10);
		movement.PushBack({ 1.0f, 2.0f }, 10);
		movement.PushBack({ 0.5f, 2.0f }, 10);
		movement.PushBack({ 0.0f, 4.0f }, 1000);
	}
	// west-south
	if (path == 13)
	{
		original_pos.y = 200;
		movement.PushBack({ -2.0f, 1.0f }, 140);
		movement.PushBack({ -2.0f, 1.5f }, 10);
		movement.PushBack({ -1.0f, 2.0f }, 10);
		movement.PushBack({ -0.5f, 1.5f }, 10);
		movement.PushBack({ 0.0f, 4.0f }, 1000);

	}
	//South-east 2 - south
	//1
	if (path == 14)
	{
		movement.PushBack({ 1.0f, 2.0f }, 80);
		movement.PushBack({ 0.5f, 2.0f }, 10);
		movement.PushBack({ 0.0f, 4.0f }, 1000);
	}
	//2
	if (path == 15)
	{
		movement.PushBack({ 1.0f, 2.0f }, 280);
		movement.PushBack({ 0.5f, 2.0f }, 10);
		movement.PushBack({ 0.0f, 4.0f }, 1000);
	}
	//3
	if (path == 16)
	{
		original_pos.y = 150;
		movement.PushBack({ 1.0f, 2.0f }, 280);
		movement.PushBack({ 0.5f, 2.0f }, 10);
		movement.PushBack({ 0.0f, 4.0f }, 1000);
	}
	//4
	if (path == 17)
	{
		original_pos.y = 300;
		movement.PushBack({ 1.0f, 2.0f }, 280);
		movement.PushBack({ 0.5f, 2.0f }, 10);
		movement.PushBack({ 0.0f, 4.0f }, 1000);
	}

	//south-west 2- south 
	//1
	if (path == 19)
	{
		original_pos.y = 0;
		movement.PushBack({ -1.0f, 2.0f }, 330);
		movement.PushBack({ -0.5f, 1.5f }, 10);
		movement.PushBack({ 0.0f, 4.0f }, 1000);
	}
	//2
	if (path == 20)
	{
		original_pos.y = 100;
		movement.PushBack({ -1.0f, 2.0f }, 330);
		movement.PushBack({ -0.5f, 1.5f }, 10);
		movement.PushBack({ 0.0f, 4.0f }, 1000);
	}
	//South-east 2- east
	//1
	if (path == 21)
	{
		movement.PushBack({ 1.0f, 2.0f }, 80);
		movement.PushBack({ 2.0f, 1.5f }, 10);
		movement.PushBack({ 2.0f, 1.0f }, 1000);
	}
	//2
	if (path == 22)
	{
		movement.PushBack({ 1.0f, 2.0f }, 140);
		movement.PushBack({ 2.0f, 1.5f }, 10);
		movement.PushBack({ 2.0f, 1.0f }, 1000);
	}
	//3
	if (path == 23)
	{
		movement.PushBack({ 1.0f, 2.0f }, 200);
		movement.PushBack({ 2.0f, 1.5f }, 10);
		movement.PushBack({ 2.0f, 1.0f }, 1000);
	}
	//4
	if (path == 24)
	{
		movement.PushBack({ 1.0f, 2.0f }, 260);
		movement.PushBack({ 2.0f, 1.5f }, 10);
		movement.PushBack({ 2.0f, 1.0f }, 1000);
	}
	//South east 2
	if (path == 25)
	{
		original_pos.y = -100;
		movement.PushBack({ 1.0f, 2.0f }, 1000);
	}
	if (path == 26)
	{
		original_pos.y = 100;
		movement.PushBack({ 1.0f, 2.0f }, 1000);
	}
	if (path == 27)
	{
		original_pos.y = 300;
		movement.PushBack({ 1.0f, 2.0f }, 1000);
	}

	//south- South east 2
	//1
	if (path == 28)
	{
		movement.PushBack({ 0.0f, 4.0f }, 160);
		movement.PushBack({ 0.5f, 2.0f }, 10);
		movement.PushBack({ 1.0f, 2.0f }, 1000);
	}
	//2
	if (path == 29)
	{
		movement.PushBack({ 0.0f, 4.0f }, 210);
		movement.PushBack({ 0.5f, 2.0f }, 10);
		movement.PushBack({ 1.0f, 2.0f }, 1000);
	}


	// south
	if (path == 1)
	{
		movement.PushBack({ 0.0f, 4.0f }, 300);
	}

	//South east 3 - east
	//1
	if (path == 2)
	{
		movement.PushBack({ 2.0f, 1.0f }, 1);
		movement.PushBack({ 0.0f, 1.0f }, 100);
		movement.PushBack({ 2.0f, 1.0f }, 1000);
	}
	//2
	if (path == 3)
	{
		movement.PushBack({ 2.0f, 1.0f }, 1);
		movement.PushBack({ 0.0f, 1.0f }, 100);
		movement.PushBack({ 2.0f, 1.5f }, 20);
		movement.PushBack({ 2.0f, 1.0f }, 1000);
	}
	//3
	if (path == 4)
	{
		movement.PushBack({ 2.0f, 1.0f }, 1);
		movement.PushBack({ 0.0f, 1.0f }, 100);
		movement.PushBack({ 2.0f, 1.5f }, 90);
		movement.PushBack({ 2.0f, 1.0f }, 1000);
	}

	//North-west 1- west
	//1
	if (path == 5)
	{
		movement.PushBack({ 2.0f, 1.0f }, 1);
		movement.PushBack({ 0.0f, 1.0f }, 150);
		movement.PushBack({ -2.0f, 0.5f }, 85);
		movement.PushBack({ -2.0f, 1.0f }, 1000);
	}
	//2
	if (path == 6)
	{
		movement.PushBack({ 2.0f, 1.0f }, 1);
		movement.PushBack({ 0.0f, 1.0f }, 100);
		movement.PushBack({ -2.0f, 0.5f }, 35);
		movement.PushBack({ -2.0f, 1.0f }, 1000);
	}
	//3
	if (path == 7)
	{
		movement.PushBack({ 2.0f, 1.0f }, 1);
		movement.PushBack({ 0.0f, 1.0f }, 50);
		movement.PushBack({ -2.0f,0.5f }, 10);
		movement.PushBack({ -2.0f, 1.0f }, 1000);
	}
	//east - north - west
	if (path == 30)
	{
		original_pos.y = 500;
		movement.PushBack({ 2.0f, 1.0f }, 150);
		movement.PushBack({ 2.0f, 0.5f }, 10);
		movement.PushBack({ 1.0f, 0.0f }, 10);
		movement.PushBack({ 0.5f, 0.0f }, 10);
		movement.PushBack({ 0.0f, 0.0f }, 600);
		movement.PushBack({ -0.5f, 0.0f }, 10);
		movement.PushBack({ -1.0f, 0.0f }, 10);
		movement.PushBack({ -2.0f, 0.5f }, 10);
		movement.PushBack({ -2.0f, 1.0f }, 1000);
	}
	//east- north east 2- stop
	if (path == 31)
	{
		original_pos.y = 600;
		movement.PushBack({ 2.0f, 1.0f }, 150);
		movement.PushBack({ 2.0f, 0.5f }, 10);
		movement.PushBack({ 1.0f, 0.0f }, 10);
		movement.PushBack({ 0.5f, 0.0f }, 10);
		movement.PushBack({ 0.0f, 0.0f }, 500);
		movement.PushBack({ 0.5f, 0.0f }, 10);
		movement.PushBack({ 1.0f, 0.0f }, 10);
		movement.PushBack({ 0.0f, 1.0f }, 1000);

	}
	//West/East stoped
	if (path == 32)
	{
		original_pos.y = -100;
		movement.PushBack({ 2.0f, 1.0f }, 1);
		movement.PushBack({ 0.0f, 1.0f }, 1000);
	}
	//South- SW2- stop
	if (path == 33)
	{
		original_pos.y = -100;
		movement.PushBack({ 0.0f, 4.0f }, 80);
		movement.PushBack({ -0.5f, 1.5f }, 10);
		movement.PushBack({ -1.0f, 2.0f }, 40);
		movement.PushBack({ 0.0f, 1.0f }, 1000);
	}
	tank = true;
	collider = App->collision->AddCollider({ 0, 0, 31 * 3 - 5, 29 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->genemies);
	animation = &updiagonalleft;
}


void Tank::MoveShoot()
{
	// Calculation between tank and player and movement of the tank

	position = original_pos + movement.GetCurrentPosition();

	position.x += left_right_mod;

	if (sqrtf((distance.y = App->player->position.y - position.y)*(distance.y = App->player->position.y - position.y) + (distance.x = App->player->position.x - position.x)* (distance.x = App->player->position.x - position.x))
		< sqrtf((distance.y = App->player2->position.y - position.y)*(distance.y = App->player2->position.y - position.y) + (distance.x = App->player2->position.x - position.x)* (distance.x = App->player2->position.x - position.x)))
	{
		distance.y = App->player->position.y - position.y;
		distance.x = App->player->position.x - position.x;
	}

	else
	{
		distance.y = App->player2->position.y - position.y;
		distance.x = App->player2->position.x - position.x;
	}

	// Animation of the tank	

	w = 31 * 3;
	h = 29 * 3;



	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == -1.0f) //North
	{
		animation = &downup;
		if (ishit == true)
		{
			animation = &hitdownup;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2 - 5;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f) //North
	{
		animation = &downup;
		if (ishit == true)
		{
			animation = &hitdownup;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2 - 5;
	}


	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 4.0f)//South
	{
		animation = &downup;
		if (ishit == true)
		{
			animation = &hitdownup;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2 - 5;
	}

	if (movement.steps[movement.GetCurrentStep()].speed.x == -2.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f) //West
	{
		animation = &leftright;
		if (ishit == true)
		{
			animation = &hitleftright;
			ishit = false;
		}
		h = 35 * 3;
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}


	if (movement.steps[movement.GetCurrentStep()].speed.x == 2.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f) //East
	{
		animation = &leftright;
		if (ishit == true)
		{
			animation = &hitleftright;
			ishit = false;
		}
		h = 35 * 3;
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}



	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f) //If tanks stop they get the last animation that was done
	{
		if (animation == &leftright || animation == &hitleftright || animation == &_leftright)
		{
			animation = &_leftright;
			if (ishit == true)
			{
				animation = &hitleftright;
				ishit = false;
			}
			h = 35 * 3;
			position1.x = position.x + w / 2;
			position1.y = position.y + h / 2;
		}
		if (animation == &downup || animation == &hitdownup || animation == &_downup)
		{
			animation = &_downup;
			if (ishit == true)
			{
				animation = &hitdownup;
				ishit = false;
			}
			position1.x = position.x + w / 2;
			position1.y = position.y + h / 2 - 5;
		}
		if (animation == &neutraldiagonalleft || animation == &hitneutraldiagonalleft || animation == &_neutraldiagonalleft)
		{
			animation = &_neutraldiagonalleft;
			if (ishit == true)
			{
				animation = &hitneutraldiagonalleft;
				ishit = false;
			}
			position1.x = position.x + w / 2;
			position1.y = position.y + h / 2;
		}
		if (animation == &neutraldiagonalright || animation == &hitneutraldiagonalright || animation == &_neutraldiagonalright)
		{
			animation = &_neutraldiagonalright;
			if (ishit == true)
			{
				animation = &hitneutraldiagonalright;
				ishit = false;
			}
			position1.x = position.x + w / 2;
			position1.y = position.y + h / 2;
		}
		if (animation == &neutraldiagonalright || animation == &hitneutraldiagonalright || animation == &_neutraldiagonalright)
		{
			animation = &_neutraldiagonalright;
			if (ishit == true)
			{
				animation = &hitneutraldiagonalright;
				ishit = false;
			}
			position1.x = position.x + w / 2;
			position1.y = position.y + h / 2;
		}
	}



	if (movement.steps[movement.GetCurrentStep()].speed.x == -0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 1.5f) // SW3
	{
		animation = &updiagonalleft;
		if (ishit == true)
		{
			animation = &hitupdiagonalleft;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}

	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f) //NE3
	{
		animation = &updiagonalleft;
		if (ishit == true)
		{
			animation = &hitupdiagonalleft;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}



	if (movement.steps[movement.GetCurrentStep()].speed.x == -2.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.5f) //NW3
	{
		animation = &updiagonalright;
		if (ishit == true)
		{
			animation = &hitupdiagonalright;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}

	if (movement.steps[movement.GetCurrentStep()].speed.x == 2.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.5f) //SE3
	{
		animation = &updiagonalright;
		if (ishit == true)
		{
			animation = &hitupdiagonalright;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}


	if (movement.steps[movement.GetCurrentStep()].speed.x == -0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f) //NW1
	{
		animation = &downdiagonalright;
		if (ishit == true)
		{
			animation = &hitdowndiagonalright;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}


	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f) //SE1
	{
		animation = &downdiagonalright;
		if (ishit == true)
		{
			animation = &hitdowndiagonalright;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}


	if (movement.steps[movement.GetCurrentStep()].speed.x == 1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f) //NE2
	{
		animation = &neutraldiagonalleft;
		if (ishit == true)
		{
			animation = &hitneutraldiagonalleft;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == -1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f) //SW2
	{
		animation = &neutraldiagonalleft;
		if (ishit == true)
		{
			animation = &hitneutraldiagonalleft;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}




	if (movement.steps[movement.GetCurrentStep()].speed.x == -1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f) // NW2
	{
		animation = &neutraldiagonalright;
		if (ishit == true)
		{
			animation = &hitneutraldiagonalright;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f) //SE2
	{
		animation = &neutraldiagonalright;
		if (ishit == true)
		{
			animation = &hitneutraldiagonalright;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == -2.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.5f) //SW1
	{
		animation = &downdiagonalleft; //CHANGE
		if (ishit == true)
		{
			animation = &hitdowndiagonalleft;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 2.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.5f) //NE1
	{
		animation = &downdiagonalleft; //CHANGE
		if (ishit == true)
		{
			animation = &hitdowndiagonalleft;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}

	if (hp < 2)
	{
		turretalive = false;
		animation1 = &noturret;
	}

	if (turretalive == true)
	{

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
			if (ishit2 == true)
			{
				animation1 = &hits;
				ishit2 = false;
			}
		}
		if (se && angle >= 54 && angle <= 72) //Good
		{
			animation1 = &se1;
			if (ishit2 == true)
			{
				animation1 = &hitse1;
				ishit2 = false;
			}
		}
		if (se && angle >= 36 && angle <= 54) // Good
		{
			animation1 = &se2;
			if (ishit2 == true)
			{
				animation1 = &hitse2;
				ishit2 = false;
			}
		}

		if (se && angle >= 18 && angle <= 36) //Good
		{
			animation1 = &se3;
			if (ishit2 == true)
			{
				animation1 = &hitse3;
				ishit2 = false;
			}
		}

		if (se && angle >= 0 && angle <= 18) // Good
		{
			animation1 = &e;
			if (ishit2 == true)
			{
				animation1 = &hite;
				ishit2 = false;
			}
		}

		// East to North
		if (ne && angle >= 0 && angle <= 18) //Good
		{
			animation1 = &e;
			if (ishit2 == true)
			{
				animation1 = &hite;
				ishit2 = false;
			}
		}
		if (ne && angle >= 18 && angle <= 36) // Good
		{
			animation1 = &ne1;
			if (ishit2 == true)
			{
				animation1 = &hitne1;
				ishit2 = false;
			}
		}
		if (ne && angle >= 36 && angle <= 54) //Good
		{
			animation1 = &ne2;
			if (ishit2 == true)
			{
				animation1 = &hitne2;
				ishit2 = false;
			}
		}
		if (ne && angle >= 54 && angle <= 72) //Good
		{
			animation1 = &ne3;
			if (ishit2 == true)
			{
				animation1 = &hitne3;
				ishit2 = false;
			}
		}
		if (ne && angle >= 72 && angle <= 90) //Good
		{
			animation1 = &n;
			if (ishit2 == true)
			{
				animation1 = &hitn;
				ishit2 = false;
			}
		}

		// North to West
		if (nw && angle >= 72 && angle <= 90) //Good
		{
			animation1 = &n;
			if (ishit2 == true)
			{
				animation1 = &hitn;
				ishit2 = false;
			}
		}
		if (nw && angle >= 54 && angle <= 72) // Good
		{
			animation1 = &nw1;
			if (ishit2 == true)
			{
				animation1 = &hitnw1;
				ishit2 = false;
			}
		}
		if (nw && angle >= 36 && angle <= 54) //Good
		{
			animation1 = &nw2;
			if (ishit2 == true)
			{
				animation1 = &hitnw2;
				ishit2 = false;
			}
		}
		if (nw && angle >= 18 && angle <= 36) //Good
		{
			animation1 = &nw3;
			if (ishit2 == true)
			{
				animation1 = &hitnw3;
				ishit2 = false;
			}
		}
		if (nw && angle >= 0 && angle <= 18) // Good
		{
			animation1 = &w11;
			if (ishit2 == true)
			{
				animation1 = &hitw11;
				ishit2 = false;
			}
		}

		// West to South
		if (sw && angle >= 0 && angle <= 18) //Good
		{
			animation1 = &w11;
			if (ishit2 == true)
			{
				animation1 = &hitw11;
				ishit2 = false;
			}
		}
		if (sw && angle >= 18 && angle <= 36) // Good
		{
			animation1 = &sw1;
			if (ishit2 == true)
			{
				animation1 = &hitsw1;
				ishit2 = false;
			}
		}
		if (sw && angle >= 36 && angle <= 54) //Good
		{
			animation1 = &sw2;
			if (ishit2 == true)
			{
				animation1 = &hitsw2;
				ishit2 = false;
			}
		}

		if (sw && angle >= 54 && angle <= 72) //Good
		{
			animation1 = &sw3;
			if (ishit2 == true)
			{
				animation1 = &hitsw3;
				ishit2 = false;
			}
		}
		if (sw && angle >= 72 && angle <= 90) //Good
		{
			animation1 = &s;
			if (ishit2 == true)
			{
				animation1 = &hits;
				ishit2 = false;
			}
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
				if (App->player->position.y < (position.y))
				{
					distance.y *= -1;
				}
				if (App->player->position.x < (position.x))
				{
					distance.x *= -1;
				}
				App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
		}
	}
}