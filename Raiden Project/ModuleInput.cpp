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
#include "ModuleGroundExplosion.h"
#include "ModuleGroundEnemies.h"


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

	if ((SDL_InitSubSystem(SDL_INIT_EVENTS) || SDL_InitSubSystem(SDL_INIT_JOYSTICK) || SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER)) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
	//Always Check for controllers
	if (SDL_NumJoysticks() == 0)
	{
		gpad = false;
		gpad_on = false;
		gpad2 = false;
		gpad2_on = false;
	}

	if (!gpad_on)
	{
		if (SDL_NumJoysticks() < 1)
		{
			//LOG("Warning: No controllers connected!\n");
		}
		else
		{
			//Load controller
			controller = SDL_GameControllerOpen(0);
			joystick = SDL_JoystickOpen(0);
			gpad_on = true;

			controller2 = SDL_GameControllerOpen(1);
			joystick2 = SDL_JoystickOpen(1);
			gpad2_on = true;

			if (controller == NULL || controller2 == NULL)
			{
				//LOG("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//LOG("%d controllers found.\n", SDL_NumJoysticks())
			}
		}
	}

	SDL_PumpEvents();

	//Controller 1 buttons

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

	//Controller 2 buttons

	Uint8 buttons2[MAX_BUTTONS];

	buttons2[0] = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_A);
	buttons2[1] = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_B);
	buttons2[2] = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_X);
	buttons2[3] = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_Y);
	buttons2[4] = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_BACK);
	buttons2[5] = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_GUIDE);
	buttons2[6] = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_START);
	buttons2[7] = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_LEFTSTICK);
	buttons2[8] = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_RIGHTSTICK);
	buttons2[9] = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
	buttons2[10] = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
	buttons2[11] = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_DPAD_UP);
	buttons2[12] = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	buttons2[13] = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	buttons2[14] = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

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

	//Gamepad 1 key state

	for (int i = 0; i < MAX_BUTTONS + 1; ++i)
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

	//Gamepad 2 key state

	for (int i = 0; i < MAX_BUTTONS + 1; ++i)
	{
		if (buttons2[i] == 1)
		{
			if (gamepad2[i] == KEY_IDLE)
				gamepad2[i] = KEY_DOWN;
			else
				gamepad2[i] = KEY_REPEAT;
		}
		else
		{
			if (gamepad2[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				gamepad2[i] = KEY_UP;
			else
				gamepad2[i] = KEY_IDLE;
		}
	}

	//Joystick 1

	int joystickpositions[5];

	//Normalized direction
	int xDir = 0;
	int yDir = 0;

	if (SDL_JoystickGetAxis(joystick, 0) > JOYSTICK_DEAD_ZONE)
	{
		joystickpositions[4] = 1;
	}
	else if (SDL_JoystickGetAxis(joystick, 0) < -JOYSTICK_DEAD_ZONE)
	{
		joystickpositions[3] = 1;
	}

	if (SDL_JoystickGetAxis(joystick, 1) > JOYSTICK_DEAD_ZONE)
	{
		joystickpositions[2] = 1;
	}
	else if (SDL_JoystickGetAxis(joystick, 1) < -JOYSTICK_DEAD_ZONE)
	{
		joystickpositions[1] = 1;
	}
	if (yDir == 0 || xDir == 0)
		joystickpositions[0] = 1;

	for (int i = 0; i < 5; ++i)
	{
		if (joystickpositions[i] == 1)
		{
			if (joystickpos[i] == KEY_IDLE)
				joystickpos[i] = KEY_DOWN;
			else
				joystickpos[i] = KEY_REPEAT;
		}
		else
		{
			if (joystickpos[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				joystickpos[i] = KEY_UP;
			else
				joystickpos[i] = KEY_IDLE;
		}
	}

	//Joystick 2

	int joystickpositions2[5];

	//Normalized direction
	int xDir2 = 0;
	int yDir2 = 0;

	if (SDL_JoystickGetAxis(joystick2, 0) > JOYSTICK_DEAD_ZONE)
	{
		joystickpositions2[4] = 1;
	}
	else if (SDL_JoystickGetAxis(joystick2, 0) < -JOYSTICK_DEAD_ZONE)
	{
		joystickpositions2[3] = 1;
	}

	if (SDL_JoystickGetAxis(joystick2, 1) > JOYSTICK_DEAD_ZONE)
	{
		joystickpositions2[2] = 1;
	}
	else if (SDL_JoystickGetAxis(joystick2, 1) < -JOYSTICK_DEAD_ZONE)
	{
		joystickpositions2[1] = 1;
	}
	if (yDir2 == 0 || xDir2 == 0)
		joystickpositions2[0] = 1;

	for (int i = 0; i < 5; ++i)
	{
		if (joystickpositions2[i] == 1)
		{
			if (joystickpos2[i] == KEY_IDLE)
				joystickpos2[i] = KEY_DOWN;
			else
				joystickpos2[i] = KEY_REPEAT;
		}
		else
		{
			if (joystickpos2[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				joystickpos2[i] = KEY_UP;
			else
				joystickpos2[i] = KEY_IDLE;
		}
	}

	if (keyboard[SDL_SCANCODE_ESCAPE])
	{
		return update_status::UPDATE_STOP;
	}

	if ((keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || joystickpos[3] == KEY_STATE::KEY_REPEAT || keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || joystickpos[4] == KEY_STATE::KEY_REPEAT) && !p1moving)
		p1moving = true;
	else
		p1moving = false;
	if ((keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || joystickpos2[3] == KEY_STATE::KEY_REPEAT || keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT || joystickpos2[4] == KEY_STATE::KEY_REPEAT) && !p2moving)
		p2moving = true;
	else
		p2moving = false;

	if (!App->player->deadplayer && !p2moving)
	{
		//Player one side scroll
		if ((keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !gpad) || (joystickpos[3] == KEY_STATE::KEY_REPEAT && gpad))
		{
			if (App->player2->deadplayer)
			{
				App->player2->position.x = App->player->position.x;
				App->player2->position.y = App->player->position.y;
			}

			if ((App->map_1->IsEnabled() && App->map_1->xmap <= -5 && App->player2->position.x <= 595))
			{
				App->map_1->xmap += App->map_1->xscrollspeed;
				App->enemies->MoveEnemiesRight(true);
				App->particles->MoveParticlesRight(true);
				App->powerups->MovePowerUpsRight(true);
				App->gexplosion->MoveExplosionRight(true);
				App->genemies->MoveGroundEnemiesRight(true);
			}
		}


		if ((keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && !gpad) || (joystickpos[4]  == KEY_STATE::KEY_REPEAT && gpad))
		{
			if (App->player2->deadplayer)
			{
				App->player2->position.x = App->player->position.x;
				App->player2->position.y = App->player->position.y;
			}

			if ((App->map_1->IsEnabled() && App->map_1->xmap >= -383 && App->player2->position.x >= 10))
			{
				App->map_1->xmap -= App->map_1->xscrollspeed;
				App->enemies->MoveEnemiesRight(false);
				App->particles->MoveParticlesRight(false);
				App->powerups->MovePowerUpsRight(false);
				App->gexplosion->MoveExplosionRight(false);
				App->genemies->MoveGroundEnemiesRight(false);
			}
		}
	}
	else if (!App->player2->deadplayer && !p1moving)
	{
		//Player two side scroll
		if ((keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && !gpad2) || (joystickpos2[3] == KEY_STATE::KEY_REPEAT && gpad2))
		{
			if (App->player->deadplayer)
			{
				App->player->position.x = App->player2->position.x;
				App->player->position.y = App->player2->position.y;
			}

			if ((App->map_1->IsEnabled() && App->map_1->xmap <= -5 && App->player->position.x <= 595))
			{
				App->map_1->xmap += App->map_1->xscrollspeed;
				App->enemies->MoveEnemiesRight(true);
				App->particles->MoveParticlesRight(true);
				App->powerups->MovePowerUpsRight(true);
				App->gexplosion->MoveExplosionRight(true);
				App->genemies->MoveGroundEnemiesRight(true);
			}
		}

		if ((keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && !gpad2) || joystickpos2[4] == KEY_STATE::KEY_REPEAT && gpad2)
		{
			if (App->player->deadplayer)
			{
				App->player->position.x = App->player2->position.x;
				App->player->position.y = App->player2->position.y;
			}

			if ((App->map_1->IsEnabled() && App->map_1->xmap >= -383 && App->player->position.x >= 10))
			{
				App->map_1->xmap -= App->map_1->xscrollspeed;
				App->enemies->MoveEnemiesRight(false);
				App->particles->MoveParticlesRight(false);
				App->powerups->MovePowerUpsRight(false);
				App->gexplosion->MoveExplosionRight(false);
				App->genemies->MoveGroundEnemiesRight(false);
			}
		}
	}

	if (App->input->gamepad[6])
	{
		gpad = true;
	}
		
	if (App->input->keyboard[SDL_SCANCODE_1])
	{
		gpad = false;
	}

	if (App->input->gamepad2[6])
	{
		gpad2 = true;
	}

	if (App->input->keyboard[SDL_SCANCODE_2])
	{
		gpad2 = false;
	}

	return update_status::UPDATE_CONTINUE;
}


// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_GameControllerClose(controller);
	controller = NULL;
	SDL_JoystickClose(joystick);
	joystick = NULL;
	SDL_GameControllerClose(controller2);
	controller2 = NULL;
	SDL_JoystickClose(joystick2);
	joystick2 = NULL;
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
	return true;
}