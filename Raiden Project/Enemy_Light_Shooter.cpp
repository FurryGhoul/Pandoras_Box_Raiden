#include "Enemy_Light_Shooter.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
//#include <Math.h>

Enemy_Light_Shooter::Enemy_Light_Shooter(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 179,0,24,34 });
	fly.speed = 0.2f;
	fly.loop = false;
	animation = &fly;


	movement.PushBack({ -0.2f, 8.0f }, 50);
	movement.PushBack({ 0.0f, 0.0f }, 50);
	movement.PushBack({ -0.2f, -5.0f }, 600);

	collider = App->collision->AddCollider({ 0, 0, 24*3-5, 24*3+20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = -50;
	w = 24*3;
	h = 34*3;
}

void Enemy_Light_Shooter::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
	distance.y = App->player->position.y - 24 - position.y - 24 * 3;
	distance.x = App->player->position.x - position.y + 24 ;
	
	

	if (distance.y <= 400 && shooting == false)
	{

		
		while (sqrt(distance.x*distance.x + distance.y*distance.y) > 10) //I'm trying to convert the distance at which the player is from the enemy in a vector that represents the speed of the bullet, which shouldn't be bigger that 10
		{
			if (distance.x > 0)
			distance.x -= distance.x*0.1;
			distance.y -= distance.y*0.1;
		}
		
		App->particles->AddParticle(App->particles->enemyshot, position.x+10, position.y + 50, COLLIDER_ENEMY_SHOT,0, 0); //In theory, the speed should be distance.x and distance.y, but at the moment it doesn't work that way
		shooting = true;
	}
}
