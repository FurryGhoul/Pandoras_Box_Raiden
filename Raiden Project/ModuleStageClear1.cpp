#include "Globals.h"
#include "Application.h"
#include "ModuleMap2.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleMap1.h"
#include "ModuleStageClear1.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleShadows.h"
#include "ModuleFonts.h"

#include <stdio.h>

ModuleStageClear1::ModuleStageClear1() : Module()
{

}
ModuleStageClear1::~ModuleStageClear1()
{

}

bool ModuleStageClear1::Init()
{
	LOG("Loading background assets");
	ground = { 0, 0 ,224 * 3 ,256 * 3 };
	StageClear1 = App->textures->Load("Assets/Winningscreen.png");
	return true;
}

update_status ModuleStageClear1::Update()
{
	if (App->particles->IsEnabled() && App->player->IsEnabled()&& App->collision->IsEnabled())
	{
		App->particles->Disable();
		App->shadows->Disable();
		App->player->Disable();
		App->player2->Disable();
		App->collision->Disable();
	}

	App->render->Blit(StageClear1, 0, 0, &ground, 224 * 3, 256 * 3+ 62);
	sprintf_s(text, 60, "CONGRATULATIONS!YOU BEAT");
	sprintf_s(text1, 60, "OUR GAME!THANK YOU FOR");
	sprintf_s(text2, 60, "PLAYING IT,YOUR HIGHEST");
	sprintf_s(text3, 60, "SCORE WAS:");

	App->fonts->BlitText(50, 600, 1, text);
	App->fonts->BlitText(50, 630, 1, text1);
	App->fonts->BlitText(50, 660, 1, text2);
	App->fonts->BlitText(50, 690, 1, text3);

	if (App->player->hiscore > App->player2->hiscore)
		App->fonts->BlitText(300, 690, 0, App->player->highscoret);
	else
		App->fonts->BlitText(300, 690, 0, App->player2->highscoret);

	if ((App->input->keyboard[SDL_SCANCODE_SPACE] && !App->input->gpad) || (App->input->gamepad[6] && App->input->gpad))
	{
		App->fade->FadeToBlack(this, App->WelcomeScreen);
	}

	return UPDATE_CONTINUE;
}

bool ModuleStageClear1::CleanUp()
{
	return true;
}