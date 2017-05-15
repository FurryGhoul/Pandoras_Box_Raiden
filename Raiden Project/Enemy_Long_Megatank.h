
#include "Enemy.h"
class Enemy_Long_Megatank : public Enemy
{
private:
	Animation shellstart;
	Animation transformation;
	Animation finalform;
	Animation stop;

	fPoint original_pos;

	Path movement;

	int shoot_time = 0;
	bool shooting = false;
public:
	Enemy_Long_Megatank(int x, int y, int path);

	void MoveShoot();
};

