#include "Enemy_Train_Coach.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleGroundEnemies.h"


Enemy_Train_Coach::Enemy_Train_Coach(int x, int y, int path) : Enemy(x, y)
{
	hp = 5;
	points = 480;	
	spritesheet = 8;
	animations = 2;
	traincoach = true;

	// Anmiation pushback's

	// Idle
	horizontal.PushBack({ 56, 16, 32, 23 });
	diagonal.PushBack({ 99, 9, 30, 30 });
	
	hithorizontal.PushBack({ 56, 55, 32, 23 });
	hitdiagonal.PushBack({ 99, 48, 30, 30 });

	// Turret
	noturret.PushBack({ 1, 1, 1, 1 });

	horizontalturret1.PushBack({ 186, 4, 16, 16 });
	horizontalturret2.PushBack({ 203, 4, 16, 16 });
	horizontalturret3.PushBack({ 220, 4, 16, 16 });
	horizontalturret4.PushBack({ 237, 4, 16, 16 });
	horizontalturret5.PushBack({ 254, 4, 16, 16 });
	horizontalturret6.PushBack({ 271, 4, 16, 16 });
	horizontalturret7.PushBack({ 288, 4, 16, 16 });
	horizontalturret8.PushBack({ 305, 4, 16, 16 });

	diagonalturret1.PushBack({ 186, 24, 16, 16 });
	diagonalturret2.PushBack({ 203, 24, 16, 16 });
	diagonalturret3.PushBack({ 220, 24, 16, 16 });
	diagonalturret4.PushBack({ 237, 24, 16, 16 });
	diagonalturret5.PushBack({ 254, 24, 16, 16 });
	diagonalturret6.PushBack({ 271, 24, 16, 16 });
	diagonalturret7.PushBack({ 288, 24, 16, 16 });
	diagonalturret8.PushBack({ 305, 24, 16, 16 });

	hithorizontalturret1.PushBack({ 186, 44, 16, 16 });
	hithorizontalturret2.PushBack({ 203, 44, 16, 16 });
	hithorizontalturret3.PushBack({ 220, 44, 16, 16 });
	hithorizontalturret4.PushBack({ 237, 44, 16, 16 });
	hithorizontalturret5.PushBack({ 254, 44, 16, 16 });
	hithorizontalturret6.PushBack({ 271, 44, 16, 16 });
	hithorizontalturret7.PushBack({ 288, 44, 16, 16 });
	hithorizontalturret8.PushBack({ 305, 44, 16, 16 });

	hitdiagonalturret1.PushBack({ 186, 64, 16, 16 });
	hitdiagonalturret2.PushBack({ 203, 64, 16, 16 });
	hitdiagonalturret3.PushBack({ 220, 64, 16, 16 });
	hitdiagonalturret4.PushBack({ 237, 64, 16, 16 });
	hitdiagonalturret5.PushBack({ 254, 64, 16, 16 });
	hitdiagonalturret6.PushBack({ 271, 64, 16, 16 });
	hitdiagonalturret7.PushBack({ 288, 64, 16, 16 });
	hitdiagonalturret8.PushBack({ 305, 64, 16, 16 });


	// Paths
	if (path == 0)
	{
		movement.PushBack({ -2.3f, 1.5f }, 1000);
		movement.loop = false;

		collider = App->collision->AddCollider({ 0, 0, 32 * 3, 23 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->genemies);
		original_pos.y = 50;
	}
	if (path == 1)
	{
		movement.PushBack({ -1.5f, -0.1f }, 1000);
		movement.loop = false;

		collider = App->collision->AddCollider({ 0, 0, 30 * 3, 30 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->genemies);
		original_pos.y = 404;
	}
	if (path == 2)
	{
		movement.PushBack({ -1.5f, -0.1f }, 1000);
		movement.loop = false;

		collider = App->collision->AddCollider({ 0, 0, 30 * 3, 30 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->genemies);
		original_pos.y = 468;
	}
	
	original_pos.x = x;
}


void Enemy_Train_Coach::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
	position.x += left_right_mod;
	++shoot_time;

	if (sqrtf((distance.y = App->player->position.y - position.y)*(distance.y = App->player->position.y - position.y) + (distance.x = App->player->position.x - position.x)* (distance.x = App->player->position.x - position.x))
		< sqrtf((distance.y = App->player2->position.y - position.y)*(distance.y = App->player2->position.y - position.y) + (distance.x = App->player2->position.x - position.x)* (distance.x = App->player2->position.x - position.x)))
	{
		distance.y = App->player->position.y - position.y;
		distance.x = App->player->position.x - position.x;
		distance1.y = App->player->position.y - position.y;
		distance1.x = App->player->position.x - position.x + 100;
	}
	else
	{
		distance.y = App->player2->position.y - position.y;
		distance.x = App->player2->position.x - position.x;
		distance1.y = App->player2->position.y - position.y;
		distance1.x = App->player2->position.x - position.x + 100;
	}

	// Animation
	animation = &horizontal;
	w = 32 * 3;
	h = 23 * 3;

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

		w = 32 * 3;
		h = 23 * 3;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == -1.5f && movement.steps[movement.GetCurrentStep()].speed.y == -0.1f)
	{
		animation = &diagonal;

		if (ishit == true)
		{
			animation = &hitdiagonal;
			ishit = false;
		}

		w = 30 * 3;
		h = 30 * 3;
	}

	// Turret animation
	animation1 = &noturret;
	w1 = 16 * 3;
	h1 = 16 * 3;
	position1.x = position.x + 25;
	position1.y = position.y + 8;


	if (movement.steps[movement.GetCurrentStep()].speed.y == 1.5f) // Horizontal path
	{
		if (shotphase <= 20) // Phase 0
		{
			animation1 = &noturret;
			shotphase++;
		}
		else if (shotphase <= 25 || shotphase > 90) // Phase 1
		{
			animation1 = &horizontalturret4;

			if (ishit == true)
			{
				animation = &hithorizontalturret4;				
				ishit = false;
			}
			shotphase++;
		}
		else if (shotphase <= 30 || shotphase > 85) // Phase 2
		{
			animation1 = &horizontalturret3;

			if (ishit == true)
			{
				animation = &hithorizontalturret3;
				ishit = false;
			}
			shotphase++;
		}
		else if (shotphase <= 35 || shotphase > 80) // Phase 3
		{
			animation1 = &horizontalturret2;

			if (ishit == true)
			{
				animation = &hithorizontalturret2;
				ishit = false;
			}
			shotphase++;			
		}
		else if (shotphase <= 40 || shotphase > 75) // Phase 4
		{
			animation1 = &horizontalturret1;

			if (ishit == true)
			{
				animation = &hithorizontalturret1;
				ishit = false;
			}
			shotphase++;
		}
		else if (shotphase <= 45 || shotphase > 70) // Phase 5
		{
			animation1 = &horizontalturret5;

			if (ishit == true)
			{
				animation = &hithorizontalturret5;
				ishit = false;
			}
			shotphase++;
		}
		else if (shotphase <= 50 || shotphase > 65) // Phase 6
		{
			animation1 = &horizontalturret6;

			if (ishit == true)
			{
				animation = &hithorizontalturret6;
				ishit = false;
			}
			shotphase++;
		}
		else if (shotphase <= 55 || shotphase > 60) // Phase 7
		{
			animation1 = &horizontalturret7;

			if (ishit == true)
			{
				animation = &hithorizontalturret7;
				ishit = false;
			}
			shotphase++;
		}
		else if (shotphase <= 60) // Phase 8
		{
			animation1 = &horizontalturret8;

			if (ishit == true)
			{
				animation = &hithorizontalturret8;
				ishit = false;
			}
			shotphase++;
		}
		
		if (shotphase == 95)
		{
			shotphase = 0;
		}
		if (shotphase == 63) //Only in this phase the train shoots
		{
			shoot = true;
		}
	}

	else if (movement.steps[movement.GetCurrentStep()].speed.y == -0.1f) // Diagonal path
	{
		position1.x = position.x + 24;
		position1.y = position.y + 22;

		if (shotphase <= 20) // Phase 0
		{
			animation1 = &noturret;
			shotphase++;
		}
		else if (shotphase <= 25 || shotphase > 90) // Phase 1
		{
			animation1 = &diagonalturret4;

			if (ishit == true)
			{
				animation = &hitdiagonalturret4;
				ishit = false;
			}
			shotphase++;
		}
		else if (shotphase <= 30 || shotphase > 85) // Phase 2
		{
			animation1 = &diagonalturret3;

			if (ishit == true)
			{
				animation = &hitdiagonalturret3;
				ishit = false;
			}
			shotphase++;
		}
		else if (shotphase <= 35 || shotphase > 80) // Phase 3
		{
			animation1 = &diagonalturret2;

			if (ishit == true)
			{
				animation = &hitdiagonalturret2;
				ishit = false;
			}
			shotphase++;
		}
		else if (shotphase <= 40 || shotphase > 75) // Phase 4
		{
			animation1 = &diagonalturret1;

			if (ishit == true)
			{
				animation = &hitdiagonalturret1;
				ishit = false;
			}
			shotphase++;
		}
		else if (shotphase <= 45 || shotphase > 70) // Phase 5
		{
			animation1 = &diagonalturret5;

			if (ishit == true)
			{
				animation = &hitdiagonalturret5;
				ishit = false;
			}
			shotphase++;
		}
		else if (shotphase <= 50 || shotphase > 65) // Phase 6
		{
			animation1 = &diagonalturret6;

			if (ishit == true)
			{
				animation = &hitdiagonalturret6;
				ishit = false;
			}
			shotphase++;
		}
		else if (shotphase <= 55 || shotphase > 60) // Phase 7
		{
			animation1 = &diagonalturret7;

			if (ishit == true)
			{
				animation = &hitdiagonalturret7;
				ishit = false;
			}
			shotphase++;
		}
		else if (shotphase <= 60) // Phase 8
		{
			animation1 = &diagonalturret8;

			if (ishit == true)
			{
				animation = &hitdiagonalturret8;
				ishit = false;
			}
			shotphase++;
		}

		if (shotphase == 95)
		{
			shotphase = 0;
		}
		if (shotphase == 63) //Only in this phase the train shoots
		{
			if (sqrtf(distance.x*distance.x + distance.y*distance.y) < 760)
				shoot = true;
		}
	}

	// Shoot
	// Shooting
	distance.x *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
	distance.y *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
	if (shoot == true)
	{
		if (App->player->position.y < (position.y))
		{
			distance.y *= -1;
		}
		if (App->player->position.x < (position.x))
		{
			distance.x *= -1;
		}
		App->particles->AddParticle(App->particles->enemyshot, position.x + 40, position.y + 20, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);

		shoot = false;
	}
}
