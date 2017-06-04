#include "Enemy_Boss_Left_Wing.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"



Enemy_Boss_Left_Wing::Enemy_Boss_Left_Wing(int x, int y, int path) : Enemy(x, y)
{
	hp = 100;
	points = 730;
	spritesheet = 10;
	animations = 1;
	bossleftwing = true;

	//Animations
	//Idle
	idle.PushBack({ 1, 174, 32, 23 });
	idle.loop = false;
	//Shooting
	shooting.PushBack({ 77, 174, 32, 23 });
	shooting.loop = false;
	shooting.speed = 0.1f;
	//Closing cannon
	closing.PushBack({ 153, 174, 32, 23 });
	closing.loop = false;
	closing.speed = 0.1f;

	w = 32 * 3;
	h = 23 * 3;
	collider = App->collision->AddCollider({ 0, 0, w, h }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_pos.x = x;
	original_pos.y = y;
	animation = &idle;
	time = SDL_GetTicks();
}


void Enemy_Boss_Left_Wing::MoveShoot()
{
	if (closing.Finished())
	{
		animation = &idle;
		closing.Reset();
	}

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

	//Shooting
	if (shoot && shooting.Finished())
	{
		if (distance.x > 1)
			distance.x = 1;
		else
			distance.x = -1;

		shooting.Reset();
		animation = &closing;

		App->particles->AddParticle(App->particles->enemyshot, position.x + 57, position.y + 50, COLLIDER_ENEMY_SHOT, 0, distance.x, 10);
		shoot = false;
	}

	if ((SDL_GetTicks() - time) >= 1200)
	{
		shoot = true;
		animation = &shooting;
		time = SDL_GetTicks();
	}

	if (ishit && modifier == 0)
	{
		modifier = 301;
		hittime = SDL_GetTicks();
	}
	if (ishit && SDL_GetTicks() - hittime >= 100)
	{
		modifier = 0;
		ishit = false;
	}
}