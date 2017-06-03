#include "Enemy.h"
#include "ModuleEnemies.h"
#include "ModuleGroundEnemies.h"

class Enemy_Train_Locomotive : public Enemy
{
private:
	// Animations
	Animation horizontal;
	Animation diagonal;
	Animation hithorizontal;
	Animation hitdiagonal;

	fPoint original_pos;
	Path movement;

	//GroundEnemyInfo firstcoach;

	//bool parts = false;

public:
	Enemy_Train_Locomotive(int x, int y, int path);
	void MoveShoot();
};

