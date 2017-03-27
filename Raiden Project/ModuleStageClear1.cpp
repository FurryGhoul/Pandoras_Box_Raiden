#include "Globals.h"
#include "Application.h"
#include "ModuleMap2.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleMap1.h"
#include "ModuleStageClear1.h"
#include"ModuleInput.h"

ModuleStageClear1::ModuleStageClear1() : Module()
{

}
ModuleStageClear1::~ModuleStageClear1()
{

}

bool ModuleStageClear1::Init()
{
	LOG("Loading background assets");
	ground = { 0, 0 ,224 * 4 ,256 * 4 };
	StageClear1 = App->textures->Load("StageClear1.png");
	return true;
}

update_status ModuleStageClear1::Update()
{

	App->render->Blit(StageClear1, 160, 0, &ground);
	if (App->input->keyboard[SDL_SCANCODE_SPACE])
	{

	}
	return UPDATE_CONTINUE;
}

bool ModuleStageClear1::CleanUp()
{
	return true;
}