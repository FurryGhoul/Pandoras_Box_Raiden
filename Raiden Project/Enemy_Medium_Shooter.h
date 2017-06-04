#pragma once
#include "Enemy.h"
class Enemy_Medium_Shooter : public Enemy
{
private:
	// Normal animation
	Animation flyi;
	Animation flys;
	Animation flycu;
	Animation flycd;

	// Hit animation
	Animation hitflyi;
	Animation hitflys;
	Animation hitflycu;
	Animation hitflycd;

	Animation hitflyi1;
	Animation hitflys1;
	Animation hitflycu1;
	Animation hitflycd1;
			
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
	bool burst = false;
	bool burst2 = false;
	bool singleburst = false;
	bool singleburst2 = false;
	int shoot_time = 0;
	int shots = 0;
	int shadowregulator = 0;
	int shadowdirection = 0;

public:
	Enemy_Medium_Shooter(int x, int y, int path);
	void MoveShoot();
};

