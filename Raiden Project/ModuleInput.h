#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_gamecontroller.h"

#define MAX_KEYS 300
#define MAX_BUTTONS 15

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];
	KEY_STATE gamepad[MAX_BUTTONS];
	SDL_GameController* controller = NULL;
	int idk = 0;
};

#endif // __ModuleInput_H__