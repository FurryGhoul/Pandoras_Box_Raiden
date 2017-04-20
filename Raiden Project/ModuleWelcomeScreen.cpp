#include "Globals.h"
#include "Application.h"
#include "ModuleMap2.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleMap1.h"
#include "ModuleInput.h"
#include "ModuleStageClear1.h"
#include "ModuleAudio_1.h"
#include "ModuleAudio_2.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePlayer2.h"
#include "ModulePowerUps.h"

ModuleWelcomeScreen::ModuleWelcomeScreen() : Module()
{

}
ModuleWelcomeScreen::~ModuleWelcomeScreen()
{

}

bool ModuleWelcomeScreen::Init()
{
	LOG("Loading background assets");
	App->map_1->Disable();
	App->map_2->Disable();
	App->StageClear1->Disable();
	App->audio->Close();
	App->audio_2->Close();
	App->particles->Disable();
	App->player->Disable();
	App->player2->Disable();

	ground = { 0, 0 ,224 * 3 ,256 * 3};
	Welcome = App->textures->Load("Assets/WelcomeScreen.png");
	return true;
}

update_status ModuleWelcomeScreen::Update()
{
	if (App->particles->IsEnabled() && App->player->IsEnabled())
	{
		App->particles->Disable();
		App->player->Disable();
		App->player2->Disable();
		App->enemies->Disable();
		App->collision->Disable();
		App->powerups->Disable();
	}

	App->render->Blit(Welcome, 0, 0, &ground);
	if (App->input->keyboard[SDL_SCANCODE_F])
	{
		App->map_1->setup = true;
		App->fade->FadeToBlack(this, App->map_1, 1.0f);
		App->map_1->xmap = -192;
		App->map_1->ymap = -9020;
	}
	return UPDATE_CONTINUE;
}

bool ModuleWelcomeScreen::CleanUp()
{
	return true;
}