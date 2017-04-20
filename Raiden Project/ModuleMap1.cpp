#include "Application.h"
#include "ModuleMap1.h"
#include "ModuleMap2.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleInput.h"
#include "ModuleAudio_1.h"
#include "ModuleAudio_2.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"

ModuleMap1::ModuleMap1() : Module()
{
	
}
ModuleMap1::~ModuleMap1()
{
   
}

bool ModuleMap1::Init()
{
	LOG("Loading background assets");
	ground = {xmap,ymap ,352*3 ,3266*3};
    Map1 = App->textures->Load("Assets/Tilemap1.png");
	
	
	return true;
}

update_status ModuleMap1::Update()
{

	if (setup)
	{
		App->particles->Enable();
	    App->player->Enable();
		App->player2->Enable();
		App->enemies->AddEnemy(ENEMY_TYPES::LIGHT_SHOOTER, 300, -4000 );
		App->enemies->AddEnemy(ENEMY_TYPES::LIGHT_SHOOTER, 300, -1000);
		App->enemies->AddEnemy(ENEMY_TYPES::LIGHT_SHOOTER, 100, -100);
		App->enemies->AddEnemy(ENEMY_TYPES::LIGHT_SHOOTER, 400, -100);
		App->enemies->AddEnemy(ENEMY_TYPES::LIGHT_SHOOTER, 300, -500);
		App->enemies->AddEnemy(ENEMY_TYPES::LIGHT_SHOOTER, 100, -500);
		App->enemies->AddEnemy(ENEMY_TYPES::LIGHT_SHOOTER, 0, -700);
		App->enemies->AddEnemy(ENEMY_TYPES::LIGHT_SHOOTER, 200, -600);
		App->enemies->AddEnemy(ENEMY_TYPES::LIGHT_SHOOTER, 150, -2000);
		App->enemies->AddEnemy(ENEMY_TYPES::LIGHT_SHOOTER, 0, -2000);
		App->enemies->AddEnemy(ENEMY_TYPES::BONUS_SHIP, 410, -500);
		App->enemies->AddEnemy(ENEMY_TYPES::TANK, 400, -500);
		App->collision->Enable();
		App->render->camera.x = App->render->camera.y = 0;
		App->enemies->Enable();
		App->player->InitialPos();
		App->player2->InitialPos();
		App->player->godmode = false;
		App->player2->godmode = false;

		setup = false;
	}
	App->render->Blit(Map1, xmap, ymap, &ground);
	App->render->camera.y -= 2;
	App->map_1->ymap += 2;
	if (App->input->keyboard[SDL_SCANCODE_F])
	{
		App->fade->FadeToBlack(this, App->map_2, 1.0f);
	}

	return UPDATE_CONTINUE;
}

bool ModuleMap1::CleanUp()
{
	return true;
}