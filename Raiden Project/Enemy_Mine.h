#pragma once
#include "Enemy.h"
class Enemy_Mine: public Enemy
{
public:

	Enemy_Mine(int x, int y, int path);
	void MoveShoot();
private:

	Animation idle;
	Animation to_explode;
	Animation hit;
	Path movement;
	fPoint original_pos;
	int shadowregulator = 0;
	int shadowdirection = 0;

};

