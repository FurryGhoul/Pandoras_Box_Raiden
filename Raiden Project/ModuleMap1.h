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
	SDL_Texture* Map1;
	SDL_Texture* Road;
	float xmap;
	float ymap;
	float yroad;
	bool setup = true;
	bool changing = false;
	float xscrollspeed = 2.4;
	float yscrollspeed;
	bool won = false;
};

#endif //__MODULEMAP1__