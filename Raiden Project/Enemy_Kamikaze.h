#pragma once
#include "Enemy.h"

class Enemy_Kamikaze : public Enemy
{
private:
	Animation turn;
	Animation turn1;
	fPoint original_pos;
	fPoint vector;
	Path movement;
	double param;
	double angle;
	Uint32 time;
	bool allowtime = true;
	bool colliderrezise = false;

public:

	Enemy_Kamikaze(int x, int y, int path);
	void MoveShoot();
};