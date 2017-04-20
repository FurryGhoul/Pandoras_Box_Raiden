#include "Tank.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>


Tank::Tank(int x, int y) : Enemy(x, y)
{
	
	spriteshit = 2;
	animations = 2;
	downup.PushBack({ 2, 4, 24, 26 });
	w = 24 * 3;
	h = 26 * 3;


	original_pos.x = x;
	original_pos.y = -50;


	
	movement.PushBack({ -0.5f, 2.0f }, 50);
	collider = App->collision->AddCollider({ 0, 0, 24 * 3 - 5, 26 * 3 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}


void Tank::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
	animation = &downup;
}
