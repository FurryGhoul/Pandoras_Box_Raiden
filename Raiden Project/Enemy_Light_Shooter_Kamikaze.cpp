#include "Enemy_Light_Shooter_Kamikaze.h"
#include "Enemy_Light_Shooter.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"
#define PI 3.14159265


Light_Shooter_Kamikaze::Light_Shooter_Kamikaze(int x, int y, int path, bool pcome_right) : Enemy(x, y)
{
	hp = 1;
	points = 130;
	light_kamikaze = true;
	// Anmiation pushback's

	//South to East
	flys.PushBack({ 16, 58, 27, 20 }); flys.name = 1;
	flyse1.PushBack({ 291, 23, 26, 21 }); flyse1.name = 2;
	flyse2.PushBack({ 250, 19, 26, 25 }); flyse2.name = 3;
	flyse3.PushBack({ 211, 18, 22, 25 }); flyse3.name = 4;

	// East to North
	flye.PushBack({ 178, 20, 20, 23 }); flye.name = 5;
	flyne1.PushBack({ 136, 19, 24, 24 }); flyne1.name = 6;
	flyne2.PushBack({ 100, 18, 26, 24 }); flyne2.name = 7;
	flyne3.PushBack({ 58, 18, 27, 22 }); flyne3.name = 8;

	//North to West
	flyn.PushBack({ 16, 18, 27, 20 });  flyn.name = 9;
	flynw1.PushBack({ 205, 56, 27, 23 }); flynw1.name = 10;
	flynw2.PushBack({ 243, 53, 27, 25 }); flynw2.name = 11;
	flynw3.PushBack({ 291, 54, 24, 24 }); flynw3.name = 12;

	//West to South
	flyw.PushBack({ 174, 55, 20, 23 }); flyw.name = 13;
	flysw1.PushBack({ 137, 54, 22, 25 }); flysw1.name = 14;
	flysw2.PushBack({ 96, 53, 25, 25 }); flysw2.name = 15;
	flysw3.PushBack({ 56, 56, 26, 20 }); flysw3.name = 16;

	collider = App->collision->AddCollider({ 0, 0, 25 * 3 - 5, 25 * 3 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	spritesheet = 8;
	animations = 1;
    
	pclock[0] = &flys;
	pclock[1] = &flysw3;
	pclock[2] = &flysw2;
	pclock[3] = &flysw1;
	pclock[4] = &flyw;
	pclock[5] = &flynw3;
	pclock[6] = &flynw2;
	pclock[7] = &flynw1;
	pclock[8] = &flyn;
	pclock[9] = &flyne3;
	pclock[10] = &flyne2;
	pclock[11] = &flyne1;
	pclock[12] = &flye;
	pclock[13] = &flyse3;
	pclock[14] = &flyse2;
	pclock[15] = &flyse1;

	getvector = false;

	come_right = pcome_right;
	if (come_right)
	{
		anim_doing = 12;
	}
	else
	{
		anim_doing = 4;
	}
	position.x =original_pos.x = x;

	position.y= original_pos.y = 100;
	if (path == 0)
	{
	position.y = original_pos.y = 100;
	}
	if (path == 1)
	{
		position.y = original_pos.y = 150;
	}
	if (path == 2)
	{
		position.y = original_pos.y = 200;
	}
	if (path == 3)
	{
		position.y = original_pos.y = 250;
	}
	if (path == 4)
	{
		position.y = original_pos.y = 300;
	}
	if (path == 5)
	{
		position.y = original_pos.y = 350;

	}
	if (path == 6)
	{
		position.y = original_pos.y = 400;
	}
	if (path == 7)
	{
		position.y = original_pos.y = 450;
	}
	if (path == 8)
	{
		position.y = original_pos.y = 500;
	}
	if (path == 9)
	{
		position.y = original_pos.y = 550;
	}
	if (path == 10)
	{
		position.y = original_pos.y = 600;
	}
	if (path == 11)
	{
		position.y = original_pos.y = 650;
	}
}


void Light_Shooter_Kamikaze::MoveShoot()
{
	if (!time_got)
	{
		time = SDL_GetTicks();
		time_got = true;
	}

if (!close && !spining)
{ 
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
	// Animation

	// Setting angle
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

	// South to East
	if (se && angle > 72 && angle < 90)
	{
		animation = &flys;
		w = 27 * 3;
		h = 20 * 3;
	}
	if (se && angle > 54 && angle < 72)
	{
		animation = &flyse1;
		w = 26 * 3;
		h = 21 * 3;
	}
	if (se && angle > 36 && angle < 54)
	{
		animation = &flyse2;
		w = 26 * 3;
		h = 25 * 3;
	}
	if (se && angle > 18 && angle < 36)
	{
		animation = &flyse3;
		w = 22 * 3;
		h = 25 * 3;
	}
	if (se && angle > 0 && angle < 18)
	{
		animation = &flye;
		w = 20 * 3;
		h = 23 * 3;
	}

	// East to North
	if (ne && angle > 0 && angle < 18)
	{
		animation = &flye;
		w = 20 * 3;
		h = 23 * 3;
	}
	if (ne && angle > 18 && angle < 36)
	{
		animation = &flyne1;
		w = 24 * 3;
		h = 24 * 3;
	}
	if (ne && angle > 36 && angle < 54)
	{
		animation = &flyne2;
		w = 26 * 3;
		h = 24 * 3;
	}
	if (ne && angle > 54 && angle < 72)
	{
		animation = &flyne3;
		w = 27 * 3;
		h = 22 * 3;
	}
	if (ne && angle > 72 && angle < 90)
	{
		animation = &flyn;
		w = 27 * 3;
		h = 20 * 3;
	}

	// North to West
	if (nw && angle > 72 && angle < 90)
	{
		animation = &flyn;
		w = 27 * 3;
		h = 20 * 3;
	}
	if (nw && angle > 54 && angle < 72)
	{
		animation = &flynw1;
	
		w = 27 * 3;
		h = 23 * 3;
	}
	if (nw && angle > 36 && angle < 54)
	{
		animation = &flynw2;
		w = 27 * 3;
		h = 25 * 3;
	}
	if (nw && angle > 18 && angle < 36)
	{
		animation = &flynw3;
	
		w = 24 * 3;
		h = 24 * 3;
	}
	if (nw && angle > 0 && angle < 18)
	{
		animation = &flyw;
		w = 20 * 3;
		h = 23 * 3;
	}

	// West to South
	if (sw && angle > 0 && angle < 18)
	{
		animation = &flyw;
		w = 20 * 3;
		h = 23 * 3;
	}
	if (sw && angle > 18 && angle < 36)
	{
		animation = &flysw1;
		w = 22 * 3;
		h = 25 * 3;
	}
	if (sw && angle > 36 && angle < 54)
	{
		animation = &flysw2;
		w = 25 * 3;
		h = 25 * 3;
	}
	if (sw && angle > 54 && angle < 72)
	{
		animation = &flysw3;
		w = 26 * 3;
		h = 20 * 3;
	}
	if (sw && angle > 72 && angle < 90)
	{
		animation = &flys;
		w = 27 * 3;
		h = 20 * 3;
	}
}
if (come_right && se || come_right && sw || !come_right && nw || !come_right && ne)
{
	clock = true;
}
else
{
	clock = false;
}
     //Movement
	if (SDL_GetTicks() - time < 1600) //Horizontal
	{
		if (come_right)
		{ 
		position.x += 3;
		animation = &flye;
		}
		else
		{
		position.x -= 3;
		animation = &flyw;
		}
		
		w = 20 * 3;
		h = 23 * 3;
	
	}
	else //Towards player
	{
	
		//Detecting distance
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

		
		
		if(sqrtf(distance.y* distance.y + distance.x*distance.x)> 150 && !close || !once)
		{ 
		    vector.x = distance.x * (5 / sqrtf(distance.x*distance.x + distance.y*distance.y));
	        vector.y = distance.y * (5 / sqrtf(distance.x*distance.x + distance.y*distance.y));
			once = true;
		
		}
		else
		{
			close = true;
			
		}
		
		//Spin 
		//Calculating anim difference
		if (!anim_calculated)
		{ 
		    if (clock && come_right)
		    { 
		        for (int i = 12; pclock[i]->name != animation->name; i++) 
		        {
					anim_difference++;
					if (i == 15)
					{
						i = -1;
					}
		        }
		    }
			if (clock && !come_right)
			{
				for (int i = 4; pclock[i]->name != animation->name; i++)
				{
					anim_difference++;
					if (i == 16)
					{
						i = -1;
					}
				}
			}
			if (!clock && come_right)
			{
				for (int i = 12; pclock[i]->name != animation->name; i--)
				{
					anim_difference++;
					if (i == 0)
					{
						i = 16;
					}
				}
			}
			if(!clock && !come_right)
				for (int i = 4; pclock[i]->name != animation->name; i--)
				{
					anim_difference++;
					if (i == 0)
					{
						i = 16;
					}
				}
			anim_calculated = true;
			anim_chill = 10;
		}
		//Spining
		if (clock  && anim_difference != anims_done && anim_chill % 10 == 0)
		{
			animation = pclock[anim_doing];
			anims_done++;
			anim_doing++;
			if (anim_doing >= 16)
			{
				anim_doing = 0;
			}
			spining = true;
		}
		if (!clock  && anim_difference != anims_done && anim_chill % 10 == 0)
		{
			
			animation = pclock[anim_doing];
			anims_done++;
			anim_doing--;
			if (anim_doing <= -1)
			{
				anim_doing = 15;
			}
			spining = true;
		
		}

		if (anim_difference == anims_done)
		{
			spining = false;
		}

		if (!spining)
		{ 
		position.x += vector.x;
		position.y += vector.y;
		}
			
			
	   //Shoot
			if (!close)
			{ 
			distance.x *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
			distance.y *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
			if (sqrtf(distance.x*distance.x + distance.y*distance.y) < 500 && shooting == false)
			{
				if (shoot_time % 40 == 0 && position.y <= 760)
				{
					if (App->player->position.y < (position.y))
					{
						distance.y *= -1;
					}
					if (App->player->position.x < (position.x))
					{
						distance.x *= -1;
					}
					App->particles->AddParticle(App->particles->enemyshot, position.x + 10, position.y + 50, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y); 

					shooting = true;
				}
				shooting = false;
			}
	    }
	}
	++shoot_time;
	++anim_chill;

	if (animation == &flys)
	{
		w = 27 * 3;
		h = 20 * 3;
	}

	if (animation == &flyse1)
	{
		w = 26 * 3;
		h = 21 * 3;
	}

	if(animation == &flyse2)
	{ 
		w = 26 * 3;
		h = 25 * 3;
	}
	

	if(animation == &flyse3)
	{ 
		w = 22 * 3;
		h = 25 * 3;
	}

	if(animation == &flye)
	{
		w = 20 * 3;
		h = 23 * 3;
	}

	// East to North
	if(animation == &flye)
	{
		w = 20 * 3;
		h = 23 * 3;
	}
	if(animation == &flyne1)
	{
		w = 24 * 3;
		h = 24 * 3;
	}
	if(animation == &flyne2)
	{
		w = 26 * 3;
		h = 24 * 3;
	}
	if(animation == &flyne3)
	{
		w = 27 * 3;
		h = 22 * 3;
	}
	if(animation == &flyn)
	{
		w = 27 * 3;
		h = 20 * 3;
	}

	// North to West
	
	if(animation == &flyn)
	{
		w = 27 * 3;
		h = 20 * 3;
	}
    if(animation == &flynw1)
    { 
		w = 27 * 3;
		h = 23 * 3;
	}
	if(animation == &flynw2)
	{
		w = 27 * 3;
		h = 25 * 3;
	}
	if(animation == &flynw3)
	{

		w = 24 * 3;
		h = 24 * 3;
	}
	if(animation == &flyw)
	{
		w = 20 * 3;
		h = 23 * 3;
	}

	// West to South
	if(animation == &flyw)
	{
		w = 20 * 3;
		h = 23 * 3;
	}
	if(animation == &flysw1)
	{
		w = 22 * 3;
		h = 25 * 3;
	}
	if(animation == &flysw2)
	{
		w = 25 * 3;
		h = 25 * 3;
	}
	if(animation == &flysw3)
	{
		w = 26 * 3;
		h = 20 * 3;
	}
	if(	animation == &flys)
	{
		w = 27 * 3;
		h = 20 * 3;
	}
}

	

