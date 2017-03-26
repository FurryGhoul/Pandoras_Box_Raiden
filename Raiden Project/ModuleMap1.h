
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )


class ModuleMap1 : public Module
{
	ModuleMap1();
	~ModuleMap1();


	
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Rect ground;
	SDL_Texture *Map1;
	int ymap = -12100;
	int xmap = -130;
};





