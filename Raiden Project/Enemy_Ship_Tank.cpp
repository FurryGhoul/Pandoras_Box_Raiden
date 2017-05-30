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
	points = 230;
	shiptank = true;

	spritesheet = 2;
	animations = 3;

	// Ship Tank animations	
	up.PushBack({ 10, 359, 23, 30 });
	down.PushBack({ 61, 360, 23, 30 });
	left.PushBack({ 107, 364, 32, 21 });
	right.PushBack({ 152, 364, 32, 21 });

	// Ship Tank hit animations	
	hitup.PushBack({ 10, 395, 23, 30 });
	hitdown.PushBack({ 61, 395, 23, 30 });
	hitleft.PushBack({ 107, 400, 32, 21 });
	hitright.PushBack({ 151, 400, 32, 21 });

	hitup1.PushBack({ 10, 395, 23, 30 });
	hitdown1.PushBack({ 61, 360, 23, 30 });
	hitleft1.PushBack({ 107, 434, 32, 21 });
	hitright1.PushBack({ 151, 434, 32, 21 });

	// Water animation
	waterdown1.PushBack({ 208, 404, 33, 29 });
	waterdown2.PushBack({ 255, 404, 33, 29 });
	waterdown3.PushBack({ 309, 404, 33, 29 });

	waterup1.PushBack({ 208, 364, 33, 29 });
	waterup2.PushBack({ 255, 364, 33, 29 });
	waterup3.PushBack({ 309, 364, 33, 29 }); // Horizontal movement and water effects are not needed in level 2

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


	// Movement
	movement.PushBack({ 0.0f, 2.0f }, 100);
	//movement.PushBack({ 0.0f, 0.0f }, 100);

	original_pos.x = x;
	original_pos.y = -200;

	//tank = true;
	collider = App->collision->AddCollider({ 0, 0, 23 * 3 - 5, 30 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->genemies);
	animation = &up;
}

void Enemy_Ship_Tank::MoveShoot()
{
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


	// Animation of the tank and water	
	w = 23 * 3;
	h = 30 * 3;
	w2 = 33 * 3;
	h2 = 29 * 3;

	collider->SetSize(w, h);

	// Down
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f)
	{
		animation = &down;

		if (ishit == true)
		{
			if (hp > 1)
				animation = &hitdown;
			else
				animation = &hitdown1;

			ishit = false;
		}
		
		if (water == 0)
		{
			animation2 = &waterdown1;
			position2.x = position.x - 16;
			position2.y = position.y - 7;

			if (waterrepeat == 10)
			{
				water++;
				waterrepeat = 0;
			}
			waterrepeat++;
		}
		else if (water == 1)
		{
			animation2 = &waterdown2;
			position2.x = position.x - 16;
			position2.y = position.y - 7;

			if (waterrepeat == 10)
			{
				water++;
				waterrepeat = 0;
			}
			waterrepeat++;
		}
		else if (water == 2)
		{
			animation2 = &waterdown3;
			position2.x = position.x - 12;
			position2.y = position.y - 7;

			if (waterrepeat == 10)
			{
				water = 0;
				waterrepeat = 0;
			}
			waterrepeat++;
		}

		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2 - 5;
	}

	// Up
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == -3.0f)
	{
		animation = &up;

		if (ishit == true)
		{
			if (hp > 1)
				animation = &hitup;
			else
				animation = &hitup1;

			ishit = false;
		}

		if (water == 0)
		{
			animation2 = &waterdown1;
			water++;
		}
		else if (water == 1)
		{
			animation2 = &waterdown2;
			water++;
		}
		else if (water == 2)
		{
			animation2 = &waterdown3;
			water = 0;
		}


		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2 - 5;
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