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
#include "ModuleGroundEnemies.h"

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
    //Chechpoint 0-> Camera = 0
	//Checkpoint 1-> Camera = -2268
	//Checkpoint 2-> Camera = -4107
	//Checkpoint 3-> Camera = -7707
	//Checkpoint 4-> Camera = -9635
	

	if (setdown)
	{
		App->player->UI = false;
		App->WelcomeScreen->setdown = true;
		App->enemies->Disable();
		App->powerups->Disable();
		App->collision->Disable();
		App->particles->Disable();
		App->gexplosion->Disable();
		App->genemies->Disable();
		App->player2->deadplayer = false;
		App->player->deadplayer = false;
		App->enemies->EraseEnemies();
		App->powerups->ErasePowerUps();
		App->particles->EraseParticles();
		App->genemies->EraseGroundEnemies();
		App->gexplosion->EraseParticles();
		powerup_kept = App->player->powerup_level;
		App->player->powerup_level = 0;
		App->player->missile_powerup_level = 0;
		App->player->red = true;
		App->player2->powerup_level = 0;
		App->player2->missile_powerup_level = 0;
		App->player2->red = true;
		setdown = false;
		App->player->bombs = 3;
		if (one_player)
		{
			App->player2->deadplayer = true;
			App->player2->godmode = false;
		}
		else
		{
			App->player2->bombs = 3;
		}
	}

	if (setup)
	{
		App->WelcomeScreen->times_started++;
		App->player->UI = true;
		App->particles->Enable();
		App->gexplosion->Enable();
		App->shadows->Enable();
		App->player->Enable();
		if (!App->player2->deadplayer)
		{
			App->player2->Enable();
		}
		App->collision->Enable();
		App->enemies->Enable();
		App->genemies->Enable();
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


		/*App->genemies->AddGroundEnemy(0, GENEMY_TYPES::TRAIN_LOCOMOTIVE, 1050, -5844);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::TRAIN_COACH, 1190, -5844);

		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::TRAIN_LOCOMOTIVE, 1050, -6012);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::TRAIN_COACH, 1190, -6012);

		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TRAIN_LOCOMOTIVE, 1050, -11100);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TRAIN_COACH, 1137, -11100);
		App->genemies->AddGroundEnemy(2, GENEMY_TYPES::TRAIN_COACH, 1201, -11100);*/

		//App->enemies->AddEnemy(0, ENEMY_TYPES::BOSS_MAIN, 350, -340);
		//App->genemies->AddGroundEnemy(0, GENEMY_TYPES::MEGATANK, 500, -300);
		if (App->player->lives < 3)
		{
			for (int i = 0; i <= powerup_kept; i++)
			{
				App->powerups->AddPowerUp(POWERUP_TYPES::REDUP, 200 + i*60, 200); 
			}
				
	
			
		}
		if (checkpoint <= 0) //CHECKPOINT 0	
		{
			// First street
		
			//Horizontal tanks
			App->genemies->AddGroundEnemy(0, GENEMY_TYPES::TANK, 0, -900);
			//Vertical tanks
			App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 750, -1200);
			App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 750, -1300);
			App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 750, -1400);


			//Second street
			//Horizontal tanks
			App->genemies->AddGroundEnemy(0, GENEMY_TYPES::TANK, 0, -1220);
			App->genemies->AddGroundEnemy(0, GENEMY_TYPES::TANK, 0, -1300);
			// Light Kamikazes
			App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -1340);
			App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -1340);
			//Vertical tanks
			App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 750, -1600);
			App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 750, -1700);
			App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 750, -1800);

			//Third street
			// Light kamikazes
			App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -2000);
			App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -2000);
			App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -2100);
			App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 0, -2200);

			App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 750, -2000);
			App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 750, -2100);
			App->genemies->AddGroundEnemy(0, GENEMY_TYPES::TANK, 0, -1880);
			App->genemies->AddGroundEnemy(0, GENEMY_TYPES::TANK, 0, -1940);
		// Invisible medalboxes
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::BOX_MEDAL, 520, -2080);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::BOX_MEDAL, 630, -2080);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::BOX_MEDAL, 520, -2180);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::BOX_MEDAL, 630, -2180);	
		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 300, -300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 600, -1700);

		App->genemies->AddGroundEnemy(2, GENEMY_TYPES::TANK, 700, -2270);
		App->genemies->AddGroundEnemy(3, GENEMY_TYPES::TANK, 600, -2290);
		App->genemies->AddGroundEnemy(4, GENEMY_TYPES::TANK, 500, -2310);

		}

		if (checkpoint <= 1)//CHECKPOINT 1	
		{
				
		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 450, -2830);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::MEGATANK, 500, -3700);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -2300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -2400);
		// Horizontal tanks

		App->genemies->AddGroundEnemy(18, GENEMY_TYPES::TANK, 0, -2300);

		//Vertical tanks		
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 750, -2300);


		//Forth street
		//Strange thing
		App->genemies->AddGroundEnemy(5, GENEMY_TYPES::TANK, 500, -2390);
		App->genemies->AddGroundEnemy(6, GENEMY_TYPES::TANK, 400, -2420);
		App->genemies->AddGroundEnemy(7, GENEMY_TYPES::TANK, 300, -2450);






		// Pool	
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -2700);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -2700);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -2740);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -2740);

		//Vertical tanks left
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 750, -2800);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 750, -2850);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 750, -2900);
		//Vertical tanks right
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 270, -2800);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 270, -2900);
		//Horizontal delayed tanks
		App->genemies->AddGroundEnemy(8, GENEMY_TYPES::TANK, -50, -2850);


		//Building after pool

		//Perfect trio
		App->enemies->AddEnemy(2, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -3320);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -3350);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -3380);

		App->enemies->AddEnemy(2, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -3420);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -3450);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -3480);

		App->enemies->AddEnemy(2, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -3620);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -3650);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -3680);

		App->enemies->AddEnemy(2, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -3920);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -3950);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -3980);

		App->enemies->AddEnemy(2, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -4020);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -4050);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -4080); 
		//Horizontal tanks
		App->genemies->AddGroundEnemy(9, GENEMY_TYPES::TANK, -50, -3150);
		App->genemies->AddGroundEnemy(10, GENEMY_TYPES::TANK, -50, -3250);

		//Vertical right tanks
		//Direct
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 750, -3150);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 750, -3250);
		//Vuelta
		App->genemies->AddGroundEnemy(13, GENEMY_TYPES::TANK, 357*3, -3700);
		App->genemies->AddGroundEnemy(11, GENEMY_TYPES::TANK, -50, -3700);

		//Vertical left tanks
		//Direct
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 270, -3450);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 270, -3550);
		//Vuelta
		App->genemies->AddGroundEnemy(12, GENEMY_TYPES::TANK, -50, -3600);
		
		
		//SE2 Tanks
		App->genemies->AddGroundEnemy(14, GENEMY_TYPES::TANK, 200, -3770);
		App->genemies->AddGroundEnemy(15, GENEMY_TYPES::TANK, 0, -3940);
		
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::BOX_MEDAL, 390, -2880);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::BOX_MEDAL, 580, -2880);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::BOX_MEDAL, 390, -3000);


		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::BOX_POWERUP, 330, -3880);

	}

		if (checkpoint <= 2) //Checkpoint 2
		{ 	
		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 700, -4200);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::BOX_POWERUP, 380, -4380);
		App->enemies->AddEnemy(2, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4220);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4280);

		App->genemies->AddGroundEnemy(16, GENEMY_TYPES::TANK, 0, -4200);
		App->genemies->AddGroundEnemy(17, GENEMY_TYPES::TANK, 0, -4350);
		//SW2 Tanks
		App->genemies->AddGroundEnemy(19, GENEMY_TYPES::TANK, 357 * 3, -4300);
		App->genemies->AddGroundEnemy(20, GENEMY_TYPES::TANK, 357 * 3, -4400);


		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 500, -5400);

		App->enemies->AddEnemy(0, ENEMY_TYPES::MEDIUM_SHOOTER, 120, -4600);
		App->enemies->AddEnemy(1, ENEMY_TYPES::MEDIUM_SHOOTER, 650, -4600);
		//Light kamizaze orgy 1
		//Left
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4500);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4530);
		App->enemies->AddEnemy(2, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4560);
		App->enemies->AddEnemy(3, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4590);
		App->enemies->AddEnemy(4, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4620);
		App->enemies->AddEnemy(5, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4650);
		App->enemies->AddEnemy(6, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4680);
		App->enemies->AddEnemy(7, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4710);
		//Right
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -4500);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -4530);
		App->enemies->AddEnemy(2, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -4560);
		App->enemies->AddEnemy(3, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -4590);
		App->enemies->AddEnemy(4, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -4620);
		App->enemies->AddEnemy(5, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -4650);
		App->enemies->AddEnemy(6, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -4680);
		App->enemies->AddEnemy(7, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -4710);

		//Light kamikaze orgy 2
		//Left
		App->enemies->AddEnemy(8, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4760);
		App->enemies->AddEnemy(9, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4790);
		App->enemies->AddEnemy(10, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4820);
		App->enemies->AddEnemy(11, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4850);
		//Right
		App->enemies->AddEnemy(8, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -4760);
		App->enemies->AddEnemy(9, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -4790);
		App->enemies->AddEnemy(10, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -4820);
		App->enemies->AddEnemy(11, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -4850);

		// Last two kamikazes
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -5000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -5000);

		//Roads1
		//Stoped
		App->genemies->AddGroundEnemy(21, GENEMY_TYPES::GREY_TANK, 150, -4950);
		App->genemies->AddGroundEnemy(21, GENEMY_TYPES::GREY_TANK, 250, -5400);

		App->genemies->AddGroundEnemy(27, GENEMY_TYPES::GREY_TANK, 150, -5600);
		App->genemies->AddGroundEnemy(27, GENEMY_TYPES::GREY_TANK, 300, -5650);
		App->genemies->AddGroundEnemy(27, GENEMY_TYPES::GREY_TANK, 700, -5650);
		App->genemies->AddGroundEnemy(27, GENEMY_TYPES::GREY_TANK, 520, -6070);
		//Horizontal to stop-right
		App->genemies->AddGroundEnemy(23, GENEMY_TYPES::GREY_TANK, 0, -5050);
		App->genemies->AddGroundEnemy(23, GENEMY_TYPES::GREY_TANK, 500, -5050);
		App->genemies->AddGroundEnemy(23, GENEMY_TYPES::GREY_TANK, 650, -5050);
		App->genemies->AddGroundEnemy(23, GENEMY_TYPES::GREY_TANK, 800, -5050);

		//Horizontal to right-stop
		App->genemies->AddGroundEnemy(29, GENEMY_TYPES::GREY_TANK, 200, -6020);
		App->genemies->AddGroundEnemy(29, GENEMY_TYPES::GREY_TANK, 100, -6020);

		//Horizontal to left-stop
		App->genemies->AddGroundEnemy(24, GENEMY_TYPES::GREY_TANK, 250, -5150);
		App->genemies->AddGroundEnemy(24, GENEMY_TYPES::GREY_TANK, 400, -5150);
		App->genemies->AddGroundEnemy(24, GENEMY_TYPES::GREY_TANK, 550, -5150);
		App->genemies->AddGroundEnemy(24, GENEMY_TYPES::GREY_TANK, 357 * 3, -5150);
		//Horizontal to stop-left
		App->genemies->AddGroundEnemy(22, GENEMY_TYPES::GREY_TANK, 850, -6020);
		App->genemies->AddGroundEnemy(22, GENEMY_TYPES::GREY_TANK, 950, -6020);

		//stop-east- north east 2
		App->genemies->AddGroundEnemy(31, GENEMY_TYPES::GREY_TANK, 420, -6070);
		//stop-west-north west 2
		App->genemies->AddGroundEnemy(30, GENEMY_TYPES::GREY_TANK, 620, -6070);


		//stop- North east 2- east- west
		App->genemies->AddGroundEnemy(25, GENEMY_TYPES::GREY_TANK, 325, -5200);
		App->genemies->AddGroundEnemy(26, GENEMY_TYPES::GREY_TANK, 450, -5200);
		//South-west 2
		App->genemies->AddGroundEnemy(28, GENEMY_TYPES::GREY_TANK, 900, -5600);
		 
		
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::TRAIN_LOCOMOTIVE, 1050, -5844);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::TRAIN_COACH, 1190, -5844);

		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::TRAIN_LOCOMOTIVE, 1050, -6012);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::TRAIN_COACH, 1190, -6012);

		// Invisible medalboxes 2
	

		//City after roads

		//South east 2- east
		App->genemies->AddGroundEnemy(21, GENEMY_TYPES::TANK, 600, -7040);
		App->genemies->AddGroundEnemy(22, GENEMY_TYPES::TANK, 550, -7090);
		App->genemies->AddGroundEnemy(23, GENEMY_TYPES::TANK, 500, -7140);
		App->genemies->AddGroundEnemy(24, GENEMY_TYPES::TANK, 450, -7190);
		// Coastline medalboxes
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::BOX_POWERUP, 820, -7080); // This should be a medal box
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::BOX_MEDAL, 720, -7180);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::BOX_MEDAL, 620, -7280);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::BOX_MEDAL, 520, -7380);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::BOX_MEDAL, 420, -7480);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::BOX_MEDAL, 360, -7630);
		// 2nd Wave
		App->enemies->AddEnemy(1, ENEMY_TYPES::MEDIUM_SHOOTER, 550, -6400);
		App->enemies->AddEnemy(2, ENEMY_TYPES::MEDIUM_SHOOTER, 400, -6600);
		App->enemies->AddEnemy(1, ENEMY_TYPES::MEDIUM_SHOOTER, 500, -6800);
		App->enemies->AddEnemy(0, ENEMY_TYPES::MEDIUM_SHOOTER, 350, -6950);
		App->enemies->AddEnemy(0, ENEMY_TYPES::MEDIUM_SHOOTER, 300, -7050);
		App->enemies->AddEnemy(0, ENEMY_TYPES::MEDIUM_SHOOTER, 250, -7230);
		App->enemies->AddEnemy(0, ENEMY_TYPES::MEDIUM_SHOOTER, 450, -7480);
		}
		if (checkpoint <= 3) //checkpoint 3
		{ 

		//South east 2
		App->genemies->AddGroundEnemy(25, GENEMY_TYPES::TANK, -50, -7770);
		App->genemies->AddGroundEnemy(26, GENEMY_TYPES::TANK, -50, -7970);
		App->genemies->AddGroundEnemy(27, GENEMY_TYPES::TANK, -50, -8170);

		//south- South east 2
		App->genemies->AddGroundEnemy(28, GENEMY_TYPES::TANK, 250, -7970);
		App->genemies->AddGroundEnemy(29, GENEMY_TYPES::TANK, 250, -8130);

		//south
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 250, -8300);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 250, -8325);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 250, -8350);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 250, -8375);

		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 250, -8500);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 250, -8525);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TANK, 250, -8550);
		// 3rd Wave
		App->enemies->AddEnemy(1, ENEMY_TYPES::MEDIUM_SHOOTER, 500, -8000);

		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::LONG_MEGATANK, 440, -8750);

		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::SHIP, 600, -7850);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::SHIP, 650, -8250);
		
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::BOX_MEDAL, 360, -7780);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::BOX_MEDAL, 360, -7930);
		// Upper coastline boxes
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::BOX_MEDAL, 650, -9400);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::BOX_POWERUP, 750, -9400);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::BOX_MEDAL, 850, -9400);
		
		// 1st Wave
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::SHIP_TANK, 750, -8950);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::SHIP_TANK, 875, -8950);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::SHIP_TANK, 812, -9025);
		// 2nd Wave
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::SHIP_TANK, 800, -9200);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::SHIP_TANK, 925, -9200);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::SHIP_TANK, 744, -9275);
		App->genemies->AddGroundEnemy(0, GENEMY_TYPES::SHIP_TANK, 856, -9275);	
		//east - north - west
		App->genemies->AddGroundEnemy(30, GENEMY_TYPES::TANK, -50, -9600);
		//east- north east 2- stop
		App->genemies->AddGroundEnemy(31, GENEMY_TYPES::TANK, -50, -9700);
      }
		if (checkpoint <= 4)
		{ 


		//West/east stop
		App->genemies->AddGroundEnemy(32, GENEMY_TYPES::TANK, 25, -10000);
		App->genemies->AddGroundEnemy(32, GENEMY_TYPES::TANK, 25, -10100);
		App->genemies->AddGroundEnemy(32, GENEMY_TYPES::TANK, 25, -10200);
		App->genemies->AddGroundEnemy(32, GENEMY_TYPES::TANK, 450, -10200);

		//South - sw2
		App->genemies->AddGroundEnemy(33, GENEMY_TYPES::TANK, 700, -10500);


		//Second roads
		//Kamikazes
		for (int i = 0; i < 6; ++i)
		{
			App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -11230 - i * 120);
			App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 390, -11250 - i * 120);
			App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 480, -11270 - i * 120);
			App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 570, -11290 - i * 120);
			App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 660, -11310 - i * 120);
			App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -11320 - i * 120);
			App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 230, -11330 - i * 120);
			App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 440, -11350 - i * 120);
			App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 700, -11370 - i * 120);
			App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 520, -11390 - i * 120);
		}

		//Stoped
		App->genemies->AddGroundEnemy(32, GENEMY_TYPES::GREY_TANK, 300, -10800);
		App->genemies->AddGroundEnemy(32, GENEMY_TYPES::GREY_TANK, 200, -10900);
		//Moving se
		App->genemies->AddGroundEnemy(33, GENEMY_TYPES::GREY_TANK, -50, -11150);
		App->genemies->AddGroundEnemy(34, GENEMY_TYPES::GREY_TANK, -50, -11250);
		App->genemies->AddGroundEnemy(35, GENEMY_TYPES::GREY_TANK, -50, -11350);


		App->genemies->AddGroundEnemy(41, GENEMY_TYPES::GREY_TANK, 400, -11650);
		App->genemies->AddGroundEnemy(41, GENEMY_TYPES::GREY_TANK, 200, -11750);
		App->genemies->AddGroundEnemy(41, GENEMY_TYPES::GREY_TANK, 0, -11850);

		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TRAIN_LOCOMOTIVE, 1050, -11100);
		App->genemies->AddGroundEnemy(1, GENEMY_TYPES::TRAIN_COACH, 1137, -11100);
		App->genemies->AddGroundEnemy(2, GENEMY_TYPES::TRAIN_COACH, 1201, -11100);

		//moving nw
		App->genemies->AddGroundEnemy(36, GENEMY_TYPES::GREY_TANK, 357 * 3, -11050);
		App->genemies->AddGroundEnemy(37, GENEMY_TYPES::GREY_TANK, 357 * 3, -11200);
		App->genemies->AddGroundEnemy(38, GENEMY_TYPES::GREY_TANK, 357 * 3, -11350);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BOSS_MAIN, 230, -12600);
		App->enemies->AddEnemy(0, ENEMY_TYPES::MINE, 350, -13600);
		App->enemies->AddEnemy(0, ENEMY_TYPES::MINE, 350, -14000);
		}
	}	
	//Checkpoint storage
	if (App->render->camera.y >= -2268)
	{
		checkpoint = 0;
	}
	else if (App->render->camera.y >= -4107)
	{
		checkpoint = 1;
	}
	else if (App->render->camera.y >= -7707)
	{
		checkpoint = 2;
	}
	else if (App->render->camera.y >= -9635)
	{
		checkpoint = 3;
	}
	else if (App->render->camera.y <= -9635)
	{
		checkpoint = 4;
	}


	App->render->Blit(Map1, xmap, ymap, &ground);
	App->render->Blit(Buildings, xmap, ymap, &buildings);
	App->render->Blit(Road, xmap, yroad, &road);

    if (!(ymap >= -170 * 3))
	{ 
		ymap += yscrollspeed;
		yroad += (yscrollspeed * 1.5);
		App->render->camera.y -= yscrollspeed;



		if (yroad >= -4350 && checkpoint != 4)
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
		cheat_win = true;

		//faster scrolling (comment "won = true;" first)
		//ymap += yscrollspeed * 50;
		//yroad += ((yscrollspeed * 1.5) * 50);
	}

	if (App->input->keyboard[SDL_SCANCODE_Z])
	{
		ymap += yscrollspeed * 10;
		yroad += ((yscrollspeed* 10) * 1.5) ;
		App->render->camera.y -= 1 * 10;
	}

	//Reset to chechpoint
	if (reset_collision && !initial_dead_time_got)
	{
		initial_dead_time = SDL_GetTicks();
		initial_dead_time_got = true;
	}
	if (SDL_GetTicks() - initial_dead_time > 1000 && reset_collision)
	{
		App->fade->FadeToBlack((Module*)App->map_1, (Module*)App->map_1);
		reset_collision = false;
		initial_dead_time_got = false;
	}
	//Reset to StageCleared
	if (won && !initial_time_win_got)
	{
		initial_time_win = SDL_GetTicks();
		initial_time_win_got = true;
	}
	if (SDL_GetTicks() - initial_time_win > 5000 && won || cheat_win)
	{
	
		App->player->UI = false;
		App->player->Disable();
		App->player2->Disable();
		App->fade->FadeToBlack(this, App->StageClear1);
		App->enemies->EraseEnemies();
		App->genemies->EraseGroundEnemies();
		App->powerups->ErasePowerUps();
		App->particles->EraseParticles();
		App->gexplosion->EraseParticles();
		App->shadows->EraseShadows();
		App->collision->Erase_Non_Player_Colliders();
		App->player->powerup_level = 0;
		App->player2->powerup_level = 0;
		App->player->missile_powerup_level = 0;
		App->player2->missile_powerup_level = 0;
		App->gexplosion->Disable();
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
			App->player->hiscore = App->player->score + App->player2->score;
		}
		App->player->allowhiscore = true;

		App->player2->lastscore = App->player2->score;
		if (App->player2->score >= App->player2->hiscore)
		{
			App->player2->hiscore = App->player->score + App->player2->score;
		}
		App->player2->allowhiscore = true;
		App->WelcomeScreen->setdown = true;
		initial_time_win_got = false;
		won = false;
		cheat_win = false;

	}


	if (App->player2->allowhiscore == true)
	{
		sprintf_s(App->player2->highscore_text, 20, "HI-SCORE");
		sprintf_s(App->player2->highscoret, 20, "   %7d", App->player2->hiscore);
		sprintf_s(App->player2->lastscore_text, 20, "2UP");
		sprintf_s(App->player2->lastscoret, 20, "   %7d", App->player2->lastscore);
		App->player2->allowhiscore = false;
	}

	if (App->player->allowhiscore == true)
	{
		sprintf_s(App->player->highscore_text, 20, "HI-SCORE");
		sprintf_s(App->player->highscoret, 20, "%7d", App->player->hiscore);
		sprintf_s(App->player->lastscore_text, 20, "GODMODE");
		sprintf_s(App->player->lastscoret, 20, "%7d", App->player->lastscore);
		App->player->allowhiscore = false;
	}

	return UPDATE_CONTINUE;
}

bool ModuleMap1::CleanUp()
{
	return true;
}