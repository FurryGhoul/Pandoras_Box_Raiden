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
	kamikaze1.type = ENEMY_TYPES::KAMIKAZE;
	kamikaze1._path = 1;
	kamikaze2.type = ENEMY_TYPES::KAMIKAZE;
	kamikaze2._path = 2;
	kamikaze3.type = ENEMY_TYPES::KAMIKAZE;
	kamikaze3._path = 3;
	kamikaze4.type = ENEMY_TYPES::KAMIKAZE;
	kamikaze4._path = 4;
	kamikaze5.type = ENEMY_TYPES::KAMIKAZE;
	kamikaze5._path = 5;
	kamikaze6.type = ENEMY_TYPES::KAMIKAZE;
	kamikaze6._path = 6;
	kamikaze7.type = ENEMY_TYPES::KAMIKAZE;
	kamikaze7._path = 7;
	kamikaze8.type = ENEMY_TYPES::KAMIKAZE;
	kamikaze8._path = 8;

	w = 96 * 3;
	h = 53 * 3;
	collider = App->collision->AddCollider({ 0, 0, w, h }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_pos.x = (x + w/2);
	original_pos.y = 10;
	time = SDL_GetTicks();
}


void Enemy_Boss_Main::MoveShoot()
{
	//Kamikaze positions
	kamikaze1.x = ((position.x - (12 * 3)) + 80 * 3 + 192);
	kamikaze1.y = ((position.y - (18 * 3)) + (16 * 3));
	kamikaze2.x = ((position.x - (12 * 3)) + 64 * 3 + 192);
	kamikaze2.y = ((position.y - (18 * 3)) + (12 * 3));
	kamikaze3.x = ((position.x - (12 * 3)) + 80 * 3 + 192);
	kamikaze3.y = ((position.y - (18 * 3)) + (32 * 3));
	kamikaze4.x = ((position.x - (12 * 3)) + 64 * 3 + 192);
	kamikaze4.y = ((position.y - (18 * 3)) + (28 * 3));
	kamikaze5.x = ((position.x - (5 * 3)) + 192);
	kamikaze5.y = ((position.y - (19 * 3)) + (16 * 3));
	kamikaze6.x = ((position.x - (5 * 3)) + (16 * 3) + 192);
	kamikaze6.y = ((position.y - (19 * 3)) + (12 * 3));
	kamikaze7.x = ((position.x - (5 * 3)) + 192);
	kamikaze7.y = ((position.y - (19 * 3)) + (32 * 3));
	kamikaze8.x = ((position.x - (5 * 3)) + (16 * 3) + 192);
	kamikaze8.y = ((position.y - (19 * 3)) + (28 * 3));

	if (shootingkamikazes)
	{
		if (kamikazewaves >= 21)
		{
			shootingkamikazes = false;
			animation = &idle;
		}
	}

	if (shootingkamikazes && (SDL_GetTicks() - time) > 500 && kamikazett)
	{
		App->enemies->SpawnEnemy(kamikaze1);
		App->enemies->SpawnEnemy(kamikaze2);
		App->enemies->SpawnEnemy(kamikaze3);
		App->enemies->SpawnEnemy(kamikaze4);
		App->enemies->SpawnEnemy(kamikaze5);
		App->enemies->SpawnEnemy(kamikaze6);
		App->enemies->SpawnEnemy(kamikaze7);
		App->enemies->SpawnEnemy(kamikaze8);
		kamikazett = false;
		kamikazewaves++;
	}

	if (idk % 100 == 0)
		kamikazett = true;

	idk++;

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