#include "Enemy.h"
#include "ModuleEnemies.h"

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
	Uint32 time2;
	Path movement;
	Path flyaway;
	Path entering;

	int bullethellwaves = 0;
	bool posreset = false;
	bool posreset1 = false;
	bool bullethell = false;
	bool firstbullethellrow = false;
	bool multipleshooting = false;
	int kamikazewaves = 0;
	bool kamikazeammo = true;
	bool shootingkamikazes = false;
	int delay = 0;
	bool parts = false;

	EnemyInfo kamikaze1;
	EnemyInfo kamikaze2;
	EnemyInfo kamikaze3;
	EnemyInfo kamikaze4;
	EnemyInfo kamikaze5;
	EnemyInfo kamikaze6;
	EnemyInfo kamikaze7;
	EnemyInfo kamikaze8;

	EnemyInfo leftwing;
	EnemyInfo rightwing;
	EnemyInfo cannon;

public:
	Enemy_Boss_Main(int x, int y, int path);
	void MoveShoot();
};

