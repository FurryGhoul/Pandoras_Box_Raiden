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
#include "ModuleStageClear1.h"

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
	ground = { 0, 0, 352 * 3, 5362 * 3 };
	road = { 0, 0, 352 * 3, 5362 * 3 };
	Map1 = App->textures->Load("Assets/Tilemap2.png");
    Road = App->textures->Load("Assets/Roads.png");
	
	return true;
}

update_status ModuleMap1::Update()
{

	if (setup)
	{
		App->particles->Enable();
	    App->player->Enable();
		if (!App->player2->deadplayer)
		{ 
		App->player2->Enable();
		}
		/*App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER,50 , -800);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 50, -800);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 352 * 3- 50, -800);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 352 * 3 - 50, -800);*/
		
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 200, -100);
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 300, -200);
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 400, -500);
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 200, -350);
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 200, -230);
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 200, -320);

		/*App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 200, -320);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 200, -340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 200, -400);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 200, -500);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 200, -600);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 200, -700);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 200, -650);
		App->enemies->AddEnemy(1, ENEMY_TYPES::MEDIUM_SHOOTER, 200, -500);*/

		//App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -320);
		//App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -340);
		//App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -400);
		//App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -500);
		//App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -600);
		//App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -700);
		//App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -650);
		//App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -500);
		//App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 200, -320);
		//App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 200, -320);
		//App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 200, -320);
		//App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP_TANK, 200, -100);

		//App->enemies->AddEnemy(0, ENEMY_TYPES::LONG_MEGATANK, 500, -100);

		//App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP, 200, -100);


		App->collision->Enable();
		App->render->camera.y = 0;
		App->enemies->Enable();
		App->powerups->Enable();
		if (!App->player2->deadplayer)
		{ 
		App->player->InitialPos();
		}
		else
		{
			App->player->MidPos();
		}
		App->player2->InitialPos();
		App->player->godmode = false;
		App->player2->godmode = false;

		setup = false;
	}

	App->render->Blit(Map1, xmap, ymap, &ground);
	App->render->Blit(Road, xmap, yroad, &road);

    if (!(ymap >= 0))
	{ 
	ymap += yscrollspeed;
	yroad += (yscrollspeed * 1.5);
	App->render->camera.y -= 1;
	}

	if ((App->input->keyboard[SDL_SCANCODE_BACKSPACE] && !App->input->gpad) || (App->input->gamepad[12] && App->input->gpad))
	{
		won = true;

		//faster scrolling (comment "won = true;" first)
		//ymap += yscrollspeed * 50;
		//yroad += ((yscrollspeed * 1.5) * 50);
	}

	if ( ymap >= 0 || won)
	{
		App->player->Disable();
		App->player2->Disable();
		App->fade->FadeToBlack(this, App->StageClear1, 1.0f);
		App->enemies->EraseEnemies();
		App->powerups->ErasePowerUps();
		App->particles->EraseParticles();
		App->collision->Erase_Non_Player_Colliders();
		App->player->powerup_level = 0;
		App->player2->powerup_level = 0;
		App->particles->Disable();		
		App->player->Playergod->SetPos(10000, 10000);
		App->player2->Playergod->SetPos(10000, 10000);
		App->player->Player->SetPos(10000, 10000);
		App->player2->Player->SetPos(10000, 10000);
		App->player2->deadplayer = false;
		App->player->deadplayer = false;
		App->player->red = true;
		App->player2->red = true;
		App->player->lastscore = App->player->score;
		if (App->player->score >= App->player->hiscore)
		{
			App->player->hiscore = App->player->score;
		}
		App->player->allowhiscore = true;

		App->player2->lastscore = App->player2->score;
		if (App->player2->score >= App->player2->hiscore)
		{
			App->player2->hiscore = App->player2->score;
		}
		App->player2->allowhiscore = true;
	}


	if (App->player2->allowhiscore == true)
	{
		sprintf_s(App->player2->highscore_text, 20, "  HI-SCORE");
		sprintf_s(App->player2->highscoret, 20, "   %7d", App->player2->hiscore);
		sprintf_s(App->player2->lastscore_text, 20, "LAST SCORE");
		sprintf_s(App->player2->lastscoret, 20, "   %7d", App->player2->lastscore);
		App->player2->allowhiscore = false;
	}
	App->fonts->BlitText(420, 20, 1, App->player2->highscore_text);
	App->fonts->BlitText(420, 55, 1, App->player2->highscoret);
	App->fonts->BlitText(420, 90, 1, App->player2->lastscore_text);
	App->fonts->BlitText(420, 125, 1, App->player2->lastscoret);

	if (App->player->allowhiscore == true)
	{
		sprintf_s(App->player->highscore_text, 20, "HI-SCORE");
		sprintf_s(App->player->highscoret, 20, "%7d", App->player->hiscore);
		sprintf_s(App->player->lastscore_text, 20, "LAST SCORE");
		sprintf_s(App->player->lastscoret, 20, "%7d", App->player->lastscore);
		App->player->allowhiscore = false;
	}
	App->fonts->BlitText(20, 20, 0, App->player->highscore_text);
	App->fonts->BlitText(20, 55, 0, App->player->highscoret);
	App->fonts->BlitText(20, 90, 0, App->player->lastscore_text);
	App->fonts->BlitText(20, 125, 0, App->player->lastscoret);

	return UPDATE_CONTINUE;
}

bool ModuleMap1::CleanUp()
{
	return true;
}