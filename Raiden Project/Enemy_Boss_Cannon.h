#include "Enemy.h"
#include "ModuleEnemies.h"

class Enemy_Boss_Cannon : public Enemy
{
private:
	Animation idle;
	Animation shooting;

	fPoint original_pos;

	Uint32 time;
	Uint32 time1;
	bool shoot = true;
	bool isshooting = false;
	int shootx = 0;
	int bullets = 0;
public:
	Enemy_Boss_Cannon(int x, int y, int path);
	void MoveShoot();
};