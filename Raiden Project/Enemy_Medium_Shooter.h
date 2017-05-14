#pragma once
#include "Enemy.h"
class Enemy_Medium_Shooter : public Enemy
{
private:
	Animation flyi;
	Animation flys;
	Animation flycu;
	Animation flycd;
			
	fPoint original_pos;
	Path movement;
	Path movement1;
	double param;
	double angle;
	bool ne = false;
	bool se = false;
	bool nw = false;
	bool sw = false;
	bool shooting = false;
	int shoot_time = 0;
	int shots = 0;

public:
	Enemy_Medium_Shooter(int x, int y, int path);
	void MoveShoot();
};

