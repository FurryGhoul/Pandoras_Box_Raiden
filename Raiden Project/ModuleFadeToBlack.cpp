#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleMap1.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFonts.h"
#include "ModuleWelcomeScreen.h"
#include <stdio.h>

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
	sprintf_s(App->player->lastscore_text, 20, "GODMODE");

	graphics = App->textures->Load("assets/FadingAnimation.png");
	return true;
}

// Update: draw background
update_status ModuleFadeToBlack::Update()
{
	if (current_step == fade_step::none)
	{
		if (App->player->UI)
		{
			counter++;
			//App->fonts->BlitText(20, 160, 0, App->player->score_text);
			App->fonts->BlitText(24, 24, 1, App->player->scoret); //score p1
			App->fonts->BlitText(102, 0, 0, App->player->score_text); //1up
			if (App->WelcomeScreen->twoplayers)
			{
				App->fonts->BlitText(490, 24, 1, App->player2->scoret); //score p2
				App->fonts->BlitText(560, 0, 0, App->player2->score_text); //2up
			}
			App->fonts->BlitText(243, 0, 0, App->player->highscore_text); //Hiscore
			App->fonts->BlitText(266, 24, 1, App->player->highscoret); //Hiscore value


				if (counter % 10 == 0 && font == 1)
					font = 0;
				else if (counter % 10 == 0 && font == 0)
					font = 1;

				if (App->player->godmode || App->player2->godmode) //Godmode text
					App->fonts->BlitText(249, 48, font, App->player->lastscore_text);
			//App->fonts->BlitText(20, 125, 0, App->player->lastscoret);
			//App->fonts->BlitText(420, 195, 1, App->player2->scoret);
			//App->fonts->BlitText(420, 20, 1, App->player2->highscore_text);
			//App->fonts->BlitText(420, 55, 1, App->player2->highscoret);
			//App->fonts->BlitText(315, 90, 1, App->player2->lastscore_text);
			//App->fonts->BlitText(420, 125, 1, App->player2->lastscoret);
			if (App->player->bomb_ammo != nullptr && App->player->IsEnabled())
			{
				App->render->Blit(App->player->graphics2, 5, 782, &(App->player->bomb_ammo->GetCurrentFrame()), App->player->bombammo_w, 14 * 3);
			}
			if (App->player2->bomb_ammo != nullptr && App->player2->IsEnabled())
			{
				App->render->Blit(App->player2->graphics2, 666 - (App->player2->bombs * 3 * 16), 782, &(App->player2->bomb_ammo->GetCurrentFrame()), App->player2->bombammo_w, 14 * 3);
			}
			if (App->player->livecounter != nullptr)
			{
				App->render->Blit(App->player->graphics2, 5, 48, &(App->player->livecounter->GetCurrentFrame()), App->player->lives_w, 8 * 3);
			}
		}

		return UPDATE_CONTINUE;
	}

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
			if (App->player->lives == 0)
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
		App->render->Blit(graphics, 0, 0, &(plates.GetCurrentFrame()), 224 * 3, 256 * 3.3);

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
bool ModuleFadeToBlack::IsFading()
{
	return current_step != fade_step::none;
}