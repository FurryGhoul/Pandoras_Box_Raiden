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
#include "ModuleShadows.h"
#include "ModuleStageClear1.h"
#include "ModuleGroundExplosion.h"

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
	ground = { 0, 0, 352*3, 5362 * 3 };
	buildings = { 0, 0, 352 * 3, 5362 * 3 };
	road = { 0, 0, 352*3 , 5362 * 3 };
	Map1 = App->textures->Load("Assets/Tilemap2.png");
    Road = App->textures->Load("Assets/Roads.png");
	Buildings = App->textures->Load("Assets/Buildings.png");
	
	return true;
}

update_status ModuleMap1::Update()
{

	if (setup)
	{
		App->particles->Enable();
		App->shadows->Enable();
	    App->player->Enable();
		if (!App->player2->deadplayer)
		{ 
		App->player2->Enable();
		}
	

		//App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 0, -200);
		//App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 352 * 3, -200);


		//App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE,0, -300 );
		App->enemies->AddEnemy(0, ENEMY_TYPES::MEGATANK, 500, -300);
		
		/*// First street
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 0, -900);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -1200);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -1300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -1400);
		//Second street
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 0, -1260);
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 0, -1340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -1600);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -1700);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -1800);
		//Third street
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -2000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -2100);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -2300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 0, -1920);
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 0, -1980);
		//Forth street
		App->enemies->AddEnemy(2, ENEMY_TYPES::TANK, 600, -2370);
		App->enemies->AddEnemy(2, ENEMY_TYPES::TANK, 500, -2400);
		App->enemies->AddEnemy(2, ENEMY_TYPES::TANK, 400, -2430);




		App->enemies->AddEnemy(0, ENEMY_TYPES::BOX_POWERUP, 450, 500);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BOX_POWERUP, 700, -780);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BOX_POWERUP, 0, -780);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BOX_POWERUP, 300, -1000);


		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 200, -1500);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 780, -1500);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 250, -1830);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 730, -1830);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 780, -2000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 200, -2070);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 780, -2140);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 200, -2210);

		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 730, -2700);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 250, -2720);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 680, -2740);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 200, -2760);

		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 780, -2900);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 660, -3000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 720, -3050);
		App->enemies->AddEnemy(2, ENEMY_TYPES::LIGHT_SHOOTER, 780, -3100);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_SHOOTER, 320, -3200);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_SHOOTER, 260, -3250);
		App->enemies->AddEnemy(2, ENEMY_TYPES::LIGHT_SHOOTER, 200, -3300);

		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 300, -300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 600, -1700);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 450, -2830);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 700, -4200);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 500, -5400);

		App->enemies->AddEnemy(0, ENEMY_TYPES::MEDIUM_SHOOTER, 400, -5400);
		App->enemies->AddEnemy(0, ENEMY_TYPES::MEDIUM_SHOOTER, 700, -5600);

		App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP, 700, -8700);
		App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP, 800, -8900);
		App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP, 400, -300);

		App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP_TANK, 700, -9100);
		App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP_TANK, 850, -9100);
		App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP_TANK, 750, -9300);

		App->enemies->AddEnemy(2, ENEMY_TYPES::KAMIKAZE, 200, -100);
		App->enemies->AddEnemy(2, ENEMY_TYPES::KAMIKAZE, 100, -200);
		App->enemies->AddEnemy(2, ENEMY_TYPES::KAMIKAZE, 200, -300);
		App->enemies->AddEnemy(2, ENEMY_TYPES::KAMIKAZE, 300, -400);

		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -6000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -6000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 250, -6000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -6300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 780, -6300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -6250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -6340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -6370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -7000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -7000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 250, -7000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -7300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 780, -7300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -7250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -7340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -7370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -8000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -8000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 250, -8000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -8300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 780, -8300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -8250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -8340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -8370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -9000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -9000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 250, -9000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -9300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 780, -9300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -9250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -9340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -9370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -10000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 250, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -10000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 780, -10300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -10250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -10340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -10370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -10000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 250, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -10300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 780, -10300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -10250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -10340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -10370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -6000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -6000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 250, -6000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -6300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 780, -6300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -6250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -6340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -6370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -7000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -7000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 250, -7000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -7300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 780, -7300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -7250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -7340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -7370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -8000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -8000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 250, -8000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -8300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 780, -8300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -8250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -8340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -8370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -9000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -9000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 250, -9000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -9300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 780, -9300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -9250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -9340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -9370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -10000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 250, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -10000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 780, -10300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -10250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -10340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -10370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -10000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 250, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -10300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 780, -10300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -10250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -10340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 200, -10370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 220, -6000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -6000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 220, -6000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 760, -6300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 510, -6300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 390, -6250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -6340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 240, -6370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 240, -7000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 620, -7000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 220, -7000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 710, -7300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 700, -7300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 380, -7250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 720, -7340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 260, -7370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 210, -8000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 720, -8000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 280, -8000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 720, -8300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 520, -8300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 460, -8250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 420, -8340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 760, -8370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 360, -9000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 500, -9000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 350, -9000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 610, -9300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 660, -9300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 650, -9250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 830, -9340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 580, -9370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 740, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 620, -10000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 290, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 330, -10000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 230, -10300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 320, -10250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 760, -10340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 220, -10370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 260, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 710, -10000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 250, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 620, -10300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 430, -10300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 380, -10250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 710, -10340);
		App->enemies->AddEnemy(1, ENEMY_TYPES::KAMIKAZE, 230, -10370);*/
		
		



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
	App->render->Blit(Buildings, xmap, ymap, &buildings);
	App->render->Blit(Road, xmap, yroad, &road);

    if (!(ymap >= 0))
	{ 
		ymap += yscrollspeed;
		yroad += (yscrollspeed * 1.5);
		App->render->camera.y -= 1;

		if (yroad >= -4350)
		{
			road1 = true;
		}

		if (road1 && !roadmoved)
		{
			yroad -= 3000;
			roadmoved = true;
		}
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
		App->gexplosion->EraseParticles();
		App->shadows->EraseShadows();
		App->collision->Erase_Non_Player_Colliders();
		App->player->powerup_level = 0;
		App->player2->powerup_level = 0;
		App->player->missile_powerup_level = 0;
		App->player2->missile_powerup_level = 0;
		App->particles->Disable();		
		App->shadows->Disable();
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