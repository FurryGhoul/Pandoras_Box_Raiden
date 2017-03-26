#include "ModuleMap1.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"

ModuleMap1::ModuleMap1()
{
	 ground = {xmap,ymap ,352 ,3266};
}
ModuleMap1::~ModuleMap1()
{
   
}

bool ModuleMap1::Start()
{
	LOG("Loading background assets");
    Map1 = App->textures->Load("Tilemaptest.png");
	return true;
}

update_status ModuleMap1::Update()
{
	App->render->Blit(App->render->tex, -130, -12100, &ground);
	return UPDATE_CONTINUE;
}