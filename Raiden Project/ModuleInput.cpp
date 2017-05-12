#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleRender.h"
#include "ModuleMap1.h"
#include "ModuleMap2.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePowerUps.h"


ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
	for (uint i = 0; i < MAX_BUTTONS; ++i)
		gamepad[i] = KEY_IDLE;
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

	if((SDL_InitSubSystem(SDL_INIT_EVENTS) || SDL_InitSubSystem(SDL_INIT_JOYSTICK) || SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER)) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	//Check for controllers
	if (SDL_NumJoysticks() < 1)
	{
		LOG("Warning: No controllers connected!\n");
	}
	else
	{
		//Load controller
		controller = SDL_GameControllerOpen(0);
		if (controller == NULL )
		{
			LOG("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			LOG("%d controllers found.\n", SDL_NumJoysticks())
		}
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
	SDL_PumpEvents();

	Uint8 buttons[MAX_BUTTONS];

	buttons[0] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
	buttons[1] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B);
	buttons[2] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X);
	buttons[3] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y);
	buttons[4] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK);
	buttons[5] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_GUIDE);
	buttons[6] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START);
	buttons[7] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSTICK);
	buttons[8] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK);
	buttons[9] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
	buttons[10] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
	buttons[11] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
	buttons[12] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	buttons[13] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	buttons[14] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

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

	for (int i = 0; i < MAX_BUTTONS; ++i)
	{
		if (buttons[i] == 1)
		{
			if (gamepad[i] == KEY_IDLE)
				gamepad[i] = KEY_DOWN;
			else
				gamepad[i] = KEY_REPEAT;
		}
		else
		{
			if (gamepad[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				gamepad[i] = KEY_UP;
			else
				gamepad[i] = KEY_IDLE;
		}
	}

	if (keyboard[SDL_SCANCODE_ESCAPE])
	{
		return update_status::UPDATE_STOP;
	}

	/*if (buttons[2] == KEY_STATE::KEY_DOWN)
	{
		LOG("\nX key pressed %d times.\n", idk);
		idk++;
	}*/

	if (!App->player->deadplayer)
	{ 
	//Player one side scroll
	if (keyboard[SDL_SCANCODE_A])
	{
		if ((App->map_1->IsEnabled() && App->map_1->xmap <= -5 && App->player->position.x < 50 )&& !(App->map_1->IsEnabled() && App->map_1->xmap >= -383 && App->player2->position.x > 550 && App->player2->deadplayer == false))
		{
			App->map_1->xmap += 6;
			App->enemies->MoveEnemiesRight(true);
			App->particles->MoveParticlesRight(true);
			App->powerups->MovePowerUpsRight(true);
			if (!(App->map_1->IsEnabled() && App->map_1->xmap <= -5 && App->player2->position.x < 50))
			{ 
			App->player2->position.x += 6;
			}
		}
	}

	if (keyboard[SDL_SCANCODE_D])
	{
		if ((App->map_1->IsEnabled() && App->map_1->xmap >= -383 && App->player->position.x > 550) && !(App->map_1->IsEnabled() && App->map_1->xmap <= -5 && App->player2->position.x < 50 && App->player2->deadplayer == false))
		{
			App->map_1->xmap -= 6;
			App->enemies->MoveEnemiesRight(false);
			App->particles->MoveParticlesRight(false);
			App->powerups->MovePowerUpsRight(false);
			if (!(App->map_1->IsEnabled() && App->map_1->xmap >= -383 && App->player2->position.x > 550))
			{ 
			App->player2->position.x -= 6;
			}
		}

	}
}

	if (!App->player2->deadplayer)
{ 
	//Player two side scroll
	if (keyboard[SDL_SCANCODE_LEFT])
	{
		if ((App->map_1->IsEnabled() && App->map_1->xmap <= -5 && App->player2->position.x < 50) && !(App->map_1->IsEnabled() && App->map_1->xmap >= -383 && App->player->position.x > 550 && App->player->deadplayer == false))
		{
			App->map_1->xmap += 6;
			App->enemies->MoveEnemiesRight(true);
			App->particles->MoveParticlesRight(true);
			App->powerups->MovePowerUpsRight(true);
			if((!App->map_1->IsEnabled() && App->map_1->xmap <= -5 && App->player->position.x))
			{ 
			App->player->position.x += 6;
			}
		}
	}

	if (keyboard[SDL_SCANCODE_RIGHT])
	{
		if ((App->map_1->IsEnabled() && App->map_1->xmap >= -383 && App->player2->position.x > 550) && !(App->map_1->IsEnabled() && App->map_1->xmap <= -5 && App->player->position.x < 50 && App->player->deadplayer == false))
		{
			App->map_1->xmap -= 6;
			App->enemies->MoveEnemiesRight(false);
			App->particles->MoveParticlesRight(false);
			App->powerups->MovePowerUpsRight(false);
			if (!(App->map_1->IsEnabled() && App->map_1->xmap >= -383 && App->player->position.x > 550))
			{ 
			App->player->position.x -= 6;
			}
		}
	}
}
	return update_status::UPDATE_CONTINUE;
}


// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_GameControllerClose(controller);
	controller = NULL;
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	return true;
}