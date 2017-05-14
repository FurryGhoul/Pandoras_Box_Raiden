#pragma once
#include "PowerUp.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

class Medals : public PowerUp
{
private:
	Animation idle1;
	Animation idle2;
	Animation idle3;

	fPoint original_pos;
	fPoint distance;
	Path movement;
	//double param;
	//double angle;

public:
	Medals(int x, int y);
	void Move();
};

