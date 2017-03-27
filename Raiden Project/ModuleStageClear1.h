#ifndef __MODULESTAGECLEAR__
#define __MODULESTAGECLEAR__
#include "Globals.h"
#include "Module.h"
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )


class ModuleStageClear1 : public Module
{
public:
	ModuleStageClear1();
	~ModuleStageClear1();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	SDL_Rect ground;
	SDL_Texture *StageClear1;
	int xmap = 0;
	int ymap = 0;
};

#endif //__MODULESTAGECLEAR__