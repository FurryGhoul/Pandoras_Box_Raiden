#pragma once
#include "PowerUp.h"
class BlueUp : public PowerUp
{
private:
	Animation idle1;


	fPoint original_pos;
	fPoint distance;
	Path movement;
	double param;
	double angle;

public:
	BlueUp(int x, int y);
	void Move();
};



