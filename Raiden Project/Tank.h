#pragma once
#include "Enemy.h"
#include "Turret.h"
class Tank: public Enemy
{
private:
	Animation downup;
	Animation leftright;
	Animation neutraldiagonalleft;
	Animation downdiagonalleft;
	Animation updiagonalleft;
	Animation neutraldiagonalright;
	Animation downdiagonalright;
	Animation updiagonalright;
	iPoint original_pos;
	iPoint distance;
	Path movement;
public:
	Tank(int, int);

	void MoveShoot();
};

