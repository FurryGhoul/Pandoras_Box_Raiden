#pragma once
#include "Enemy.h"
//	YOU SHOULD ONLY SPAWN KAMIKAZES IN X 0 OR X 352*3. Depending on the path you can decide the Y
class Light_Shooter_Kamikaze : public Enemy
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
	Animation last_anim;
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
	int time;
	bool time_got = false;
	bool get_vector;
	fPoint vector;
	int follow_time;
	bool once = false;
	bool follow_time_got;
	bool close;
	bool come_right;
public:
	Light_Shooter_Kamikaze(int x, int y, int path, bool pcome_right);
	void MoveShoot();
};

