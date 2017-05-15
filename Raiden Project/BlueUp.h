#pragma once
#include "PowerUp.h"
class BlueUp : public PowerUp
{
private:
	Animation idle1;


	
	fPoint original_pos;
	fPoint pos_mod;
	Path movement;
	double radius;



public:
	BlueUp(int x, int y, double pcenterx = 0, double pcentery = 0, double angle = 0, bool first = true);
	void Move();
};



