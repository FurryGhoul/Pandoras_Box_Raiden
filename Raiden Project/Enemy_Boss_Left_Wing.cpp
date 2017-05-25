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
	hp = 30;
	points = 730;
	spritesheet = 10;
	animations = 1;
	bosswing = true;

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

	//Path
	//Entering
	movement.PushBack({ 0.0f, 2.0f }, 100);
	//Movement
	movement.PushBack({ 2.0f, 0.0f }, 80); movement.PushBack({ -2.0f, 0.0f }, 160); movement.PushBack({ 2.0f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 2.0f }, 30); movement.PushBack({ 0.0f, -2.0f }, 80); movement.PushBack({ -2.0f, 0.0f }, 80);
	movement.PushBack({ 2.0f, 0.0f }, 160); movement.PushBack({ -2.0f, 0.0f }, 80); movement.PushBack({ 0.0f, 2.0f }, 60);

	movement.PushBack({ 2.0f, 0.0f }, 80); movement.PushBack({ -2.0f, 0.0f }, 160); movement.PushBack({ 2.0f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 2.0f }, 30); movement.PushBack({ 0.0f, -2.0f }, 80); movement.PushBack({ -2.0f, 0.0f }, 80);
	movement.PushBack({ 2.0f, 0.0f }, 160); movement.PushBack({ -2.0f, 0.0f }, 80); movement.PushBack({ 0.0f, 2.0f }, 60);

	movement.PushBack({ 2.0f, 0.0f }, 80); movement.PushBack({ -2.0f, 0.0f }, 160); movement.PushBack({ 2.0f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 2.0f }, 30); movement.PushBack({ 0.0f, -2.0f }, 80); movement.PushBack({ -2.0f, 0.0f }, 80);
	movement.PushBack({ 2.0f, 0.0f }, 160); movement.PushBack({ -2.0f, 0.0f }, 80); movement.PushBack({ 0.0f, 2.0f }, 60);

	movement.PushBack({ 2.0f, 0.0f }, 80); movement.PushBack({ -2.0f, 0.0f }, 160); movement.PushBack({ 2.0f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 2.0f }, 30); movement.PushBack({ 0.0f, -2.0f }, 80); movement.PushBack({ -2.0f, 0.0f }, 80);
	movement.PushBack({ 2.0f, 0.0f }, 160); movement.PushBack({ -2.0f, 0.0f }, 80); movement.PushBack({ 0.0f, 2.0f }, 60);

	movement.PushBack({ 2.0f, 0.0f }, 80); movement.PushBack({ -2.0f, 0.0f }, 160); movement.PushBack({ 2.0f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 2.0f }, 30); movement.PushBack({ 0.0f, -2.0f }, 80); movement.PushBack({ -2.0f, 0.0f }, 80);
	movement.PushBack({ 2.0f, 0.0f }, 160); movement.PushBack({ -2.0f, 0.0f }, 80); movement.PushBack({ 0.0f, 2.0f }, 60);

	movement.PushBack({ 2.0f, 0.0f }, 80); movement.PushBack({ -2.0f, 0.0f }, 160); movement.PushBack({ 2.0f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 2.0f }, 30); movement.PushBack({ 0.0f, -2.0f }, 80); movement.PushBack({ -2.0f, 0.0f }, 80);
	movement.PushBack({ 2.0f, 0.0f }, 160); movement.PushBack({ -2.0f, 0.0f }, 80); movement.PushBack({ 0.0f, 2.0f }, 60);

	movement.PushBack({ 2.0f, 0.0f }, 80); movement.PushBack({ -2.0f, 0.0f }, 160); movement.PushBack({ 2.0f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 2.0f }, 30); movement.PushBack({ 0.0f, -2.0f }, 80); movement.PushBack({ -2.0f, 0.0f }, 80);
	movement.PushBack({ 2.0f, 0.0f }, 160); movement.PushBack({ -2.0f, 0.0f }, 80); movement.PushBack({ 0.0f, 2.0f }, 60);

	movement.PushBack({ 2.0f, 0.0f }, 80); movement.PushBack({ -2.0f, 0.0f }, 160); movement.PushBack({ 2.0f, 0.0f }, 80);
	//Flying away
	movement.PushBack({ 0.0f, 2.0f }, 30); movement.PushBack({ 0.0f, -2.0f }, 80); movement.PushBack({ 0.0f, 3.0f }, 10000);

	w = 32 * 3;
	h = 23 * 3;
	collider = App->collision->AddCollider({ 0, 0, w, h }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_pos.x = x;
	original_pos.y = y;
	time = SDL_GetTicks();
	time1 = SDL_GetTicks();
	animation = &idle;
}


void Enemy_Boss_Left_Wing::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
	position.x += left_right_mod;

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

	if ((SDL_GetTicks() - time1) >= 1200)
	{
		shoot = true;
		animation = &shooting;
		time1 = SDL_GetTicks();
	}
}