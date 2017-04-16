#include "Enemy.h"
class Enemy_Light_Shooter : public Enemy
{
private:
	Animation flys;
	Animation flyn;
	Animation flye;
	Animation flyw;
	Animation flyse;
	Animation flyne;
	Animation flysw;
	Animation flynw;
	iPoint original_pos;
	iPoint distance;
	Path movement;
	double param;
	double angle;
	bool ne = false;
	bool se = true;
	bool nw = false;
	bool sw = false;
	bool shooting = false;

public:

	Enemy_Light_Shooter(int x, int y);
	void MoveShoot();

};
