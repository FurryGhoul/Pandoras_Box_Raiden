#pragma once
#include "PowerUp.h"
class BlueUp : public PowerUp
{
private:
	Animation idle1;


	iPoint original_pos;
	iPoint distance;
	Path movement;
	double param;
	double angle;

public:
	BlueUp(int x, int y);
	void Move();
};



