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
		if (!App->player2->deadplayer)
		{ 
		App->player2->Enable();
		}
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 300, -400);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 100, -450);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 500, -500);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 410, -560);
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 100, -600);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 180, -600);
		//App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 250, -660);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 320, -720);
		//App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 410, -800);

		//App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 50, -900);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 200, -900);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 420, -920);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 350, -920);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 350, -970);
		//App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 500, -970);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 150, -1050);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 0, -1050);
		//App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 330, -1050);

		App->enemies->AddEnemy(2, ENEMY_TYPES::TANK, 50, -1200);
		App->enemies->AddEnemy(2, ENEMY_TYPES::TANK, 0, -1350);

		//App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 500, -1500);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 160, -1500);
		//App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 400, -1550);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 330, -1550);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 520, -1700);
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 550, -1700);
		//App->enemies->AddEnemy(2, ENEMY_TYPES::TANK, 160, -1750);
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 480, -1800);
		//App->enemies->AddEnemy(2, ENEMY_TYPES::TANK, 90, -1850);

		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 500, -2000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 160, -2000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 300, -2100);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 260, -2100);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 500, -2200);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 330, -2200);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 60, -2200);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 420, -2200);

		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 450, -2400);
		// Testing spawns
		App->powerups->AddPowerUp(POWERUP_TYPES::REDUP, 200, -100);
		App->powerups->AddPowerUp(POWERUP_TYPES::REDUP, 200, -100);
		//App->powerups->AddPowerUp(POWERUP_TYPES::REDUP, 200, -100);
		//App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 200, -200);
		//App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 200, -100);
		//App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 200, -100);

		App->collision->Enable();
		App->render->camera.x = App->render->camera.y = 0;
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
	App->render->camera.y -= 2;//both speed where reduced to 1
	App->map_1->ymap += 2;
	if (App->input->keyboard[SDL_SCANCODE_BACKSPACE])
	{
		App->render->camera.y = -5500;
		//App->fade->FadeToBlack(this, App->map_2, 1.0f);
	}
	if (App->render->camera.y <= -5500)
	{
		App->player->Disable();
		App->player2->Disable();
		App->fade->FadeToBlack(this, App->StageClear1, 1.0f);
		App->enemies->EraseEnemies();
		App->powerups->ErasePowerUps();
		App->player->powerup_level = 0;
		App->player2->powerup_level = 0;

		App->player->Playergod->SetPos(10000, 10000);
		App->player2->Playergod->SetPos(10000, 10000);
		App->player->Player->SetPos(10000, 10000);
		App->player2->Player->SetPos(10000, 10000);
		App->player2->deadplayer = false;
		App->player->deadplayer = false;

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