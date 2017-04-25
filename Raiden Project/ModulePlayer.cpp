#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModuleMap1.h"
#include "ModuleMap2.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemies.h"
#include "ModuleFonts.h"
#include "ModulePowerUps.h"

#include <stdio.h>

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	InitialPos();

	// Idle animation
	idle.PushBack({ 3, 2, 22, 28});

	// Idle animation 2
	idlep.PushBack({ 28, 2, 22, 29 });

	// Move right

	right.PushBack({ 53, 2, 19, 28 });
	right1.PushBack({ 97, 2, 14, 28 });

	// Move right 2

	rightp.PushBack({ 75, 2, 19, 29 });
	right1p.PushBack({ 114, 2, 14, 29 });

	// Move left

	left.PushBack({ 131, 2, 19, 28 });
	left1.PushBack({ 175, 2, 14, 28 });

	// Move left 2

	leftp.PushBack({ 153, 2, 19, 29 });
	left1p.PushBack({ 192, 2, 14, 29 });
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Init()
{
	LOG("Loading player");

	graphics = App->textures->Load("Assets/Player1.png");
	Player = App->collision->AddCollider({ 0, 0, player_w, player_h }, COLLIDER_PLAYER, this, 3); // Bullettype 3 differentiate the player colliders
	Playergod = App->collision->AddCollider({ 0, 0, player_w, player_h }, COLLIDER_GOD, this, 3);
	Player->SetPos(82938, 2323);
	score = 0;
	font_score = App->fonts->Load("Assets/Font.png", "> ?@ABCDEFGHIJKLMNOPQRSTUVWXYZ!�?_^#$%&'()x+.-,;tpsczpc/0123456789:", 3);

	/*	
		@ = "copyright symbol"
		� = smaller "!"
		^ = """ (quotation marks)
		x = smaller "X"
		t = "TM"
		ps = "pts"
		cz = "cts"
		pc = "pcs"
	*/

	return true;
}


// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->fonts->UnLoad(font_score);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (godmode == false)
	{
		Playergod->SetPos(10000000, 10000000);
	}
	if (godmode == true)
	{
		Player->SetPos(10000000, 10000000);
	}

	if (allowtimep == true)
	{
		timep = SDL_GetTicks();
		allowtimep = false;
	}

	if (SDL_GetTicks() >= (timep + 10))
	{
		if (propeller == true)
		{
			propeller = false;
			allowtimep = true;
		}

		else if (propeller == false)
		{
			propeller = true;
			allowtimep = true;
		}
	}

	int speed = 10;

	if (propeller)
	{
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			if (allowtime == true)
			{
				time = SDL_GetTicks();
				allowtime = false;
			}

			if (current_animation != &left)
			{
				left.Reset();
				current_animation = &left;
			}

			if (current_animation != &left1 && SDL_GetTicks() >= (time + 300))
			{
				left1.Reset();
				current_animation = &left1;
			}

			if ((App->map_1->IsEnabled() || App->map_2->IsEnabled()) && position.x >= 10)
			{
				position.x -= speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			if (allowtime == true)
			{
				time = SDL_GetTicks();
				allowtime = false;
			}

			if (current_animation != &right)
			{
				right.Reset();
				current_animation = &right;
			}

			if (current_animation != &right1 && SDL_GetTicks() >= (time + 300))
			{
				right1.Reset();
				current_animation = &right1;
			}

			if ((App->map_1->IsEnabled() || App->map_2->IsEnabled()) && position.x <= 594)
			{
				position.x += speed;
				
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			position.y += speed;

			if ((App->map_1->IsEnabled() || App->map_2->IsEnabled()) && position.y >= 683)
			{
				position.y -= speed;
				
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
		{
			position.y -= speed;
			
			if ((App->map_1->IsEnabled() || App->map_2->IsEnabled()) && position.y <= -1)
			{
				position.y += speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP)
		{
			allowtime = true;
			time = SDL_GetTicks();
			if (current_animation != &left)
			{
				left.Reset();
				current_animation = &left;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP)
		{
			allowtime = true;
			time = SDL_GetTicks();
			if (current_animation != &right)
			{
				right.Reset();
				current_animation = &right;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_S]
			&& App->input->keyboard[SDL_SCANCODE_W])
		{
			current_animation = &idle;
		}
		if (App->input->keyboard[SDL_SCANCODE_D]
			&& App->input->keyboard[SDL_SCANCODE_A])
		{
			current_animation = &idle;
		}

		if (
			App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
		{
			if (SDL_GetTicks() >= time + 100)
			{
				current_animation = &idle;
			}
		}

		// Draw everything --------------------------------------
		if (current_animation == &idle)
		{
			player_w = 22 * 3;
			player_h = 28 * 3;
		}
		else if (current_animation == &left || current_animation == &right)
		{
			player_w = 19 * 3;
			player_h = 28 * 3;
		}
		else if (current_animation == &left1 || current_animation == &right1)
		{
			player_w = 14 * 3;
			player_h = 28 * 3;
		}
		// Draw UI (score) --------------------------------------
		sprintf_s(score_text, 20, "SCORE", score);
		sprintf_s(scoret, 20, "%7d", score);

		// TODO 3: Blit the text of the score in at the bottom of the screen

		App->fonts->BlitText(20, 160, 0, score_text);
		App->fonts->BlitText(20, 195, 0, scoret);
	}

	else
	{
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			if (allowtime == true)
			{
				time = SDL_GetTicks();
				allowtime = false;
			}

			if (current_animation != &leftp)
			{
				leftp.Reset();
				current_animation = &leftp;
			}

			if (current_animation != &left1p && SDL_GetTicks() >= (time + 300))
			{
				left1p.Reset();
				current_animation = &left1p;
			}

			if ((App->map_1->IsEnabled() || App->map_2->IsEnabled()) && position.x >= 10)
			{
				position.x -= speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			if (allowtime == true)
			{
				time = SDL_GetTicks();
				allowtime = false;
			}

			if (current_animation != &rightp)
			{
				rightp.Reset();
				current_animation = &rightp;
			}

			if (current_animation != &right1p && SDL_GetTicks() >= (time + 300))
			{
				right1p.Reset();
				current_animation = &right1p;
			}

			if ((App->map_1->IsEnabled() || App->map_2->IsEnabled()) && position.x <= 594)
			{
				position.x += speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			position.y += speed;

			if ((App->map_1->IsEnabled() || App->map_2->IsEnabled()) && position.y >= 683)
			{
				position.y -= speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
		{
			position.y -= speed;
			
			if ((App->map_1->IsEnabled() || App->map_2->IsEnabled()) && position.y <= -1)
			{
			position.y += speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP)
		{
			allowtime = true;
			time = SDL_GetTicks();
			if (current_animation != &leftp)
			{
				leftp.Reset();
				current_animation = &leftp;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP)
		{
			allowtime = true;
			time = SDL_GetTicks();
			if (current_animation != &rightp)
			{
				rightp.Reset();
				current_animation = &rightp;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_S]
			&& App->input->keyboard[SDL_SCANCODE_W])
		{
			current_animation = &idlep;
		}
		if (App->input->keyboard[SDL_SCANCODE_D]
			&& App->input->keyboard[SDL_SCANCODE_A])
		{
			current_animation = &idlep;
		}

		if (
			App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
		{
			if (SDL_GetTicks() >= time + 100)
			{
				current_animation = &idlep;
			}
		}

		// Draw everything --------------------------------------
		if (current_animation == &idlep)
		{
			player_w = 22 * 3;
			player_h = 29 * 3;
		}
		else if (current_animation == &leftp || current_animation == &rightp)
		{
			player_w = 19 * 3;
			player_h = 29 * 3;
		}
		else if (current_animation == &left1p || current_animation == &right1p)
		{
			player_w = 14 * 3;
			player_h = 29 * 3;
		}
		// Draw UI (score) --------------------------------------
		sprintf_s(score_text, 20, "SCORE", score);
		sprintf_s(scoret, 20, "%7d", score);

		// TODO 3: Blit the text of the score in at the bottom of the screen

		App->fonts->BlitText(20, 160, 0, score_text);
		App->fonts->BlitText(20, 195, 0, scoret);
	}
	

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		if (powerup_level == 0)
		{
			App->particles->AddParticle(App->particles->laser, position.x + speed + 20, position.y, COLLIDER_PLAYER_SHOT, 1);
		}
		if (powerup_level == 1)
		{
 			App->particles->AddParticle(App->particles->laser, position.x + speed, position.y, COLLIDER_PLAYER_SHOT, 1);
			App->particles->AddParticle(App->particles->laser, position.x + speed + 25, position.y, COLLIDER_PLAYER_SHOT, 1, 0, 0, 0, true);
		}

	}


	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), player_w, player_h);
	if (Player != nullptr && godmode == false)
	{
		Player->SetPos(position.x, position.y);
		Player->SetSize(player_w, player_h);
	}
	else if (Playergod != nullptr && godmode == true)
	{
		Playergod->SetPos(position.x, position.y);
		Playergod->SetSize(player_w, player_h);

	}

	// Godmode
	if (App->input->keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		if (godmode)
		{
			Playergod->SetPos(10000000, 10000000);
			godmode = false;
		}
		else if (Player != nullptr)
		{
			Player->SetPos(10000000, 10000000);
			godmode = true;
		}
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

	if (Player != nullptr && Player == c1 && deadplayer == false && c2->type != COLLIDER_POWER_UP)
	{
		lastscore = score;
		if (score >= hiscore)
		{
			hiscore = score;
		}
		score = 0;
		Disable();
		position.x = 10000000;
		position.y = 10000000;
		Player->SetPos(10000000, 10000000);
		deadplayer = true;
		allowhiscore = true;
		powerup_level = 0;
	}

	if (Player != nullptr && Player == c1 && App->player2->deadplayer && deadplayer && c2->type != COLLIDER_POWER_UP)
	{
		
		App->enemies->Disable();
		App->powerups->Disable();
		App->collision->Disable();
		App->player2->deadplayer = false;
		deadplayer = false;
		App->fade->FadeToBlack((Module*)App->map_1, (Module*)App->WelcomeScreen);
		App->enemies->EraseEnemies();
		powerup_level = 0;
		App->powerups->ErasePowerUps();
	}
}