#include "Enemy.h"

class Enemy_Megatank : public Enemy
{
private:
	Animation spinning;
	Animation idle;
	Animation hit;

	fPoint original_pos;

	Path movement;

	int charge = 0;

public:
	Enemy_Megatank(int x, int y, int path);
	void MoveShoot();
};

