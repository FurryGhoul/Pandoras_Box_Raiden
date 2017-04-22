#include "Enemy.h"
#pragma once
class Enemy_Bonus_Ship : public Enemy
{
private:
	Animation flydown;
	Animation flysides;
	Animation stop;
	Animation propeller;
	Animation none;
	Animation charge;
	iPoint original_pos;
	iPoint original_pos1;
	iPoint original_pos2;
	Path movement;
	bool side = false;
	bool shooting = false;
public:
	Enemy_Bonus_Ship(int x, int y);
	void MoveShoot();
};

