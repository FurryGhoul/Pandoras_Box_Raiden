#include "Enemy_Boss_Main.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"



Enemy_Boss_Main::Enemy_Boss_Main(int x, int y, int path) : Enemy(x, y)
{
	hp = 420;
	points = 29000;
	spritesheet = 10;
	animations = 1;
	megatank = true;

	//Animations
	//Idle with kamikazes
	idlewithkamikazes.PushBack({ 1, 92, 96, 53 });
	idlewithkamikazes.loop = false;
	//Idle
	idle.PushBack({ 1, 27, 96, 53 });
	idle.loop = false;
	//Opening
	opening.PushBack({ 1, 27, 96, 53 });
	opening.PushBack({ 98, 27, 96, 53 });
	opening.PushBack({ 195, 27, 96, 53 });
	opening.PushBack({ 292, 27, 96, 53 });
	opening.PushBack({ 389, 27, 96, 53 });
	opening.PushBack({ 486, 27, 96, 53 });
	//Closing
	closing.PushBack({ 486, 27, 96, 53 });
	closing.PushBack({ 389, 27, 96, 53 });
	closing.PushBack({ 292, 27, 96, 53 });
	closing.PushBack({ 195, 27, 96, 53 });
	closing.PushBack({ 98, 27, 96, 53 });
	closing.PushBack({ 1, 27, 96, 53 });
	//Shooting
	shooting.PushBack({ 98, 92, 96, 53 });
	shooting.PushBack({ 195, 92, 96, 53 });
	shooting.PushBack({ 292, 92, 96, 53 });
	//Destroyed
	destroyed.PushBack({ 583, 27, 96, 53 });
	destroyed.loop = false;

	//Path
	//Fly away
	flyaway.PushBack({ 0.0f, 3.0f }, 10000);
	//Entering
	entering.PushBack({ 0.0f, 2.0f }, 100);
	//Movement
	movement.PushBack({ 2.0f, 0.0f }, 80);
	movement.PushBack({ -2.0f, 0.0f }, 160);
	movement.PushBack({ 2.0f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 2.0f }, 30);
	movement.PushBack({ 0.0f, -2.0f }, 80);
	movement.PushBack({ -2.0f, 0.0f }, 80);
	movement.PushBack({ 2.0f, 0.0f }, 160);
	movement.PushBack({ -2.0f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 2.0f }, 60);
	movement.loop = true;

	//Kamikazes info
	//Kamikaze 1
	//Kamikaze 2
	//kamikaze2.type = ENEMY_TYPES::KAMIKAZE;
	//kamikaze2.x = (position.x - 0);
	//kamikaze2.y = 1;
	//kamikaze2._path = 2;

	w = 96 * 3;
	h = 53 * 3;
	collider = App->collision->AddCollider({ 0, 0, w, h }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_pos.x = (x + w/2);
	original_pos.y = 10;
	time = SDL_GetTicks();
}


void Enemy_Boss_Main::MoveShoot()
{
	if ((SDL_GetTicks() - time) < 2000)
	{
		animation = &idlewithkamikazes;
		position = original_pos + entering.GetCurrentPosition();
		position.x += left_right_mod;
	}
	else if ((SDL_GetTicks() - time) < 100000)
	{
		if (!posreset)
		{
			original_pos = position;
			posreset = true;
		}
		position = original_pos + movement.GetCurrentPosition();
		position.x += left_right_mod;
	}
	else
	{
		if (!posreset1)
		{
			original_pos = position;
			posreset1 = true;
		}
		position = original_pos + flyaway.GetCurrentPosition();
		position.x += left_right_mod;
	}
}