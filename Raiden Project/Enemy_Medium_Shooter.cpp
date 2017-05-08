#include "Enemy_Medium_Shooter.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"

#define PI 3.14159265

Enemy_Medium_Shooter::Enemy_Medium_Shooter(int x, int y, int path) : Enemy(x, y)
{
	hp = 17;
	points = 480;
	
	// Anmiation pushback's

	// Idle animation
	/*flyi.PushBack({ 8, 47, 73, 54 });
	flyi1.PushBack({ 86, 47, 73, 53 });
	flyi2.PushBack({ 164, 47, 73, 54 });
	flyi3.PushBack({ 242, 47, 73, 53 });*/

	// Shooting animation
	flys.PushBack({ 8, 109, 73, 54 });
	flys1.PushBack({ 86, 109, 73, 52 });
	flys2.PushBack({ 164, 109, 73, 54 });
	flys3.PushBack({ 242, 109, 73, 52 });

	movement.PushBack({ -0.2f, 8.0f }, 50);
	movement.PushBack({ 0.0f, 0.0f }, 100);
	movement.PushBack({ -0.2f, -5.0f }, 600);

	mediumshooter = true;
	collider = App->collision->AddCollider({ 0, 0, 73 * 3 - 110, 54 * 3 - 110 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	spriteshit = 3;
	animations = 1;
	original_pos.x = x;
	original_pos.y = -50;
}

void Enemy_Medium_Shooter::MoveShoot()
{

	position = original_pos + movement.GetCurrentPosition();


	//position = original_pos + movement1.GetCurrentPosition();

	position.x += left_right_mod;

	++shoot_time;

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
	// Animation

	animation = &flys;
	w = 73 * 3;
	h = 53 * 3;

	distance.x = fabs(distance.x);
	distance.y = fabs(distance.y);

	// Shooting
	distance.x *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
	distance.y *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
	if (sqrtf(distance.x*distance.x + distance.y*distance.y) < 500 && shooting == false)
	{
		if (shoot_time % 80 == 0 && position.y <= 760)
		{
			if (App->player->position.y - 22 < (position.y - 22 * 3))
			{
				distance.y *= -1;
			}
			if (App->player->position.x < (position.x + 22))
			{
				distance.x *= -1;
			}
			App->particles->AddParticle(App->particles->enemyshot, position.x + 10, position.y + 50, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y); //In theory, the speed should be distance.x and distance.y, but at the moment it doesn't work that way

			shooting = true;
		}
		shooting = false;
	}
}