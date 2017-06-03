/*#include "Globals.h"
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
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"

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
	if (!(App->particles->IsEnabled() && App->player->IsEnabled() &&  App->collision->IsEnabled()))
	{
		App->particles->Enable();
		App->shadows->Enable();
		App->player->Enable();
		App->player2->Enable();

		App->collision->Enable();
	}
	App->map_1->ymap += 2;
	App->render->Blit(Map2, App->map_1->xmap, App->map_1->ymap-13457+7158, &ground);
	if (App->input->keyboard[SDL_SCANCODE_BACKSPACE])
	{
		App->fade->FadeToBlack(this, App->StageClear1);
		
	}
	return UPDATE_CONTINUE;	
	
}

bool ModuleMap2::CleanUp()
{
	return true;
}*/