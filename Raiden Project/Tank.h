#pragma once
#include "Enemy.h"
#include "Turret.h"
class Tank: public Enemy
{
private:
	//Tank animations
	Animation downup;
	Animation leftright;
	Animation neutraldiagonalleft;
	Animation downdiagonalleft;
	Animation updiagonalleft;
	Animation neutraldiagonalright;
	Animation downdiagonalright;
	Animation updiagonalright;

	//Turret animations
	Animation s;
	Animation n;
	Animation e;
	Animation w11;
	Animation se1;
	Animation ne1;
	Animation sw1;
	Animation nw1;
	Animation se2;
	Animation ne2;
	Animation sw2;
	Animation nw2;
	Animation se3;
	Animation ne3;
	Animation sw3;
	Animation nw3;
	double param;
	double angle;
	bool ne = false;
	bool se = false;
	bool nw = false;
	bool sw = false;
	bool shooting = false;

	
	
	


	iPoint original_pos;
	
	Path movement;
public:
	Tank(int, int);

	void MoveShoot();
};

