#pragma once
#include "Enemy.h"
class Enemy_Train_Coach : public Enemy
{
private:
	// Coach animations
	Animation horizontal;
	Animation diagonal;
	Animation hithorizontal;
	Animation hitdiagonal;

	// Turret animations
	Animation noturret;

	Animation horizontalturret1;
	Animation horizontalturret2;
	Animation horizontalturret3;
	Animation horizontalturret4;
	Animation horizontalturret5;
	Animation horizontalturret6;
	Animation horizontalturret7;
	Animation horizontalturret8;

	Animation hithorizontalturret1;
	Animation hithorizontalturret2;
	Animation hithorizontalturret3;
	Animation hithorizontalturret4;
	Animation hithorizontalturret5;
	Animation hithorizontalturret6;
	Animation hithorizontalturret7;
	Animation hithorizontalturret8;

	Animation diagonalturret1;
	Animation diagonalturret2;
	Animation diagonalturret3;
	Animation diagonalturret4;
	Animation diagonalturret5;
	Animation diagonalturret6;
	Animation diagonalturret7;
	Animation diagonalturret8;

	Animation hitdiagonalturret1;
	Animation hitdiagonalturret2;
	Animation hitdiagonalturret3;
	Animation hitdiagonalturret4;
	Animation hitdiagonalturret5;
	Animation hitdiagonalturret6;
	Animation hitdiagonalturret7;
	Animation hitdiagonalturret8;

	fPoint original_pos;
	Path movement;
		
	double angle;	
	bool shoot = false; // Makes the turret shoot
	int shoot_time = 0;
	int shotphase = 0; // Phase of the shooting animation

public:
	Enemy_Train_Coach(int x, int y, int path);
	void MoveShoot();
};

