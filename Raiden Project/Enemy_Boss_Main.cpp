#include "Enemy_Boss_Main.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"
#include "ModuleMap1.h"
#include "ModuleShadows.h"

Enemy_Boss_Main::Enemy_Boss_Main(int x, int y, int path) : Enemy(x, y)
{
	hp = 1300;
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
	opening.loop = false;
	opening.speed = 0.1f;
	//Closing
	closing.PushBack({ 486, 27, 96, 53 });
	closing.PushBack({ 389, 27, 96, 53 });
	closing.PushBack({ 292, 27, 96, 53 });
	closing.PushBack({ 195, 27, 96, 53 });
	closing.PushBack({ 98, 27, 96, 53 });
	closing.PushBack({ 1, 27, 96, 53 });
	closing.loop = false;
	closing.speed = 0.1f;
	//Shooting
	shooting.PushBack({ 98, 92, 96, 53 });
	shooting.PushBack({ 195, 92, 96, 53 });
	shooting.PushBack({ 292, 92, 96, 53 });
	shooting.PushBack({ 98, 92, 96, 53 });
	shooting.PushBack({ 195, 92, 96, 53 });
	shooting.PushBack({ 98, 92, 96, 53 });
	shooting.loop = false;
	//Destroyed
	destroyed.PushBack({ 583, 27, 96, 53 });
	destroyed.loop = false;

	//Path
	//Entering
	movement.PushBack({ 0.0f, 1.5f }, 300);
	//Movement
	movement.PushBack({ 1.5f, 0.0f }, 80); movement.PushBack({ -1.5f, 0.0f }, 160); movement.PushBack({ 1.5f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 1.5f }, 30); movement.PushBack({ 0.0f, -1.5f }, 80); movement.PushBack({ -1.5f, 0.0f }, 80);
	movement.PushBack({ 1.5f, 0.0f }, 160); movement.PushBack({ -1.5f, 0.0f }, 80); movement.PushBack({ 0.0f, 1.5f }, 60);

	movement.PushBack({ 1.5f, 0.0f }, 80); movement.PushBack({ -1.5f, 0.0f }, 160); movement.PushBack({ 1.5f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 1.5f }, 30); movement.PushBack({ 0.0f, -1.5f }, 80); movement.PushBack({ -1.5f, 0.0f }, 80);
	movement.PushBack({ 1.5f, 0.0f }, 160); movement.PushBack({ -1.5f, 0.0f }, 80); movement.PushBack({ 0.0f, 1.5f }, 60);

	movement.PushBack({ 1.5f, 0.0f }, 80); movement.PushBack({ -1.5f, 0.0f }, 160); movement.PushBack({ 1.5f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 1.5f }, 30); movement.PushBack({ 0.0f, -1.5f }, 80); movement.PushBack({ -1.5f, 0.0f }, 80);
	movement.PushBack({ 1.5f, 0.0f }, 160); movement.PushBack({ -1.5f, 0.0f }, 80); movement.PushBack({ 0.0f, 1.5f }, 60);

	movement.PushBack({ 1.5f, 0.0f }, 80); movement.PushBack({ -1.5f, 0.0f }, 160); movement.PushBack({ 1.5f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 1.5f }, 30); movement.PushBack({ 0.0f, -1.5f }, 80); movement.PushBack({ -1.5f, 0.0f }, 80);
	movement.PushBack({ 1.5f, 0.0f }, 160); movement.PushBack({ -1.5f, 0.0f }, 80); movement.PushBack({ 0.0f, 1.5f }, 60);

	movement.PushBack({ 1.5f, 0.0f }, 80); movement.PushBack({ -1.5f, 0.0f }, 160); movement.PushBack({ 1.5f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 1.5f }, 30); movement.PushBack({ 0.0f, -1.5f }, 80); movement.PushBack({ -1.5f, 0.0f }, 80);
	movement.PushBack({ 1.5f, 0.0f }, 160); movement.PushBack({ -1.5f, 0.0f }, 80); movement.PushBack({ 0.0f, 1.5f }, 60);

	movement.PushBack({ 1.5f, 0.0f }, 80); movement.PushBack({ -1.5f, 0.0f }, 160); movement.PushBack({ 1.5f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 1.5f }, 30); movement.PushBack({ 0.0f, -1.5f }, 80); movement.PushBack({ -1.5f, 0.0f }, 80);
	movement.PushBack({ 1.5f, 0.0f }, 160); movement.PushBack({ -1.5f, 0.0f }, 80); movement.PushBack({ 0.0f, 1.5f }, 60);

	movement.PushBack({ 1.5f, 0.0f }, 80); movement.PushBack({ -1.5f, 0.0f }, 160); movement.PushBack({ 1.5f, 0.0f }, 80);
	movement.PushBack({ 0.0f, 1.5f }, 30); movement.PushBack({ 0.0f, -1.5f }, 80); movement.PushBack({ -1.5f, 0.0f }, 80);
	movement.PushBack({ 1.5f, 0.0f }, 160); movement.PushBack({ -1.5f, 0.0f }, 80); movement.PushBack({ 0.0f, 1.5f }, 60);

	movement.PushBack({ 1.5f, 0.0f }, 80); movement.PushBack({ -1.5f, 0.0f }, 160); movement.PushBack({ 1.5f, 0.0f }, 80);
	//Flying away
	movement.PushBack({ 0.0f, 1.5f }, 30); movement.PushBack({ 0.0f, -1.5f }, 80); movement.PushBack({ 0.0f, 3.0f }, 10000);

	//After death
	movement2.PushBack({ 0.0f, 0.0f }, 100);
	movement2.PushBack({ 0.0f, 0.1f }, 1000);
	

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
	original_pos.y = -250;
	time = SDL_GetTicks();
	animation = &idlewithkamikazes;
}


