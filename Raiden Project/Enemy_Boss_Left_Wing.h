#include "Enemy.h"
#include "ModuleEnemies.h"

class Enemy_Boss_Left_Wing : public Enemy
{
private:
	Animation idle;
	Animation shooting;
	Animation closing;

	Uint32 time;
	Uint32 time1;
	fPoint original_pos;
	Path movement;
	Path flyaway;
	Path entering;

	bool shoot = false;
	bool posreset = false;
	bool posreset1 = false;

public:
	Enemy_Boss_Left_Wing(int x, int y, int path);
	void MoveShoot();
};
