#ifndef __ModuleEnemy_H__
#define __ModuleEnemy_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleEnemy : public Module
{
public:
	ModuleEnemy();
	~ModuleEnemy();

	bool Init();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation right;
	Animation left;
	iPoint position;
	bool ideling = false;
	int enemy_w = 23*3-2;
	int enemy_h = 30*2;
	bool moving = false;
	Collider* Enemy = nullptr;
};

#endif