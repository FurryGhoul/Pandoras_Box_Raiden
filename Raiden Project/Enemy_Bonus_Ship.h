#include "Enemy.h"
#pragma once
class Enemy_Bonus_Ship : public Enemy
{
private:
	Animation flydown;
	Animation flysides;
	Animation stop;
	Animation propeller;
	iPoint original_pos;
	iPoint original_pos1;
	Path movement;
	bool side = false;
public:
	Enemy_Bonus_Ship(int x, int y);
	void MoveShoot();
};

