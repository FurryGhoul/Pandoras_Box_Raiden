#include "Enemy.h"
#include "ModuleEnemies.h"

class Enemy_Train_Locomotive : public Enemy
{
private:
	// Normal animation
	Animation flyi;
	Animation flys;

	fPoint original_pos;
	Path movement;
	Path movement1;
	double param;
	double angle;
	bool ne = false;
	bool se = false;
	bool nw = false;
	bool sw = false;
	bool shooting = false;
	bool burst = false;
	bool burst2 = false;
	bool singleburst = false;
	bool singleburst2 = false;
	int shoot_time = 0;
	int shots = 0;

public:
	Enemy_Train_Locomotive(int x, int y, int path);
	void MoveShoot();
};

