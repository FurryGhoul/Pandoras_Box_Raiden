#include "Box_PowerUp.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleGroundEnemies.h"

Box_PowerUp::Box_PowerUp(int x, int y, int path) : Enemy(x, y)
{
	hp = 1;
	points = 100;
	powerupbox = true;


	idle.PushBack({ 31, 1, 27, 25 });

	movement.PushBack({ 0.0f, 1.0f }, 100);

	collider = App->collision->AddCollider({ 0, 0, 27 * 3 - 5, 24 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->genemies);

	spritesheet = 4;
	animations = 1;

	original_pos.x = x;
	original_pos.y = -100;

}

void Box_PowerUp::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
	position.x += left_right_mod;

	w = 27 * 3;
	h = 25 * 3;

	animation = &idle;
}