#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Init();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation right;
	Animation left;
	Animation right1;
	Animation left1;
	iPoint position;
	bool ideling = false;
	bool allowtime = true;
	int player_w;
	int player_h;
	Uint32 time;
	bool moving = false;
	Collider* Player = nullptr;
};

#endif