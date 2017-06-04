#include "Enemy_Long_Megatank.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleGroundEnemies.h"


Enemy_Long_Megatank::Enemy_Long_Megatank(int x, int y, int path) : Enemy(x, y)
{
	spritesheet = 6;
	animations = 1;

	hp = 240;
	points = 880;

	shellstart.PushBack({ 8, 7, 81, 53 });
	shellstart.PushBack({ 8, 7, 81, 53 });
	shellstart.PushBack({ 90, 7, 81, 53 });
	shellstart.PushBack({ 90, 7, 81, 53 });
	shellstart.PushBack({ 90, 65, 81, 53 });
	shellstart.PushBack({ 90, 65, 81, 53 });
	shellstart.PushBack({ 172, 65, 81, 53 });
	shellstart.PushBack({ 172, 65, 81, 53 });
	shellstart.PushBack({ 172, 7, 81, 53 });
	shellstart.PushBack({ 172, 7, 81, 53 });
	shellstart.PushBack({ 254, 7, 81, 53 });
	shellstart.PushBack({ 254, 7, 81, 53 });
	shellstart.PushBack({ 254, 65, 81, 53 });
	shellstart.PushBack({ 254, 65, 81, 53 });
	shellstart.PushBack({ 172, 65, 81, 53 });
	shellstart.PushBack({ 172, 65, 81, 53 });
	shellstart.PushBack({ 172, 7, 81, 53 });
	shellstart.PushBack({ 172, 7, 81, 53 });
	shellstart.PushBack({ 336, 7, 81, 53 });
	shellstart.PushBack({ 336, 7, 81, 53 });
	shellstart.PushBack({ 336, 65, 81, 53 });
	shellstart.PushBack({ 336, 65, 81, 53 });
	shellstart.PushBack({ 8, 65, 81, 53 });
	shellstart.PushBack({ 8, 65, 81, 53 });
	shellstart.loop = true;
	shellstart.speed = 0.9f;

	hitshell.PushBack({ 664, 7, 81, 53 });

	dmgshell.PushBack({ 8, 7, 81, 53 });
	dmgshell.PushBack({ 8, 7, 81, 53 });
	dmgshell.PushBack({ 910, 7, 81, 53 });
	dmgshell.PushBack({ 910, 7, 81, 53 });
	dmgshell.PushBack({ 90, 65, 81, 53 });
	dmgshell.PushBack({ 90, 65, 81, 53 });
	dmgshell.PushBack({ 992, 65, 81, 53 });
	dmgshell.PushBack({ 172, 65, 81, 53 });
	dmgshell.PushBack({ 172, 7, 81, 53 });
	dmgshell.PushBack({ 1074, 7, 81, 53 });
	dmgshell.PushBack({ 254, 7, 81, 53 });
	dmgshell.PushBack({ 254, 7, 81, 53 });
	dmgshell.PushBack({ 1156, 65, 81, 53 });
	dmgshell.PushBack({ 1156, 65, 81, 53 });
	dmgshell.PushBack({ 172, 65, 81, 53 });
	dmgshell.PushBack({ 172, 65, 81, 53 });
	dmgshell.PushBack({ 1074, 7, 81, 53 });
	dmgshell.PushBack({ 1074, 7, 81, 53 });
	dmgshell.PushBack({ 336, 7, 81, 53 });
	dmgshell.PushBack({ 336, 7, 81, 53 });
	dmgshell.PushBack({ 1238, 65, 81, 53 });
	dmgshell.PushBack({ 1238, 65, 81, 53 });
	dmgshell.PushBack({ 8, 65, 81, 53 });
	dmgshell.PushBack({ 910, 65, 81, 53 });
	dmgshell.loop = true;
	dmgshell.speed = 0.5f;

	transformation.PushBack({ 90, 123, 81, 53 });
	transformation.PushBack({ 90, 123, 81, 53 });
	transformation.PushBack({ 172, 123, 81, 53 });
	transformation.PushBack({ 172, 123, 81, 53 });
	transformation.PushBack({ 254, 123, 81, 53 });
	transformation.PushBack({ 254, 181, 81, 53 });
	transformation.PushBack({ 172, 181, 81, 53 });
	transformation.PushBack({ 172, 181, 81, 53 });
	transformation.PushBack({ 336, 181, 81, 53 });
	transformation.PushBack({ 336, 181, 81, 53 });
	transformation.loop = false;
	transformation.speed = 0.5f;

	hittransformation.PushBack({ 664,181,81,53 });

	dmgtransformation.PushBack({ 90, 123, 81, 53 });
	dmgtransformation.PushBack({ 90, 123, 81, 53 });
	dmgtransformation.PushBack({ 992, 123, 81, 53 });
	dmgtransformation.PushBack({ 992, 123, 81, 53 });
	dmgtransformation.PushBack({ 254, 123, 81, 53 });
	dmgtransformation.PushBack({ 254, 181, 81, 53 });
	dmgtransformation.PushBack({ 992, 181, 81, 53 });
	dmgtransformation.PushBack({ 992, 181, 81, 53 });
	dmgtransformation.PushBack({ 336, 181, 81, 53 });
	dmgtransformation.PushBack({ 336, 181, 81, 53 });
	dmgtransformation.loop = false;
	dmgtransformation.speed = 0.5f;
	
	transformation2.PushBack({ 8, 239, 81, 53 });
	transformation2.PushBack({ 8, 239, 81, 53 });
	transformation2.PushBack({ 8, 239, 81, 53 });
	transformation2.PushBack({ 90, 297, 81, 53 });
	transformation2.PushBack({ 90, 297, 81, 53 });
	transformation2.PushBack({ 172, 297, 81, 53 });
	transformation2.PushBack({ 172, 297, 81, 53 });
	transformation2.PushBack({ 254, 297, 81, 53 });
	transformation2.loop = false;
	transformation2.speed = 0.5f;

	hittransformation2.PushBack({ 664,297,81,53 });

	dmgtransformation2.PushBack({ 828, 239, 81, 53 });
	dmgtransformation2.PushBack({ 8, 239, 81, 53 });
	dmgtransformation2.PushBack({ 8, 239, 81, 53 });
	dmgtransformation2.PushBack({ 910, 297, 81, 53 });
	dmgtransformation2.PushBack({ 910, 297, 81, 53 });
	dmgtransformation2.PushBack({ 172, 297, 81, 53 });
	dmgtransformation2.PushBack({ 172, 297, 81, 53 });
	dmgtransformation2.PushBack({ 1074, 297, 81, 53 });
	dmgtransformation2.loop = false;
	dmgtransformation2.speed = 0.5f;

	transformation3.PushBack({ 254, 355, 81, 53 });
	transformation3.PushBack({ 172, 355, 81, 53 });
	transformation3.PushBack({ 172, 355, 81, 53 });
	transformation3.PushBack({ 336, 355, 81, 53 });
	transformation3.PushBack({ 336, 355, 81, 53 });
	transformation3.loop = false;
	transformation3.speed = 0.5f;

	hittransformation3.PushBack({ 664,355,81,53 });

	dmgtransformation3.PushBack({ 1074, 355, 81, 53 });
	dmgtransformation3.PushBack({ 172, 355, 81, 53 });
	dmgtransformation3.PushBack({ 172, 355, 81, 53 });
	dmgtransformation3.PushBack({ 1156, 355, 81, 53 });
	dmgtransformation3.PushBack({ 1156, 355, 81, 53 });
	dmgtransformation3.loop = false;
	dmgtransformation3.speed = 0.5f;

	transformation4.PushBack({ 8, 413, 81, 53 });
	transformation4.PushBack({ 8, 413, 81, 53 });
	transformation4.PushBack({ 90, 413, 81, 53 });
	transformation4.PushBack({ 90, 413, 81, 53 });
	transformation4.PushBack({ 172, 413, 81, 53 });
	transformation4.PushBack({ 172, 413, 81, 53 });
	transformation4.PushBack({ 254, 413, 81, 53 });
	transformation4.PushBack({ 254, 413, 81, 53 });
	transformation4.loop = false;
	transformation4.speed = 0.5f;

	hittransformation4.PushBack({ 582,413,81,53 });


	dmgtransformation4.PushBack({ 8, 413, 81, 53 });
	dmgtransformation4.PushBack({ 8, 413, 81, 53 });
	dmgtransformation4.PushBack({ 910, 413, 81, 53 });
	dmgtransformation4.PushBack({ 910, 413, 81, 53 });
	dmgtransformation4.PushBack({ 172, 413, 81, 53 });
	dmgtransformation4.PushBack({ 172, 413, 81, 53 });
	dmgtransformation4.PushBack({ 1074, 413, 81, 53 });
	dmgtransformation4.PushBack({ 1074, 413, 81, 53 });
	dmgtransformation4.loop = false;
	transformation4.speed = 0.5f;

	finalform.PushBack({ 336, 413, 81, 53 });
	finalform.PushBack({ 336, 413, 81, 53 });
	finalform.PushBack({ 8, 471, 81, 53 });
	finalform.PushBack({ 8, 471, 81, 53 });
	finalform.PushBack({ 90, 471, 81, 53 });
	finalform.PushBack({ 90, 471, 81, 53 });
	finalform.PushBack({ 172, 471, 81, 53 });
	finalform.PushBack({ 172, 471, 81, 53 });
	finalform.PushBack({ 254, 471, 81, 53 });
	finalform.PushBack({ 254, 471, 81, 53 });
	finalform.PushBack({ 336, 471, 81, 53 });
	finalform.PushBack({ 336, 471, 81, 53 });

	dmgfinalform.PushBack({ 336, 413, 81, 53 });
	dmgfinalform.PushBack({ 336, 413, 81, 53 });
	dmgfinalform.PushBack({ 828, 471, 81, 53 });
	dmgfinalform.PushBack({ 828, 471, 81, 53 });
	dmgfinalform.PushBack({ 90, 471, 81, 53 });
	dmgfinalform.PushBack({ 90, 471, 81, 53 });
	dmgfinalform.PushBack({ 992, 471, 81, 53 });
	dmgfinalform.PushBack({ 992, 471, 81, 53 });
	dmgfinalform.PushBack({ 254, 471, 81, 53 });
	dmgfinalform.PushBack({ 254, 471, 81, 53 });
	dmgfinalform.PushBack({ 1156, 471, 81, 53 });
	dmgfinalform.PushBack({ 1156, 471, 81, 53 });

	stop.PushBack({ 336, 471, 81, 53 });

	dmgstop.PushBack({ 336, 471, 81, 53 });
	dmgstop.PushBack({ 336, 471, 81, 53 });
	dmgstop.PushBack({ 1156, 471, 81, 53 });
	dmgstop.PushBack({ 1156, 471, 81, 53 });

	hitfinalform.PushBack({ 746, 471, 81, 53 });


	longmegatank = true;
	
	movement.PushBack({-1.0f, 1.0f}, 250);
	movement.PushBack({ 0.0f, 0.0f}, 70);
	movement.PushBack({ 0.0f, -1.0f}, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 50);
	movement.PushBack({ 0.0f, 1.0f }, 75);
	movement.PushBack({ 0.0f, -1.0f }, 300);
	movement.PushBack({ 0.0f, 1.0f }, 100);
	movement.PushBack({ 0.0f, 4.0f }, 1000);
	
	collider = App->collision->AddCollider({ 0, 0, 48*3, 45*3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->genemies);
	
	original_pos.x = x;
	original_pos.y = -200;
}

void Enemy_Long_Megatank::MoveShoot()
{
	w = 81 * 3;
	h = 53 * 3;
	

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

	if (movement.steps[movement.GetCurrentStep()].speed.x == -1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f)
	{
		if (hp >= 30)
		animation = &shellstart;
		shell = true;
		if (ishit == true)
		{
			animation = &hitshell;
			ishit = false;
		}

		if (hp < 30)
			animation = &dmgshell;
		shell = true;
		if (ishit == true)
		{
			animation = &hitshell;
			ishit = false;
		}
	}

	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f)
	{
		if (hp >= 30)
		{
			animation = &transformation;
			if (ishit == true)
			{
				animation = &hittransformation;
				ishit = false;
			}
			if (transformation.Finished())
			{
				step1 = true;
			}
			if (step1 == true)
			{
				animation = &transformation2;
				if (ishit2 == true)
				{
					animation = &hittransformation2;
					ishit2 = false;
				}
				if (transformation2.Finished())
				{
					step1 = false;
					step2 = true;
				}
			}
			if (step2 == true)
			{
				animation = &transformation3;
				if (ishit3 == true)
				{
					animation = &hittransformation3;
					ishit3 = false;
				}
				if (transformation3.Finished())
				{
					step2 = false;
					step3 = true;
				}
			}
			if (step3 == true)
			{
				animation = &transformation4;
				if (ishit4 == true)
				{
					animation = &hittransformation4;
					ishit4 = false;
				}
				if (transformation4.Finished())
				{
					step3 = false;
				}
			}
		}
		if (hp < 30)
		{
			animation = &dmgtransformation;
			if (ishit == true)
			{
				animation = &hittransformation;
				ishit = false;
			}
			if (dmgtransformation.Finished())
			{
				step1 = true;
			}
			if (step1 == true)
			{
				animation = &dmgtransformation2;
				if (ishit2 == true)
				{
					animation = &hittransformation2;
					ishit2 = false;
				}
				if (dmgtransformation2.Finished())
				{
					step1 = false;
					step2 = true;
				}
			}
			if (step2 == true)
			{
				animation = &dmgtransformation3;
				if (ishit3 == true)
				{
					animation = &hittransformation3;
					ishit3 = false;
				}
				if (dmgtransformation3.Finished())
				{
					step2 = false;
					step3 = true;
				}
			}
			if (step3 == true)
			{
				animation = &dmgtransformation4;
				if (ishit4 == true)
				{
					animation = &hittransformation4;
					ishit4 = false;
				}
				if (dmgtransformation4.Finished())
				{
					step3 = false;
				}
			}
		}
	}
	
	

	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == -1.0f
		|| movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 4.0f)
	{
		if (hp >= 30)
		{
			animation = &finalform;
			shooting = true;
			shell = false;
			if (ishit == true)
			{
				animation = &hitfinalform;
				ishit = false;
			}
		}
		if (hp < 30)
		{
			animation = &dmgfinalform;
			shooting = true;
			shell = false;
			if (ishit == true)
			{
				animation = &hitfinalform;
				ishit = false;
			}
		}
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f)
	{
		if (hp >= 30)
		{
			animation = &stop;
			shooting = true;
			shell = false;
			if (ishit == true)
			{
				animation = &hitfinalform;
				ishit = false;
			}
		}
		if (hp < 30)
		{
			animation = &dmgstop;
			shooting = true;
			shell = false;
			if (ishit == true)
			{
				animation = &hitfinalform;
				ishit = false;
			}
		}

	}

	
	distance.x = fabs(distance.x);
	distance.y = fabs(distance.y);
	// Shooting
	if (shell == true)
	{
		time_controll++;
		if (time_controll % 50 == 0)

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
	
	if (shooting == true)

	{
		++shoot_time;
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
			if (shoot_time % 140 == 0)//first wave
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 30 * 3, position.y + 11 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time % 143 == 0)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 38 * 3, position.y + 11 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time % 146 == 0)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 44 * 3, position.y + 16 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time % 149 == 0)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 44 * 3, position.y + 23 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time % 152 == 0)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 38 * 3, position.y + 29 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time % 155 == 0)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 30 * 3, position.y + 29 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time % 158 == 0)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 24 * 3, position.y + 23 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time % 161 == 0)//second wave
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 24 * 3, position.y + 16 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time % 165 == 0)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 30 * 3, position.y + 11 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time % 168 == 0)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 38 * 3, position.y + 11 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time % 171 == 0)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 44 * 3, position.y + 16 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time % 174 == 0)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 44 * 3, position.y + 23 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time % 177 == 0)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 38 * 3, position.y + 29 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time % 180 == 0)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 30 * 3, position.y + 29 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time % 183 == 0)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 24 * 3, position.y + 23 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time % 186 == 0)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + 24 * 3, position.y + 16 * 3, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
			if (shoot_time == 220)
			{
				shoot_time = 100;
				++shoot_time;
			}
		}
		shooting == false;
	}
}