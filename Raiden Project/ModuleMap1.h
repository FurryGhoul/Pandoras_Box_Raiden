#ifndef __MODULEMAP1__
#define __MODULEMAP1__
#include "Globals.h"
#include "Module.h"
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )


class ModuleMap1 : public Module
{
public:
	ModuleMap1();
	~ModuleMap1();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	SDL_Rect ground;
	SDL_Rect road;
	SDL_Rect buildings;
	SDL_Texture* Map1;
	SDL_Texture* Road;
	SDL_Texture* Buildings;
	float xmap;
	float ymap;
	float yroad;
	bool setup = true;
	bool changing = false;
	float xscrollspeed = 2.4;
	float yscrollspeed = 1;
	bool road1 = false;
	bool roadmoved = false;
	bool won = false;
	int checkpoint = 0;
	bool one_player = true;
	bool setdown = false;
	bool reset_collision = false;
	int initial_dead_time = 0;
	bool initial_dead_time_got = false;
	int initial_time_win = 0;
	bool initial_time_win_got = false;
	bool cheat_win = false;
	int powerup_kept = 0;
	bool leftwingalive = true;
	bool rightwingalive = true;
	bool cannonalive = true;

};

#endif //__MODULEMAP1__