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
#include "ModulePowerUps.h"
#include "ModuleFonts.h"

#include <stdio.h>

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
		App->enemies->AddEnemy(ENEMY_TYPES::BONUS_SHIP, 210, -1700);
		App->enemies->AddEnemy(ENEMY_TYPES::BONUS_SHIP, 410, -2200);
		App->enemies->AddEnemy(ENEMY_TYPES::BONUS_SHIP, 300, -3200);
		App->enemies->AddEnemy(ENEMY_TYPES::BONUS_SHIP, 350, -3900);
		App->enemies->AddEnemy(ENEMY_TYPES::TANK, 200, -500);
		App->powerups->AddPowerUp(POWERUP_TYPES::REDUP, 200, -550);

		App->collision->Enable();
		App->render->camera.x = App->render->camera.y = 0;
		App->enemies->Enable();
		App->powerups->Enable();
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
	if (App->render->camera.y == -4500)
	{
		App->fade->FadeToBlack(this, App->WelcomeScreen, 1.0f);
		App->enemies->EraseEnemies();
	}


	if (App->player2->allowhiscore == true)
	{
		sprintf_s(App->player2->highscore_text, 10, "HI-SCORE");
		sprintf_s(App->player2->highscore, 10, "%7d", App->player2->hiscore);
	//	sprintf_s(App->player2->lastscore_text, 10, "LAST SCORE");
		//sprintf_s(App->player2->lastscoret, 10, "%7d", App->player2->lastscore);
		App->player2->allowhiscore = false;
	}
	App->fonts->BlitText(450, 20, 1, App->player2->highscore_text);
	App->fonts->BlitText(450, 55, 1, App->player2->highscore);
	//App->fonts->BlitText(450, 85, 1, App->player2->lastscore_text);
	//App->fonts->BlitText(450, 115, 1, App->player2->lastscoret);

	if (App->player->allowhiscore == true)
	{
		sprintf_s(App->player->highscore_text, 10, "HI-SCORE");
		sprintf_s(App->player->highscore, 10, "%7d", App->player->hiscore);
		//sprintf_s(App->player->lastscoret, 10, "LAST SCORE");
	//	sprintf_s(App->player->lastscoret, 10, "%7d", App->player->lastscore);
		App->player->allowhiscore = false;
	}
	App->fonts->BlitText(20, 20, 0, App->player->highscore_text);
	App->fonts->BlitText(20, 55, 0, App->player->highscore);
	//App->fonts->BlitText(20, 85, 0, App->player->lastscore_text);
	//App->fonts->BlitText(20, 115, 0, App->player->lastscoret);

	return UPDATE_CONTINUE;
}

bool ModuleMap1::CleanUp()
{
	return true;
}