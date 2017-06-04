#include "Enemy_Boss_Cannon.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"



Enemy_Boss_Cannon::Enemy_Boss_Cannon(int x, int y, int path) : Enemy(x, y)
{
	hp = 100;
	points = 1100;
	spritesheet = 10;
	animations = 1;
	bosscannon = true;

	//Animations
	//Idle
	idle.PushBack({ 238, 174, 32, 26 });
	idle.loop = false;
	//Shooting
	shooting.PushBack({ 271, 174, 32, 26 });
	shooting.PushBack({ 304, 174, 32, 26 });
	shooting.PushBack({ 337, 174, 32, 26 });
	shooting.PushBack({ 370, 174, 32, 26 });
	shooting.PushBack({ 403, 174, 32, 26 });
	shooting.PushBack({ 436, 174, 32, 26 });
	shooting.loop = true;
	shooting.speed = 0.2f;

	w = 32 * 3;
	h = 26 * 3;
	collider = App->collision->AddCollider({ 0, 0, w, h }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_pos.x = x;
	original_pos.y = y;
	animation = &idle;
	time = SDL_GetTicks();
	time1 = SDL_GetTicks();
	shootx = 40;
	bullets = 14;
}


void Enemy_Boss_Cannon::MoveShoot()
{
	if (!isshooting)
		animation = &idle;
	else
		animation = &shooting;
	//Shooting
	if (bullets > 0 && shoot)
	{
		isshooting = true;

		App->particles->AddParticle(App->particles->enemyshot, position.x + shootx, position.y + 60, COLLIDER_ENEMY_SHOT, 0, 0, 10);

		if (shootx == 40)
			shootx = 14;
		else if (shootx == 14)
			shootx = 66;
		else if (shootx == 66)
			shootx = 40;

		shoot = false;

		bullets--;

		if (bullets < 1)
		{
			time1 = SDL_GetTicks();
			isshooting = false;
		}
	}

	if ((SDL_GetTicks() - time) >= 150)
	{
		shoot = true;
		time = SDL_GetTicks();
	}

	if (bullets < 1 && (SDL_GetTicks() - time1) >= 5000)
		bullets = 14;

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