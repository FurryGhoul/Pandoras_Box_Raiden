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


	bool multiple_laser;
	int howmuch_lasers;
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
	SDL_Texture* graphics2 = nullptr;
	Animation* current_animation = nullptr;
	Animation* bomb_ammo = nullptr;

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
	Animation bomb1;
	Animation bomb2;
	Animation bomb3;
	Animation bomb4;
	Animation bomb5;
	Animation bomb6;
	iPoint position;
	int bombs;
	Uint32 bombtime;
	int bombammo_w;
	int font_score = -1;
	char score_text[20];
	char scoret[20];
	char highscore_text[20];
	char lastscore_text[20];
	char lastscoret[20];
	char highscoret[20];
	uint hiscore = 0;
	uint lastscore = 0;
	int score = 0;
	// Animation
	bool ideling = false;
	bool allowtime = true;
	bool allowtimep = true;
	bool moving = false;
	bool propeller = true;
	Uint32 time;
	Uint32 timep; //time for propellers

	int player_w;
	int player_h;
	bool godmode = false; // To know if the godmode is on or not
	bool deadplayer = false; // To know if player is dead or not
	bool allowhiscore = true;

	Collider* Player = nullptr;
	Collider* Playergod = nullptr;
	int powerup_level = 0; // To know which level is the powerup at
	bool red = true; //To know if the powerup is blue or red

};

#endif