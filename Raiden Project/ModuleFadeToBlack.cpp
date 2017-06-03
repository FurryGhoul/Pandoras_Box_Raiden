#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleMap1.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayer.h"
#include "ModuleWelcomeScreen.h"


ModuleFadeToBlack::ModuleFadeToBlack()
{
	screen = { 0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE };
}

ModuleFadeToBlack::~ModuleFadeToBlack()
{}

// Load assets
bool ModuleFadeToBlack::Init()
{
	LOG("Preparing Fade Screen");
	plates.PushBack({ 1, 1, 224, 256 });
	plates.PushBack({ 226, 1, 224, 256 });
	plates.PushBack({ 451, 1, 224, 256 });
	plates.PushBack({ 676, 1, 224, 256 });
	plates.PushBack({ 1, 258, 224, 256 });
	plates.PushBack({ 226, 258, 224, 256 });
	plates.PushBack({ 451, 258, 224, 256 });
	plates.PushBack({ 676, 258, 224, 256 });
	plates.PushBack({ 676, 258, 224, 256 });
	plates.PushBack({ 676, 258, 224, 256 });
	plates.PushBack({ 676, 258, 224, 256 });
	plates.PushBack({ 676, 258, 224, 256 });
	plates.PushBack({ 676, 258, 224, 256 });
	plates.PushBack({ 676, 258, 224, 256 });
	plates.PushBack({ 676, 258, 224, 256 });
	plates.PushBack({ 676, 258, 224, 256 });
	plates.PushBack({ 676, 258, 224, 256 });
	plates.PushBack({ 676, 258, 224, 256 });
	plates.PushBack({ 676, 258, 224, 256 });
	plates.PushBack({ 1, 258, 224, 256 });
	plates.PushBack({ 676, 1, 224, 256 });
	plates.PushBack({ 451, 1, 224, 256 });
	plates.PushBack({ 226, 1, 224, 256 });
	plates.PushBack({ 1, 1, 224, 256 });
	plates.speed = 0.2f;
	plates.loop = false;

	graphics = App->textures->Load("assets/FadingAnimation.png");
	return true;
}

// Update: draw background
update_status ModuleFadeToBlack::Update()
{
	if (current_step == fade_step::none)
		return UPDATE_CONTINUE;

	Uint32 now = SDL_GetTicks() - start_time;
	float normalized = MIN(1.0f, (float)now / (float)total_time);

	switch (current_step)
	{
	case fade_step::fade_to_black:
	{
		if (now >= total_time)
		{
			// TODO 2: enable / disable the modules received when FadeToBlacks() gets called
			module_off1->Disable();
			module_on1->Enable();
			// ---
			//Setting the map depending on the checkpoint
			if (App->map_1->checkpoint == 0)
			{
				App->map_1->xmap = -192;
				App->map_1->ymap = -15000;
				App->map_1->yroad = (App->map_1->ymap - 2300);
				App->render->camera.y = 0;
			}
			if (App->map_1->checkpoint == 1)
			{
				App->map_1->xmap = -192;
				App->map_1->ymap = -12732;
				App->map_1->yroad = -13898;
				App->render->camera.y = -2268;
			}
			if (App->map_1->checkpoint == 2)
			{
				App->map_1->xmap = -192;
				App->map_1->ymap = -10893;
				App->map_1->yroad = -11139;
				App->render->camera.y = -4107;
			}
			if (App->map_1->checkpoint == 3)
			{
				App->map_1->xmap = -192;
				App->map_1->ymap = -7293;
				App->map_1->yroad = -5739;
				App->render->camera.y = -7707;
			}
			if (App->map_1->checkpoint == 4)
			{
				App->map_1->xmap = -192;
				App->map_1->ymap = -5365;
				App->map_1->yroad = -5846;
				App->render->camera.y = -9635;

			}
			//Just functional for player one at the moment
			if (App->player->lifes == 0)
			{
				App->WelcomeScreen->setdown = true;
			}
			else
			{
				App->map_1->setup = true;
				App->map_1->setdown = true;
			}
			// ---
			total_time += total_time;
			start_time = SDL_GetTicks();
			current_step = fade_step::fade_from_black;
		}
	} break;

	case fade_step::fade_from_black:
	{
		normalized = 1.0f - normalized;

		if (now >= total_time)
			current_step = fade_step::none;
	} break;
	}

	//Blit
	if (!plates.Finished())
		App->render->Blit(graphics, 0, 0, &(plates.GetCurrentFrame()), 224 * 3, 256 * 3);

	return UPDATE_CONTINUE;
}

// Fade to black. At mid point deactivate one module, then activate the other
bool ModuleFadeToBlack::FadeToBlack(Module* module_off, Module* module_on)
{
	bool ret = false;

	if (current_step == fade_step::none)
	{

		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = 710;
		module_off1 = module_off;
		module_on1 = module_on;
		plates.Reset();
		ret = true;
	}

	return ret;
}