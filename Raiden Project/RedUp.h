#pragma once
#include "PowerUp.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

class RedUp : public PowerUp
{
private:
	Animation idle1;

	fPoint original_pos;
	fPoint pos_mod;
	Path movement;
	double radius;



public:
	RedUp(int x, int y, double pcenterx = 0, double pcentery = 0, double pangle= 0, bool first = true);
	void Move();
};

