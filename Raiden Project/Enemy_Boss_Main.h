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
	Uint32 time3;
	Uint32 time4;
	Path movement;
	Path movement2;
	Path flyaway;
	Path entering;

	int bullethellwaves = 0;
	int shootingwaves = 0;
	int counter = 0;
	bool posreset = false;
	bool posreset1 = false;
	bool bullethell = false;
	bool _shooting = false;
	bool allowshooting = false;
	bool firstbullethellrow = false;
	bool multipleshooting = false;
	int kamikazewaves = 0;
	bool kamikazeammo = true;
	bool shootingkamikazes = false;
	int delay = 0;
	bool parts = false;
	bool orange = false;
	bool alive = true;
	Uint32 orangetime = 0;
	int shadowregulator = 0;

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

