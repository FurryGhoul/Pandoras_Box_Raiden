#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_gamecontroller.h"
#include "SDL\include\SDL_joystick.h"

#define MAX_KEYS 300
#define MAX_BUTTONS 15
#define MAX_POSITIVE_JOYSTICK_POSITIONS 32767
#define MAX_NEGATIVE_JOYSTICK_POSITIONS -32768
#define MAX_JOYSTICK_POSITIONS 65535

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
	const int JOYSTICK_DEAD_ZONE = 8000;
	KEY_STATE keyboard[MAX_KEYS];
	KEY_STATE gamepad[MAX_BUTTONS];
	KEY_STATE joystickpos[4];
	SDL_GameController* controller = NULL;
	SDL_Joystick* joystick = NULL;
	Sint16 idk;
};

#endif // __ModuleInput_H__