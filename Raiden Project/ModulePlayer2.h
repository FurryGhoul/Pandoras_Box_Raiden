#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Init();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;

	//animations with the small propeller.
	Animation idle;
	Animation right;
	Animation left;
	Animation right1;
	Animation left1;
	//animations with the big propeller.
	Animation idlep;
	Animation rightp;
	Animation leftp;
	Animation right1p;
	Animation left1p;
	iPoint position;
	bool ideling = false;
	bool allowtime = true;
	bool allowtimep = true;
	bool propeller = true;
	int player_w;
	int player_h;
	bool moving = false;
	bool godmode = false;
	bool deadplayer = false;
	Uint32 time;
	Uint32 timep; //time for propellers
	Collider* Player = nullptr;

};

#endif