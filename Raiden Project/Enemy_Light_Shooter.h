#include "Enemy.h"
class Enemy_Light_Shooter : public Enemy
{
private:
	Animation fly;
	iPoint original_pos;
	iPoint distance;
	Path movement;
	bool shooting = false;
public:

	Enemy_Light_Shooter(int x, int y);
	void MoveShoot();

};
