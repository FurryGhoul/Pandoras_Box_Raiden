#pragma once
#include "Enemy.h"
#include "Tank.h"
class Turret: public Enemy
{
public:
	Turret(int, int);
	void MoveShoot();
};

