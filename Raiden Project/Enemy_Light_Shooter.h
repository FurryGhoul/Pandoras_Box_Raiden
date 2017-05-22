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
	fPoint original_pos;
	Path movement;

	double param;
	double angle;
	bool ne = false;
	bool se = false;
	bool nw = false;
	bool sw = false;
	bool shooting = false;
	int shoot_time = 0;

public:

	Enemy_Light_Shooter(int x, int y, int path);
	void MoveShoot();

};
