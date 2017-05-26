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
		//App->enemies->AddEnemy(0, ENEMY_TYPES::BOSS_MAIN, 230, -200);

		//App->enemies->AddEnemy(0, ENEMY_TYPES::GREY_TANK, 500, -300);

		App->enemies->AddEnemy(0, ENEMY_TYPES::MEGATANK, 500, -300);

		

		// First street
		//Horizontal tanks
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 0, -900);
		//Vertical tanks
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -1200);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -1300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -1400);


		//Second street
		//Horizontal tanks
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 0, -1220);
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 0, -1300);
		// Light Kamikazes
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -1340);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -1340);
		//Vertical tanks
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -1600);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -1700);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -1800);


		//Third street
		// Light kamikazes
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -2000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -2000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -2100);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 0, -2200);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -2300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -2400);
	    // Horizontal tanks

		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 0, -1880);
		App->enemies->AddEnemy(0, ENEMY_TYPES::TANK, 0, -1940);		
		App->enemies->AddEnemy(18, ENEMY_TYPES::TANK, 0, -2300);

		//Vertical tanks		
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -2300);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -2000);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -2100);

		//Forth street
		//Strange thing
		App->enemies->AddEnemy(5, ENEMY_TYPES::TANK, 500, -2390);
		App->enemies->AddEnemy(6, ENEMY_TYPES::TANK, 400, -2420);
		App->enemies->AddEnemy(7, ENEMY_TYPES::TANK, 300, -2450);

		App->enemies->AddEnemy(2, ENEMY_TYPES::TANK, 700, -2270);
		App->enemies->AddEnemy(3, ENEMY_TYPES::TANK, 600, -2290);
		App->enemies->AddEnemy(4, ENEMY_TYPES::TANK, 500, -2310);


	


		// Pool	
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -2700);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -2700);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -2740);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_KAMIKAZE, 672, -2740);

		//Vertical tanks left
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -2800);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -2850);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -2900);
		//Vertical tanks right
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 270, -2800);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 270, -2900);
		//Horizontal delayed tanks
        App->enemies->AddEnemy(8, ENEMY_TYPES::TANK, -50, -2850);


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

		App->enemies->AddEnemy(2, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4220);
		App->enemies->AddEnemy(1, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::LIGHT_KAMIKAZE, -50, -4280);

	    //Horizontal tanks
		App->enemies->AddEnemy(9, ENEMY_TYPES::TANK, -50, -3150);
		App->enemies->AddEnemy(10, ENEMY_TYPES::TANK, -50, -3250);

		//Vertical right tanks
		//Direct
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -3150);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 750, -3250);
		//Vuelta
        App->enemies->AddEnemy(13, ENEMY_TYPES::TANK, 357*3, -3700);
        App->enemies->AddEnemy(11, ENEMY_TYPES::TANK, -50, -3700);

		//Vertical left tanks
		//Direct
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 270, -3450);
		App->enemies->AddEnemy(1, ENEMY_TYPES::TANK, 270, -3550);
		//Vuelta
		App->enemies->AddEnemy(12, ENEMY_TYPES::TANK, -50, -3600);
		
		
		//SE2 Tanks
		App->enemies->AddEnemy(14, ENEMY_TYPES::TANK, 200, -3770);
		App->enemies->AddEnemy(15, ENEMY_TYPES::TANK, 0, -3940);
		App->enemies->AddEnemy(16, ENEMY_TYPES::TANK, 0, -4200);
		App->enemies->AddEnemy(17, ENEMY_TYPES::TANK, 0, -4350);
		//SW2 Tanks
		App->enemies->AddEnemy(19, ENEMY_TYPES::TANK, 357 * 3, -4300);
		App->enemies->AddEnemy(20, ENEMY_TYPES::TANK, 357 * 3, -4400);

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
		App->enemies->AddEnemy(21, ENEMY_TYPES::GREY_TANK, 150, -4950);
		App->enemies->AddEnemy(21, ENEMY_TYPES::GREY_TANK, 250, -5400);

		App->enemies->AddEnemy(27, ENEMY_TYPES::GREY_TANK, 150, -5600);
		App->enemies->AddEnemy(27, ENEMY_TYPES::GREY_TANK, 300, -5650);
		App->enemies->AddEnemy(27, ENEMY_TYPES::GREY_TANK, 700, -5650);
		App->enemies->AddEnemy(27, ENEMY_TYPES::GREY_TANK, 520, -6070);
		//Horizontal to stop-right
		App->enemies->AddEnemy(23, ENEMY_TYPES::GREY_TANK, 0, -5050);
		App->enemies->AddEnemy(23, ENEMY_TYPES::GREY_TANK, 500, -5050);
		App->enemies->AddEnemy(23, ENEMY_TYPES::GREY_TANK, 650, -5050);
		App->enemies->AddEnemy(23, ENEMY_TYPES::GREY_TANK, 800, -5050);

		//Horizontal to right-stop
		App->enemies->AddEnemy(29, ENEMY_TYPES::GREY_TANK, 200, -6020);
		App->enemies->AddEnemy(29, ENEMY_TYPES::GREY_TANK, 100, -6020);

		//Horizontal to left-stop
		App->enemies->AddEnemy(24, ENEMY_TYPES::GREY_TANK, 250, -5150);
		App->enemies->AddEnemy(24, ENEMY_TYPES::GREY_TANK, 400, -5150);
		App->enemies->AddEnemy(24, ENEMY_TYPES::GREY_TANK, 550, -5150);
		App->enemies->AddEnemy(24, ENEMY_TYPES::GREY_TANK, 357 * 3, -5150);
		//Horizontal to stop-left
		App->enemies->AddEnemy(22, ENEMY_TYPES::GREY_TANK, 850, -6020);
		App->enemies->AddEnemy(22, ENEMY_TYPES::GREY_TANK, 950, -6020);

		//stop-east- north east 2
		App->enemies->AddEnemy(31, ENEMY_TYPES::GREY_TANK, 420, -6070);
		//stop-west-north west 2
		App->enemies->AddEnemy(30, ENEMY_TYPES::GREY_TANK, 620, -6070);


		//stop- North east 2- east- west
		App->enemies->AddEnemy(25, ENEMY_TYPES::GREY_TANK, 325, -5200);
		App->enemies->AddEnemy(26, ENEMY_TYPES::GREY_TANK, 450, -5200);
		//South-west 2
		App->enemies->AddEnemy(28, ENEMY_TYPES::GREY_TANK, 900, -5600);
		 

		App->enemies->AddEnemy(0, ENEMY_TYPES::BOX_POWERUP, 330, -3880);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BOX_POWERUP, 380, -4380);



		App->enemies->AddEnemy(0, ENEMY_TYPES::BOX_MEDAL, 700, -7100);



		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 300, -300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 600, -1700);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 450, -2830);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 700, -4200);
		App->enemies->AddEnemy(0, ENEMY_TYPES::BONUS_SHIP, 500, -5400);

		App->enemies->AddEnemy(0, ENEMY_TYPES::MEDIUM_SHOOTER, 120, -4600);
		App->enemies->AddEnemy(1, ENEMY_TYPES::MEDIUM_SHOOTER, 650, -4600);
		// 2nd Wave
		App->enemies->AddEnemy(1, ENEMY_TYPES::MEDIUM_SHOOTER, 550, -6400);
		App->enemies->AddEnemy(2, ENEMY_TYPES::MEDIUM_SHOOTER, 400, -6600);
		App->enemies->AddEnemy(1, ENEMY_TYPES::MEDIUM_SHOOTER, 500, -6800);
		App->enemies->AddEnemy(0, ENEMY_TYPES::MEDIUM_SHOOTER, 350, -6950);
		App->enemies->AddEnemy(0, ENEMY_TYPES::MEDIUM_SHOOTER, 300, -7050);
		App->enemies->AddEnemy(0, ENEMY_TYPES::MEDIUM_SHOOTER, 250, -7230);
		App->enemies->AddEnemy(0, ENEMY_TYPES::MEDIUM_SHOOTER, 450, -7480);
		// 3rd Wave
		App->enemies->AddEnemy(1, ENEMY_TYPES::MEDIUM_SHOOTER, 500, -8000);

		App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP, 600, -7850);
		App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP, 650, -8250);
		
		// 1st Wave
		App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP_TANK, 750, -8950);
		App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP_TANK, 875, -8950);
		App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP_TANK, 812, -9025);
		// 2nd Wave
		App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP_TANK, 800, -9200);
		App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP_TANK, 925, -9200);
		App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP_TANK, 744, -9275);
		App->enemies->AddEnemy(0, ENEMY_TYPES::SHIP_TANK, 856, -9275);

		//App->enemies->AddEnemy(2, ENEMY_TYPES::KAMIKAZE, 200, -100);
		//App->enemies->AddEnemy(2, ENEMY_TYPES::KAMIKAZE, 100, -200);
		//App->enemies->AddEnemy(2, ENEMY_TYPES::KAMIKAZE, 200, -300);
		//App->enemies->AddEnemy(2, ENEMY_TYPES::KAMIKAZE, 300, -400);

		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -6000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -6000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 250, -6000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -6300);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 780, -6300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -6250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -6340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 200, -6370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -7000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -7000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 250, -7000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -7300);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 780, -7300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -7250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -7340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 200, -7370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -8000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -8000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 250, -8000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -8300);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 780, -8300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -8250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -8340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 200, -8370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -9000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -9000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 250, -9000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -9300);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 780, -9300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -9250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -9340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 200, -9370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -10000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 250, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -10000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 780, -10300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -10250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -10340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 200, -10370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -10000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 250, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -10300);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 780, -10300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -10250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -10340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 200, -10370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -6000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -6000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 250, -6000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -6300);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 780, -6300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -6250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -6340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 200, -6370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -7000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -7000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 250, -7000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -7300);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 780, -7300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -7250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -7340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 200, -7370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -8000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -8000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 250, -8000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -8300);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 780, -8300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -8250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -8340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 200, -8370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -9000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -9000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 250, -9000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -9300);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 780, -9300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -9250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -9340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 200, -9370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -10000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 250, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -10000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 780, -10300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -10250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -10340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 200, -10370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 200, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -10000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 250, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -10300);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 780, -10300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 300, -10250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 780, -10340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 200, -10370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 220, -6000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 730, -6000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 220, -6000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 760, -6300);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 510, -6300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 390, -6250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 750, -6340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 240, -6370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 240, -7000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 620, -7000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 220, -7000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 710, -7300);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 700, -7300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 380, -7250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 720, -7340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 260, -7370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 210, -8000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 720, -8000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 280, -8000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 720, -8300);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 520, -8300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 460, -8250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 420, -8340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 760, -8370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 360, -9000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 500, -9000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 350, -9000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 610, -9300);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 660, -9300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 650, -9250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 830, -9340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 580, -9370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 740, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 620, -10000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 290, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 330, -10000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 230, -10300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 320, -10250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 760, -10340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 220, -10370);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 260, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 710, -10000);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 250, -10000);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 620, -10300);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 430, -10300);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 380, -10250);
		App->enemies->AddEnemy(0, ENEMY_TYPES::KAMIKAZE, 710, -10340);
		App->enemies->AddEnemy(9, ENEMY_TYPES::KAMIKAZE, 230, -10370);
		
		



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
		App->render->camera.y -= yscrollspeed;

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
	if (App->input->keyboard[SDL_SCANCODE_Z])
	{
		ymap += yscrollspeed * 10;
		yroad += ((yscrollspeed* 10) * 1.5) ;
		App->render->camera.y -= 1 * 10;
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