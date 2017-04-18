#include "Enemy.h"
#pragma once
class Enemy_Bonus_Ship : public Enemy
{
private:
	Animation flydown;
	Animation flyup;
	Animation idle;
	iPoint original_pos;
	iPoint distance;
	Path movement;
public:
	Enemy_Bonus_Ship(int x, int y);
	void MoveShoot();
};

