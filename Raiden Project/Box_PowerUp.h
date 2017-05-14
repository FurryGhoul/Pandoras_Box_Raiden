#pragma once
#include "Enemy.h"

class Box_PowerUp : public Enemy
{
private:
	Animation idle;

	fPoint original_pos;
	fPoint distance;
	Path movement;

public:
	Box_PowerUp(int x, int y, int path);
	void MoveShoot();
};