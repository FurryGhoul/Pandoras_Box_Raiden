#include "Enemy.h"
class Enemy_Light_Shooter : public Enemy
{
private:
	Animation flys;
	Animation flyn;
	Animation flye;
	Animation flyw;
	Animation flyse1;
	Animation flyne1;
	Animation flysw1;
	Animation flynw1;
	Animation flyse2;
	Animation flyne2;
	Animation flysw2;
	Animation flynw2;
	Animation flyse3;
	Animation flyne3;
	Animation flysw3;
	Animation flynw3;
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
