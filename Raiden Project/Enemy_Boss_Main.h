#include "Enemy.h"

class Enemy_Boss_Main : public Enemy
{
private:
	Animation idlewithkamikazes;
	Animation idle;
	Animation opening;
	Animation closing;
	Animation shooting;
	Animation destroyed;

	fPoint original_pos;
	Uint32 time;
	Path movement;
	Path flyaway;
	Path entering;

	bool posreset = false;
	bool posreset1 = false;

public:
	Enemy_Boss_Main(int x, int y, int path);
	void MoveShoot();
};

