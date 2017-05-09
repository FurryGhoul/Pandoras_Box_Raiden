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
	Animation hit;
	iPoint original_pos;
	iPoint original_pos1;
	iPoint original_pos2;
	iPoint original_pos3;
	Path movement;
	double param;
	double angle;
	bool side = false;
	bool movingsidetoside = false;
	bool shooting = false;
	bool _charge = false;
	int shoot_time = 0;
	int charge_time = 0;
public:
	Enemy_Bonus_Ship(int x, int y, int path);
	void MoveShoot();
};

