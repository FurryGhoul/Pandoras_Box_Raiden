#pragma once
#include "Enemy.h"

class Enemy_Kamikaze : public Enemy
{
private:
	Animation turn;
	Animation turn1;
	Animation deploying;
	Animation deploying1;
	fPoint original_pos;
	fPoint vector;
	Path movement;
	double param;
	double angle;
	bool bosskamikaze = false;
	Uint32 time;
	Uint32 time2;
	int delay = 0;
	bool allowtime = true;
	bool colliderrezise = false;

public:

	Enemy_Kamikaze(int x, int y, int path);
	void MoveShoot();
};