#pragma once
#include "Enemy.h"
#include "Turret.h"

class Enemy_Ship_Tank : public Enemy
{
private:
	//Ship_Tank animations
	Animation up;
	Animation down;
	Animation left;
	Animation right;

	//Ship_Tank hit animations
	Animation hitup;
	Animation hitdown;
	Animation hitleft;
	Animation hitright;

	Animation hitup1;
	Animation hitdown1;
	Animation hitleft1;
	Animation hitright1;

	//Water animations
	Animation waterup1;
	Animation waterup2;
	Animation waterup3;
	Animation waterdown1;
	Animation waterdown2;
	Animation waterdown3;
	Animation waterleft1;
	Animation waterleft2;
	Animation waterleft3;
	Animation waterright1;
	Animation waterright2;
	Animation waterright3;

	//Turret animations
	Animation noturret;
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

	//Turret hit animations
	Animation hits;
	Animation hitn;
	Animation hite;
	Animation hitw11;
	Animation hitse1;
	Animation hitne1;
	Animation hitsw1;
	Animation hitnw1;
	Animation hitse2;
	Animation hitne2;
	Animation hitsw2;
	Animation hitnw2;
	Animation hitse3;
	Animation hitne3;
	Animation hitsw3;
	Animation hitnw3;
	double param;
	double angle;
	bool ne = false;
	bool se = false;
	bool nw = false;
	bool sw = false;
	bool turretalive = true; // Bool to see if the turret is still alive
	int shooting = 0;
	int time_controll = 0;
	int water = 0;
	int waterrepeat = 0;


	fPoint original_pos;

	Path movement;
public:
	Enemy_Ship_Tank(int x, int y, int path);
	void MoveShoot();
};