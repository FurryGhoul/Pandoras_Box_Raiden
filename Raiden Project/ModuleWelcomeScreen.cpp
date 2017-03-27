#include "Globals.h"
#include "Application.h"
#include "ModuleMap2.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleMap1.h"
#include"ModuleInput.h"
#include "ModuleStageClear1.h"
#include "ModuleAudio_1.h"
#include "ModuleAudio_2.h"
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
	ground = { 0, 0 ,224 * 4 ,256 * 4};
	Welcome = App->textures->Load("WelcomeScreen.png");
	return true;
}

update_status ModuleWelcomeScreen::Update()
{

	App->render->Blit(Welcome, 160, 0, &ground);
	if (App->input->keyboard[SDL_SCANCODE_SPACE])
	{
		Disable();
		App->map_1->Enable();
		App->audio->Init();
		
	}
	return UPDATE_CONTINUE;
}

bool ModuleWelcomeScreen::CleanUp()
{
	return true;
}