void Enemy_Boss_Main::MoveShoot()
{
	if (position.y >= 850)
		App->map_1->won = true;

	if (shadowregulator % 2 == 0)
	{
		if (hp > 0)
			App->shadows->AddShadow(App->shadows->bossmain, position.x, position.y, (139 - 30) * 3, 59 * 3);
		if (App->map_1->leftwingalive)
			App->shadows->AddShadow(App->shadows->bossleftwing, position.x, position.y, (125 - 30) * 3, 72 * 3);
		if (App->map_1->rightwingalive)
			App->shadows->AddShadow(App->shadows->bossrightwing, position.x, position.y, (182 - 30) * 3, 72 * 3);
		if (App->map_1->cannonalive)
			App->shadows->AddShadow(App->shadows->bosscannon, position.x, position.y, (154 - 30) * 3, 75 * 3);
	}
	shadowregulator++;

	if (alive == true)
	{
 		position = original_pos + movement.GetCurrentPosition();
		position.x += left_right_mod;
	}

	else if (alive == false)
	{
		position += movement2.GetCurrentPosition();
	}

	App->enemies->SetPos();

	//Boss parts
	if (!parts)
	{
		App->enemies->SpawnEnemy(leftwing);
		App->enemies->SpawnEnemy(rightwing);
		App->enemies->SpawnEnemy(cannon);
		parts = true;
	}

	App->enemies->SetPos();

	//Shooting kamikazes
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
		if (kamikazewaves >= 13)
		{
			kamikazeammo = false;
			animation = &idle;
			multipleshooting = true;
			time = SDL_GetTicks();
		}
	}

	if (kamikazeammo && (SDL_GetTicks() - time) > 2500 && shootingkamikazes && (SDL_GetTicks() - time2) > delay && alive == true)
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

	//Shooting bullet hell
	if (!kamikazeammo && !bullethell && !firstbullethellrow && SDL_GetTicks() - time >= 3000)
	{
		firstbullethellrow = true;
		bullethell = true;
	}

	if (bullethell)
	{
		time = SDL_GetTicks();
		animation = &opening;
		closing.Reset();

		if (opening.Finished() && alive == true)
		{
			if (bullethellwaves == 0)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 0, -12);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -9, -6, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 9, -6, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -9, 6, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 9, 6, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 0, 12, false, true);
				bullethellwaves++;
				time2 = SDL_GetTicks();
			}
			if (SDL_GetTicks() - time2 >= 300 && bullethellwaves == 1)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -3, -12);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 9, -3, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -9, -3, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 9, 3, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 3, 12, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -9, 3, false, true);
				bullethellwaves++;
			}
			if (SDL_GetTicks() - time2 >= 600 && bullethellwaves == 2)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -9, -12);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 3, -12, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -12, 0, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 12, 0, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -3, 12, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 9, 12, false, true);
				bullethellwaves++;
			}
			if (SDL_GetTicks() - time2 >= 900 && bullethellwaves == 3)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 3, -12);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -3, 12, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -9, 9, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 12, -3, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -12, 3, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 9, 9, false, true);
				bullethellwaves++;
			}
			if (SDL_GetTicks() - time2 >= 1200 && bullethellwaves == 4)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 0, -12);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -9, -6, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 9, -6, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -9, 6, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 9, 6, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 0, 12, false, true);
				bullethellwaves++;
			}
			if (SDL_GetTicks() - time2 >= 1500 && bullethellwaves == 5)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -3, -12);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 9, -3, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -9, -3, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 9, 3, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 3, 12, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -9, 3, false, true);
				bullethellwaves++;
			}
			if (SDL_GetTicks() - time2 >= 1800 && bullethellwaves == 6)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -9, -12);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 3, -12, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -12, 0, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 12, 0, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -3, 12, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 9, 12, false, true);
				bullethellwaves++;
			}
			if (SDL_GetTicks() - time2 >= 2100 && bullethellwaves == 7)
			{
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 3, -12);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -3, 12, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -9, 9, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 12, -3, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, -12, 3, false, true);
				App->particles->AddParticle(App->particles->longmegatank_laser, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, 9, 9, false, true);

				animation = &closing;
				time3 = SDL_GetTicks();
				opening.Reset();
				bullethell = false;
				bullethellwaves = 0;
				allowshooting = true;
			}
		}
	}

	if (!kamikazeammo && !bullethell && SDL_GetTicks() - time >= 9000)
		bullethell = true;

	if (!kamikazeammo && !_shooting && SDL_GetTicks() - time3 >= 4000 && allowshooting)
		_shooting = true;

	if (_shooting && alive == true)
	{
		animation = &shooting;

		if (shootingwaves == 0) //first
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 9, 3);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -9, 3, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 9, 3, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -9, 3, false, true);

			shootingwaves++;
			time4 = SDL_GetTicks();
		}
		if (SDL_GetTicks() - time4 >= 200 && shootingwaves == 1)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 8, 5);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -8, 5, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 8, 5, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -8, 5, false, true);

			shootingwaves++;
		}
		if (SDL_GetTicks() - time4 >= 400 && shootingwaves == 2)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 9, 4);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -9, 4, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 9, 4, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -9, 4, false, true);

			shootingwaves++;
		}
		if (SDL_GetTicks() - time4 >= 600 && shootingwaves == 3)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 6, 8);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -6, 8, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 6, 8, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -6, 8, false, true);

			shootingwaves++;
		}
		if (SDL_GetTicks() - time4 >= 800 && shootingwaves == 4)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 5, 9);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -5, 9, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 5, 9, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -5, 9, false, true);

			shootingwaves++;
		}
		if (SDL_GetTicks() - time4 >= 1000 && shootingwaves == 5)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 4, 9);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -4, 9, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 4, 9, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -4, 9, false, true);

			shootingwaves++;
		}
		if (SDL_GetTicks() - time4 >= 1200 && shootingwaves == 6)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 7, 7);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -7, 7, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 7, 7, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -7, 7, false, true);

			shootingwaves++;
		}
		if (SDL_GetTicks() - time4 >= 1400 && shootingwaves == 7)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -3, 9);

			shootingwaves++;
		}
		if (SDL_GetTicks() - time4 >= 1600 && shootingwaves == 8)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 3, 9);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -3, 9, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -3, 9, false, true);

			shootingwaves++;
		}
		if (SDL_GetTicks() - time4 >= 1800 && shootingwaves == 9)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 4, 9);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -4, 9, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 4, 9, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -4, 9, false, true);

			shootingwaves++;
		}
		if (SDL_GetTicks() - time4 >= 2000 && shootingwaves == 10)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 3, 9);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -3, 9, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 3, 9, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -3, 9, false, true);

			shootingwaves++;
		}
		if (SDL_GetTicks() - time4 >= 2200 && shootingwaves == 11)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 9, 3);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -9, 3, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 9, 3, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -9, 3, false, true);

			shootingwaves++;
		}
		if (SDL_GetTicks() - time4 >= 2400 && shootingwaves == 12) //last
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 10, 3);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 - 80, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -10, 3, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, 10, 3, false, true);
			App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2 + 100, position.y + h - 30, COLLIDER_ENEMY_SHOT, 0, -10, 3, false, true);
			
			animation = &idle;
			_shooting = false;
			allowshooting = false;
			shooting.Reset();
			shootingwaves = 0;
		}
	}

	if (ishit && modifier != 301)
	{
		modifier = 301;
		hittime = SDL_GetTicks();
	}
	if (ishit && SDL_GetTicks() - hittime >= 100)
	{
		modifier = 0;
		ishit = false;
	}

	if (orange && modifier != 534 && SDL_GetTicks() - orangetime >= 200)
	{
		modifier = 534;
		orangetime = SDL_GetTicks();
	}
	if (orange && SDL_GetTicks() - orangetime >= 200)
	{
		modifier = 0;
		orangetime = SDL_GetTicks();
	}

	if (hp <= 125)
		orange = true;

	if (hp <= 0)
	{
		alive = false;
  		animation = &destroyed;
		counter++;
		
		points = 0;

		collider->type = COLLIDER_NONE;
	
		if (counter == 10)
		{
			App->particles->AddParticle(App->particles->bonusmedium_explosion, position.x - 50, position.y, COLLIDER_NONE);
		}
		if (counter == 20)
		{
			App->particles->AddParticle(App->particles->bonusmedium_explosion, position.x, position.y + 50, COLLIDER_NONE);
		}
		if (counter == 30)
		{
			App->particles->AddParticle(App->particles->bonusmedium_explosion, position.x + 100, position.y, COLLIDER_NONE);
		}
		if (counter == 40)
		{
			App->particles->AddParticle(App->particles->bonusmedium_explosion, position.x + 75, position.y - 75, COLLIDER_NONE);
		}
		if (counter == 50)
		{
			App->particles->AddParticle(App->particles->bonusmedium_explosion, position.x + 50, position.y - 20, COLLIDER_NONE);
		}
		if (counter == 60)
		{
			App->particles->AddParticle(App->particles->bonusmedium_explosion, position.x + 30, position.y - 60, COLLIDER_NONE);
			App->particles->AddParticle(App->particles->bonusmedium_explosion, position.x + 60, position.y, COLLIDER_NONE);
		}
		if (counter == 70)
		{
			App->particles->AddParticle(App->particles->bonusmedium_explosion, position.x, position.y - 75, COLLIDER_NONE);
		}
		if (counter == 71)
		{
			counter = 1;
		}
	}

}