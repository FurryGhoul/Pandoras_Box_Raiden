#include "Globals.h"
#include "Application.h"
#include "ModuleMap2.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleMap1.h"
#include "ModuleInput.h"
#include "ModuleStageClear1.h"
#include "ModuleAudio_1.h"
#include "ModuleAudio_2.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePlayer2.h"
#include "ModulePowerUps.h"
#include "ModuleShadows.h"
#include "ModuleGroundExplosion.h"
#include "ModuleGroundEnemies.h"

ModuleWelcomeScreen::ModuleWelcomeScreen() : Module()
{

}
ModuleWelcomeScreen::~ModuleWelcomeScreen()
{

}

bool ModuleWelcomeScreen::Init()
{
	LOG("Loading background assets");
	App->map_1->Disable();

	App->StageClear1->Disable();
	App->audio_2->Close();
	App->particles->Disable();
	App->shadows->Disable();
	App->player->Disable();
	App->player2->Disable();

	ground = { 0, 0 ,224 * 3 ,256 * 3};
	Welcome = App->textures->Load("Assets/WelcomeScreen.png");
	return true;
}

update_status ModuleWelcomeScreen::Update()
{

	App->render->Blit(Welcome, 0, 0, &ground, 224 * 3, 256*3 + 62 );

	if (setdown)
	{
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
		App->player->powerup_level = 0;
		App->player->missile_powerup_level = 0;
		App->player->red = true;
		App->player2->powerup_level = 0;
		App->player2->missile_powerup_level = 0;
		App->player2->red = true;
		setdown = false;
		App->player->score = 0;
		App->player2->score = 0;
		App->map_1->setup = true;
		App->map_1->won = false;
		App->map_1->road1 = false;
		App->map_1->roadmoved = false;	
		App->collision->Erase_Non_Player_Colliders();
		App->map_1->checkpoint = 0;
	}
	if (App->input->keyboard[SDL_SCANCODE_1])
	{
		
		App->player2->deadplayer = true;
		App->player2->godmode = false;
		App->player->lives = 3;
		App->player->bombs = 3;
		App->fade->FadeToBlack(this, App->map_1);
		App->input->gpad = false;
		App->map_1->one_player = true;
		
	}

	if (App->input->gamepad[6])
	{
		App->player2->deadplayer = true;
		App->player->lives = 3;
		App->player2->godmode = false;
		App->player->bombs = 3;
		App->fade->FadeToBlack(this, App->map_1);
		App->input->gpad = true;
		App->map_1->one_player = true;
	}

	if (App->input->keyboard[SDL_SCANCODE_2])
	{
		App->player->bombs = 3;
		App->player2->bombs = 3;
		App->player->lives = 3;
		//App->player2->lifes = 3; player 2 has no lifes yet
		App->player2->godmode = false;
		App->player->godmode = false;
		App->fade->FadeToBlack(this, App->map_1);
		App->input->gpad = false;
		App->map_1->one_player = false;
	}

	return UPDATE_CONTINUE;
}

bool ModuleWelcomeScreen::CleanUp()
{
	return true;
}