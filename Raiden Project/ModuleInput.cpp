#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleRender.h"
#include "ModuleMap1.h"
#include "ModuleMap2.h"
#include "ModulePlayer.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
}

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

	if (keyboard[SDL_SCANCODE_ESCAPE])
	{
		return update_status::UPDATE_STOP;
	}

	App->map_1->ymap += 6;

	/*if (App->map_1->IsEnabled() && keyboard[SDL_SCANCODE_D] && App->player->position.x == 600 && App->map_1->xmap <= -5)
	{
		App->map_1->xmap += 6;
	}*/

		
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if (keyboard[SDL_SCANCODE_DOWN])
	{
		App->map_1->ymap -= 6;
	}

	if (keyboard[SDL_SCANCODE_A])
	{
		if (App->map_1->IsEnabled() && App->map_1->xmap <= -5 && App->player->position.x < 50)
		{
			App->map_1->xmap += 6;
		}

		if (App->map_2->IsEnabled() && App->map_1->xmap <= -3 && App->player->position.x < 50)
		{
			App->map_1->xmap += 6;
		}
	}

	if (keyboard[SDL_SCANCODE_D])
	{
		if (App->map_1->IsEnabled() && App->map_1->xmap >= -383 && App->player->position.x > 550)
		{
			App->map_1->xmap -= 6;
		}

		if (App->map_2->IsEnabled() && App->map_1->xmap >= -231 && App->player->position.x > 550)
		{
			App->map_1->xmap -= 6;
		}
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