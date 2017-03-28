#include "Globals.h"
#include "Application.h"
#include "ModuleMap2.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleMap1.h"
#include "ModuleWelcomeScreen.h"
#include"ModuleStageClear1.h"
#include "ModuleInput.h"
#include "ModuleAudio_1.h"
#include "ModuleAudio_2.h"
#include "ModuleFadeToBlack.h"
ModuleMap2::ModuleMap2() : Module()
{

}
ModuleMap2::~ModuleMap2()
{

}

bool ModuleMap2::Init()
{
	LOG("Loading background assets");
	ground = { App->map_1->xmap, App->map_1->ymap, 301*3, 5362*3};
	Map2 = App->textures->Load("Assets/Tilemap2.png");
	return true;
}

update_status ModuleMap2::Update()
{

	App->render->Blit(Map2, App->map_1->xmap, App->map_1->ymap-13457+7158, &ground);
	if (App->input->keyboard[SDL_SCANCODE_SPACE])
	{
		App->fade->FadeToBlack(this, App->StageClear1, 1.0f);
		
	}
	return UPDATE_CONTINUE;	
	
}

bool ModuleMap2::CleanUp()
{
	return true;
}