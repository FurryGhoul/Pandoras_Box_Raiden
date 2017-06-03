#include "Enemy.h"

class Enemy_Megatank : public Enemy
{
private:
	Animation spinning;
	Animation decelaration;
	Animation idle;
	Animation hit;

	Animation dmgspinning;
	Animation dmgdecelaration;

	fPoint original_pos;

	Path movement;

	int charge = 100;
	bool spin = false;
	bool slow = false;
	bool stop = false;

public:
	Enemy_Megatank(int x, int y, int path);
	void MoveShoot();
};

