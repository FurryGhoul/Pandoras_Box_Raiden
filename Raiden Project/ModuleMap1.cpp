#include "Application.h"
#include "ModuleMap1.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"


ModuleMap1::ModuleMap1() : Module()
{
	
}
ModuleMap1::~ModuleMap1()
{
   
}

bool ModuleMap1::Init()
{
	LOG("Loading background assets");

	ground = {xmap,ymap ,352 ,3266};
    Map1 = App->textures->Load("Tilemaptest.png");
	return true;
}

update_status ModuleMap1::Update()
{

	App->render->Blit(Map1, xmap, ymap, &ground);
	return UPDATE_CONTINUE;
}

bool ModuleMap1::CleanUp()
{
	return true;
}