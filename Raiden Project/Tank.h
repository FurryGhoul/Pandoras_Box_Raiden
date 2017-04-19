#pragma once
#include "Enemy.h"
#include "Turret.h"
class Tank: public Enemy
{
private:
	Animation idle;
	iPoint original_pos;
	iPoint distance;
	Path movement;
public:
	Tank(int, int);

	void MoveShoot();
};

