#pragma once
#include "Enemy.h"
class Enemy_Medium_Shooter : public Enemy
{
private:
	Animation flyi;
	Animation flyi1;
	Animation flyi2;
	Animation flyi3;
	Animation flys;
	Animation flys1;
	Animation flys2;
	Animation flys3;
	
	iPoint original_pos;
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

public:
	Enemy_Medium_Shooter(int x, int y, int path);
	void MoveShoot();
};

