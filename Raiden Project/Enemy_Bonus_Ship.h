#include "Enemy.h"
#pragma once
class Enemy_Bonus_Ship : public Enemy
{
private:
	Animation flydown;
	Animation flysides;
	Animation stop;
	iPoint original_pos;
	iPoint distance;
	Path movement;
	bool side = false;
public:
	Enemy_Bonus_Ship(int x, int y);
	void MoveShoot();
};

