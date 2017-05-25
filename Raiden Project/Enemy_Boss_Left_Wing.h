#include "Enemy.h"
#include "ModuleEnemies.h"

class Enemy_Boss_Left_Wing : public Enemy
{
private:
	Animation idle;
	Animation shooting;
	Animation closing;

	fPoint original_pos;

	Uint32 time;
	bool shoot = false;

public:
	Enemy_Boss_Left_Wing(int x, int y, int path);
	void MoveShoot();
};