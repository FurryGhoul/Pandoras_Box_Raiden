#pragma once
#include "Enemy.h"
class Enemy_Ship : public Enemy
{
public:
	// Ship
	Animation down;

	// Door
	Animation semiopen;
	Animation open;
	Animation nodoor;

	// Water waves
	Animation water1;
	Animation water2;
	Animation water3;
	
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
	int shotphase = 0;
	int water = 0;
	int waterrepeat = 0;

public:
	Enemy_Ship(int x, int y, int path);
	void MoveShoot();
};

