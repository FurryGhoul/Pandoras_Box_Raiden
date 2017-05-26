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
	Animation hitsides;
	Animation hitdown;
	fPoint original_pos;
	fPoint original_pos1;
	fPoint original_pos2;
	fPoint original_pos3;
	Path movement;
	double param;
	double angle;
	bool side = false;
	bool change = false;
	bool movingsidetoside = false;
	bool shooting = false;
	bool _charge = false;
	int shoot_time = 0;
public:
	Enemy_Bonus_Ship(int x, int y, int path);
	void MoveShoot();
};

