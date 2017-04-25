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
	void InitialPos()
	{
		position.x = 205;
		position.y = 620;
	}
	void MidPos()
	{
		position.x = 300;
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
	char score_text[20];
	char scoret[20];
	char highscore_text[20];
	char lastscore_text[20];
	char lastscoret[20];
	char highscoret[20];
	int score = 0;
	uint hiscore = 0;
	uint lastscore;
	bool ideling = false;
	bool allowtime = true;
	bool allowtimep = true;
	bool propeller = true;
	int player_w;
	int player_h;
	bool allowhiscore = true;
	bool moving = false;
	bool godmode = false;
	bool deadplayer = false;
	Uint32 time;
	Uint32 timep; //time for propellers
	Collider* Player = nullptr;
	Collider* Playergod = nullptr;
	int powerup_level = 0;

};

#endif