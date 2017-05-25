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
	bossmain = true;

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

	//Parts info
	leftwing.type = ENEMY_TYPES::BOSS_LEFT_WING;
	leftwing._path = 0;
	leftwing.x = position.x - 32 * 3;
	leftwing.y = position.y + 32 * 3;

	rightwing.type = ENEMY_TYPES::BOSS_RIGHT_WING;
	rightwing._path = 0;
	rightwing.x = position.x + 96 * 3;
	rightwing.y = position.y + 32 * 3;

	cannon.type = ENEMY_TYPES::BOSS_CANNON;
	cannon._path = 0;
	cannon.x = position.x + 32 * 3;
	cannon.y = position.y + 34 * 3;

	w = 96 * 3;
	h = 53 * 3;
	collider = App->collision->AddCollider({ 0, 0, w, h }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_pos.x = (x + w/2);
	original_pos.y = 10;
	time = SDL_GetTicks();
	animation = &idlewithkamikazes;
}


void Enemy_Boss_Main::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
	position.x += left_right_mod;

	App->enemies->SetPos();

	//Kamikaze parts
	if (!parts)
	{
		App->enemies->SpawnEnemy(leftwing);
		App->enemies->SpawnEnemy(rightwing);
		App->enemies->SpawnEnemy(cannon);
		parts = true;
	}

	App->enemies->SetPos();

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
	
	if (kamikazeammo)
	{
		if (kamikazewaves >= 21)
		{
			kamikazeammo = false;
			animation = &idle;
		}
	}

	if (kamikazeammo && (SDL_GetTicks() - time) > 2500 && shootingkamikazes && (SDL_GetTicks() - time2) > delay)
	{
		App->enemies->SpawnEnemy(kamikaze1);
		App->enemies->SpawnEnemy(kamikaze2);
		App->enemies->SpawnEnemy(kamikaze3);
		App->enemies->SpawnEnemy(kamikaze4);
		App->enemies->SpawnEnemy(kamikaze5);
		App->enemies->SpawnEnemy(kamikaze6);
		App->enemies->SpawnEnemy(kamikaze7);
		App->enemies->SpawnEnemy(kamikaze8);
		shootingkamikazes = false;
		kamikazewaves++;
	}

	if (!shootingkamikazes)
	{
		if (kamikazewaves % 2 == 0)
		{
			shootingkamikazes = true;
			delay = 2000;
		}
		else
		{
			shootingkamikazes = true;
			delay = 1000;
		}
		time2 = SDL_GetTicks();
	}
}