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

	//EnemyInfo kamikaze1;
	//EnemyInfo kamikaze2;
	//EnemyInfo kamikaze3;
	//EnemyInfo kamikaze4;
	//EnemyInfo kamikaze5;
	//EnemyInfo kamikaze6;
	//EnemyInfo kamikaze7;
	//EnemyInfo kamikaze8;

public:
	Enemy_Boss_Main(int x, int y, int path);
	void MoveShoot();
};

