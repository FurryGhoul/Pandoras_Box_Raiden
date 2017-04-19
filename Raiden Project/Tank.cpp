#include "Tank.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>


Tank::Tank(int x, int y) : Enemy(x, y)
{
	/*
	spriteshit = 3;
	idle.PushBack[2, 4, 24, 26];
	original_pos.x = x;
	original_pos.y = -50;

	movement.PushBack({ -0.05f, 0 }, 50);*/
}


void Tank::MoveShoot()
{
	position = original_pos + movement.GetCurrentPosition();
}
