#include "Enemy.h"
#include "ModuleEnemies.h"

class Enemy_Boss_Cannon : public Enemy
{
private:
	Animation idle;
	Animation shooting;

	fPoint original_pos;

	Uint32 time;
	bool shoot = false;

public:
	Enemy_Boss_Cannon(int x, int y, int path);
	void MoveShoot();
};