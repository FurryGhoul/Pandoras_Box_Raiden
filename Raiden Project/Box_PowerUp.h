#pragma once
#include "Enemy.h"

class Box_PowerUp : public Enemy
{
private:
	Animation idle;

	iPoint original_pos;
	iPoint distance;
	Path movement;

public:
	Box_PowerUp(int x, int y, int path);
	void MoveShoot();
};