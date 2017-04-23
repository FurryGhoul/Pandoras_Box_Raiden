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
	void InitialPos()
	{
		position.x = 405;
		position.y = 620;
	}

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
	int font_score = -1;
	char score_text[10];
	char highscore_text[10];
	char lastscore_text[10];
	char lastscoret[10];
	char highscore[10];
	uint hiscore = 0;
	uint score = 0;
	uint lastscore = 0;
	bool ideling = false;
	bool allowtime = true;
	bool allowtimep = true;
	bool propeller = true;
	int player_w;
	int player_h;
	bool moving = false;
	bool godmode = false;
	bool deadplayer = false;
	bool allowhiscore = true;
	Uint32 time;
	Uint32 timep; //time for propellers
	Collider* Player = nullptr;
	int powerup_level = 0;

};

#endif