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
	Animation idle2;
	Animation idle3;

	iPoint original_pos;
	iPoint distance;
	Path movement;
	double param;
	double angle;

public:
	RedUp(int x, int y);
};

