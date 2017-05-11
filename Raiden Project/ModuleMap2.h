/*#ifndef __MODULEMAP2__
#define __MODULEMAP2__
#include "Globals.h"
#include "Module.h"
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )


class ModuleMap2 : public Module
{
public:
	ModuleMap2();
	~ModuleMap2();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	SDL_Rect ground;
	SDL_Texture *Map2;
	bool changing = false;
	
};

#endif //__MODULEMAP2__
*/
