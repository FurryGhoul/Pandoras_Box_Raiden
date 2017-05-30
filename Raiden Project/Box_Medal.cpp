#include "Box_Medal.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"

Box_Medal::Box_Medal(int x, int y, int path) : Enemy(x, y)
{
	hp = 1;
	points = 100;
	medalbox = true;
	
	
	idle.PushBack({ 1, 1, 27, 25 });
	invisible.PushBack({ 0, 0, 1, 1 });

	movement.PushBack({ 0.0f, 1.0f }, 100);

	collider = App->collision->AddCollider({ 0, 0, 27 * 3 - 5, 24 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->genemies);

	spritesheet = 4;
	animations = 1;

	original_pos.x = x;
	original_pos.y = -100;

	if (path == 0)
		animation = &idle;
	if (path == 1)
		animation = &invisible;
}

void Box_Medal::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
	position.x += left_right_mod;

	w = 27 * 3;
	h = 25 * 3;
		
}