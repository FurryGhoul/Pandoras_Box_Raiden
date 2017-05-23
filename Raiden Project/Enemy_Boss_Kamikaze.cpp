#include "Enemy_Boss_Kamikaze.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"

#define PI 3.14159265

Enemy_Boss_Kamikaze::Enemy_Boss_Kamikaze(int x, int y, int path) : Enemy(x, y)
{
	hp = 1;
	points = 0;
	w = 32 * 3;
	h = 39 * 3;

	//Animation

	deploying.speed = 0.08f;

	// Anmiation pushback's

	//Coming from left
	deploying.PushBack({ 2, 2, 32, 39 });
	deploying.PushBack({ 37, 2, 32, 39 });
	deploying.PushBack({ 72, 2, 32, 39 });
	deploying.PushBack({ 107, 2, 32, 39 });
	deploying.PushBack({ 142, 2, 32, 39 });
	deploying.PushBack({ 177, 2, 32, 39 });
	deploying.PushBack({ 212, 2, 32, 39 });

	if (path == 0)
		movement.PushBack({ 4.0f, 4.0f }, 200);

	//Coming from right
	deploying1.PushBack({ 2, 50, 32, 39 });
	deploying1.PushBack({ 37, 50, 32, 39 });
	deploying1.PushBack({ 72, 50, 32, 39 });
	deploying1.PushBack({ 107, 50, 32, 39 });
	deploying1.PushBack({ 142, 50, 32, 39 });
	deploying1.PushBack({ 177, 50, 32, 39 });
	deploying1.PushBack({ 212, 50, 32, 39 });

	spritesheet = 5;
	animations = 1;
	original_pos.x = x;
	original_pos.y = -50;
	deploying.loop = true;
	deploying1.loop = true;

	if (path < 4)
		animation = &deploying;
	else if (path > 3)
		animation = &deploying1;

	time = SDL_GetTicks();
}

void Enemy_Boss_Kamikaze::MoveShoot()
{
	if ((SDL_GetTicks() - time) < 1430)
	{
		position = original_pos + movement.GetCurrentPosition();
		position.x += left_right_mod;
	}
	else
	{
		App->enemies->AddEnemy(3, ENEMY_TYPES::KAMIKAZE, position.x, position.y);
		position.y = 10000;
	}
}