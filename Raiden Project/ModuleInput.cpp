#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleRender.h"

ModuleInput::ModuleInput() : Module()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
	SDL_PumpEvents();

	keyboard = SDL_GetKeyboardState(NULL);
	if (keyboard[SDL_SCANCODE_ESCAPE])
	{
		return update_status::UPDATE_STOP;
	}

	if (keyboard[SDL_SCANCODE_UP])
	{
		App->render->ymap += 6;
	}

	if (keyboard[SDL_SCANCODE_DOWN])
	{
		App->render->ymap -= 6;
	}

	if (keyboard[SDL_SCANCODE_LEFT])
	{
		App->render->xmap += 6;
	}

	if (keyboard[SDL_SCANCODE_RIGHT])
	{
		App->render->xmap -= 6;
	}
	// TODO 1: find out how to detect if the ESC key was pressed
	// and quit the game

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}