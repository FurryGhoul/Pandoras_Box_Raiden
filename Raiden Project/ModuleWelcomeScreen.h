#ifndef __MODULEWELCOMESCREEN__
#define __MODULEWELCOMESCREEN__
#include "Globals.h"
#include "Module.h"
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )


class ModuleWelcomeScreen : public Module
{
public:
	ModuleWelcomeScreen();
	~ModuleWelcomeScreen();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	SDL_Rect ground;
	SDL_Texture *Welcome;
	int xmap = 0;
	int ymap = 0;
};

#endif //__MODULEWELCOMSCREEN__