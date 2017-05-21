#pragma once
#include "Enemy.h"
class Enemy_Ship : public Enemy
{
public:
	// Ship
	Animation down;
	Animation hitdown;
	Animation hitdown1;

	// Door
	Animation semiopen;
	Animation open;
	Animation nodoor;

	Animation hitsemiopen;
	Animation hitopen;

	Animation hitsemiopen1;
	Animation hitopen1;

	// Water waves
	Animation waterdown1;
	Animation waterdown2;
	Animation waterdown3;
	
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
	bool shoot = false; // Makes the ship shoot
	int shoot_time = 0;
	int shotphase = 0; // Phase of the shooting animation
	int water = 0;
	int waterrepeat = 0;

public:
	Enemy_Ship(int x, int y, int path);
	void MoveShoot();
};

