#include "Application.h"
#include "ModuleMap1.h"
#include "ModuleMap2.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleInput.h"
#include "ModuleAudio_1.h"
#include "ModuleAudio_2.h"
ModuleMap1::ModuleMap1() : Module()
{
	
}
ModuleMap1::~ModuleMap1()
{
   
}

bool ModuleMap1::Init()
{
	xmap = -190;
	ymap = -9020;
	LOG("Loading background assets");
	ground = {xmap,ymap ,352*3 ,3266*3};
    Map1 = App->textures->Load("Tilemap1.png");
	return true;
}

update_status ModuleMap1::Update()
{
	App->render->Blit(Map1, xmap, ymap, &ground);
	if (App->input->keyboard[SDL_SCANCODE_SPACE])
	{
		Disable();
		App->map_2->Enable();
		App->audio->Close();
		App->audio_2->Init();
		xmap = -10;
		ymap = -1718;
	}

	return UPDATE_CONTINUE;
}

bool ModuleMap1::CleanUp()
{
	return true;
}