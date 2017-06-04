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
#include"ModuleWelcomeScreen.h"
#include "ModuleAudio_2.h"
#include "ModuleShadows.h"

#include <stdio.h>

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;
	bomb_ammo = NULL;

	InitialPos();

	// Idle animation
	idle.PushBack({ 3, 2, 22, 28 });

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

	//Bomb ammo
	bomb1.PushBack({ 236, 132, 16, 14 });
	bomb2.PushBack({ 236, 132, 32, 14 });
	bomb3.PushBack({ 236, 132, 48, 14 });
	bomb4.PushBack({ 236, 132, 64, 14 });
	bomb5.PushBack({ 236, 132, 80, 14 });
	bomb6.PushBack({ 236, 132, 96, 14 });
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Init()
{
	LOG("Loading player");

	graphics = App->textures->Load("Assets/Player2.png");
	graphics2 = App->textures->Load("Assets/graphics2.png");
	Player = App->collision->AddCollider({ 0, 0, player_w, player_h }, COLLIDER_PLAYER, this, 4); // Bullettype 4 differentiate the player colliders
	Playergod = App->collision->AddCollider({ 0, 0, player_w, player_h }, COLLIDER_GOD, this, 4);
	Player->SetPos(82938, 2323);
	score = 0;
	font_score = App->fonts->Load("Assets/Font.png", "> ?@ABCDEFGHIJKLMNOPQRSTUVWXYZ!¡?_^#$%&'()x+.-,;tpsczpc/0123456789:", 3);

	/*
	@ = "copyright symbol"
	¡ = smaller "!"
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
bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	App->fonts->UnLoad(font_score);

	return true;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	if (bombs < 0)
	{
		bombs = 0;
	}
	else if (bombs > 6)
	{
		bombs = 6;
	}

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

	float speed = 3.6;

	if (propeller)
	{
		if ((App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && !App->input->gpad2) || (App->input->joystickpos2[3] == KEY_STATE::KEY_REPEAT && App->input->gpad2))
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
				shadowdirection = 1;
			}

			if (current_animation != &left1 && SDL_GetTicks() >= (time + 300))
			{
				left1.Reset();
				current_animation = &left1;
				shadowdirection = 2;
			}

			if (App->map_1->IsEnabled() && position.x >= 10)
			{
				position.x -= speed;
			}
		}

		if ((App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && !App->input->gpad2) || (App->input->joystickpos2[4] == KEY_STATE::KEY_REPEAT && App->input->gpad2))
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
				shadowdirection = 3;
			}

			if (current_animation != &right1 && SDL_GetTicks() >= (time + 300))
			{
				right1.Reset();
				current_animation = &right1;
				shadowdirection = 4;
			}

			if (App->map_1->IsEnabled() && position.x <= 594)
			{
				position.x += speed;

			}
		}

		if ((App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT && !App->input->gpad2) || (App->input->joystickpos2[2] == KEY_STATE::KEY_REPEAT && App->input->gpad2))
		{
			position.y += speed;

			if (App->map_1->IsEnabled() && position.y >= 740)
			{
				position.y -= speed;

			}
		}

		if ((App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && !App->input->gpad2) || (App->input->joystickpos2[1] == KEY_STATE::KEY_REPEAT && App->input->gpad2))
		{
			position.y -= speed;

			if (App->map_1->IsEnabled() && position.y <= -1)
			{
				position.y += speed;
			}
		}

		if ((App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN && !App->input->gpad2) || (App->input->joystickpos2[3] == KEY_STATE::KEY_DOWN && App->input->gpad2))
		{
			allowtime = true;
			time = SDL_GetTicks();
			if (current_animation != &left)
			{
				left.Reset();
				current_animation = &left;
				shadowdirection = 1;
			}
		}

		if ((App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN && !App->input->gpad2) || (App->input->joystickpos2[4] == KEY_STATE::KEY_DOWN && App->input->gpad2))
		{
			allowtime = true;
			time = SDL_GetTicks();
			if (current_animation != &right)
			{
				right.Reset();
				current_animation = &right;
				shadowdirection = 3;
			}
		}

		if (((App->input->keyboard[SDL_SCANCODE_DOWN] && !App->input->gpad2) || (App->input->joystickpos2[2] && App->input->gpad2))
			&& ((App->input->keyboard[SDL_SCANCODE_UP] && !App->input->gpad2) || (App->input->joystickpos2[1] && App->input->gpad2)))
		{
			current_animation = &idle;
			shadowdirection = 0;
		}
		if (((App->input->keyboard[SDL_SCANCODE_RIGHT] && !App->input->gpad2) || (App->input->joystickpos2[4] && App->input->gpad2))
			&& ((App->input->keyboard[SDL_SCANCODE_LEFT] && !App->input->gpad2) || (App->input->joystickpos2[3] && App->input->gpad2)))
		{
			current_animation = &idle;
			shadowdirection = 0;
		}

		if (((App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE && !App->input->gpad2) || (App->input->joystickpos2[3] == KEY_STATE::KEY_IDLE && App->input->gpad2))
			&& ((App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE && !App->input->gpad2) || (App->input->joystickpos2[4] == KEY_STATE::KEY_IDLE && App->input->gpad2)))
		{
			if (SDL_GetTicks() >= time + 100)
			{
				current_animation = &idle;
				shadowdirection = 0;
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
		sprintf_s(score_text, 20, "2UP", score);
		sprintf_s(scoret, 20, "%7d", score);
	}

	else
	{
		if ((App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && !App->input->gpad2) || (App->input->joystickpos2[3] == KEY_STATE::KEY_REPEAT && App->input->gpad2))
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
				shadowdirection = 1;
			}

			if (current_animation != &left1p && SDL_GetTicks() >= (time + 300))
			{
				left1p.Reset();
				current_animation = &left1p;
				shadowdirection = 2;
			}

			if (App->map_1->IsEnabled() && position.x >= 10)
			{
				position.x -= speed;
			}
		}

		if ((App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && !App->input->gpad2) || (App->input->joystickpos2[4] == KEY_STATE::KEY_REPEAT && App->input->gpad2))
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
				shadowdirection = 3;
			}

			if (current_animation != &right1p && SDL_GetTicks() >= (time + 300))
			{
				right1p.Reset();
				current_animation = &right1p;
				shadowdirection = 4;
			}

			if (App->map_1->IsEnabled() && position.x <= 594)
			{
				position.x += speed;
			}
		}

		if ((App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT && !App->input->gpad2) || (App->input->joystickpos2[2] == KEY_STATE::KEY_REPEAT && App->input->gpad2))
		{
			position.y += speed;

			if (App->map_1->IsEnabled() && position.y >= 740)
			{
				position.y -= speed;
			}
		}

		if ((App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && !App->input->gpad2) || (App->input->joystickpos2[1] == KEY_STATE::KEY_REPEAT && App->input->gpad2))
		{
			position.y -= speed;

			if (App->map_1->IsEnabled() && position.y <= -1)
			{
				position.y += speed;
			}
		}

		if ((App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN && !App->input->gpad2) || (App->input->joystickpos2[3] == KEY_STATE::KEY_DOWN && App->input->gpad2))
		{
			allowtime = true;
			time = SDL_GetTicks();
			if (current_animation != &leftp)
			{
				leftp.Reset();
				current_animation = &leftp;
				shadowdirection = 1;
			}
		}

		if ((App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN && !App->input->gpad2) || (App->input->joystickpos2[4] == KEY_STATE::KEY_DOWN && App->input->gpad2))
		{
			allowtime = true;
			time = SDL_GetTicks();
			if (current_animation != &rightp)
			{
				rightp.Reset();
				current_animation = &rightp;
				shadowdirection = 3;
			}
		}

		if (((App->input->keyboard[SDL_SCANCODE_DOWN] && !App->input->gpad2) || (App->input->joystickpos2[2] && App->input->gpad2))
			&& ((App->input->keyboard[SDL_SCANCODE_UP] && !App->input->gpad2) || (App->input->joystickpos2[1] && App->input->gpad2)))
		{
			current_animation = &idlep;
			shadowdirection = 0;
		}
		if (((App->input->keyboard[SDL_SCANCODE_RIGHT] && !App->input->gpad2) || (App->input->joystickpos2[4] && App->input->gpad2))
			&& ((App->input->keyboard[SDL_SCANCODE_LEFT] && !App->input->gpad2) || (App->input->joystickpos2[3] && App->input->gpad2)))
		{
			current_animation = &idlep;
			shadowdirection = 0;
		}

		if (((App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE && !App->input->gpad2) || (App->input->joystickpos2[3] == KEY_STATE::KEY_IDLE && App->input->gpad2))
			&& ((App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE && !App->input->gpad2) || (App->input->joystickpos2[4] == KEY_STATE::KEY_IDLE && App->input->gpad2)))
		{
			if (SDL_GetTicks() >= time + 100)
			{
				current_animation = &idlep;
				shadowdirection = 0;
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
		sprintf_s(score_text, 20, "2UP", score);
		sprintf_s(scoret, 20, "%7d", score);
	}

	if ((App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN && bombs >= 1 && SDL_GetTicks() - bombtime >= 2100) && !App->input->gpad2)
	{
		App->particles->AddParticle(App->particles->bomb, position.x + speed + 20, position.y, COLLIDER_NONE, 48);
		bombs--;
		bombtime = SDL_GetTicks();
		Mix_PlayChannel(-1, App->audio_2->fx_bomb_drop, 0);
	}
	else if ((App->input->gamepad2[0] == KEY_STATE::KEY_DOWN && bombs >= 1 && SDL_GetTicks() - bombtime >= 2100) && App->input->gpad2)
	{
		App->particles->AddParticle(App->particles->bomb, position.x + speed + 20, position.y, COLLIDER_NONE, 48);
		bombs--;
		bombtime = SDL_GetTicks();
		Mix_PlayChannel(-1, App->audio_2->fx_bomb_drop, 0);
	}

	if ((App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && !App->input->gpad2) || (App->input->gamepad2[2] == KEY_STATE::KEY_DOWN && App->input->gpad2))
	{
		
		if (red == true)
		{
			Mix_PlayChannel(-1, App->audio_2->fx_shoot, 0);
			if (powerup_level <= 0)
			{
				App->particles->AddParticle(App->particles->double_shot, position.x + 25, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 1);

				if (score < 0)
					score = 0;
			}
			if (powerup_level == 1)
			{
				App->particles->AddParticle(App->particles->double_shot, position.x + 10, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 1);
				App->particles->AddParticle(App->particles->double_shot, position.x + 35, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1);

				if (score < 0)
					score = 0;
			}
			if (powerup_level == 2)
			{
				App->particles->AddParticle(App->particles->double_shot, position.x + 25, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 1);
				App->particles->AddParticle(App->particles->double_shot, position.x + 35, position.y, COLLIDER_PLAYER_SHOT, 2, 3, 0, 0, true, 1);
				App->particles->AddParticle(App->particles->double_shot, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 2, -3, 0, 0, true, 1);

				if (score < 0)
					score = 0;
			}
			if (powerup_level == 3)
			{
				App->particles->AddParticle(App->particles->triple_shot, position.x + 20, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 2);
				App->particles->AddParticle(App->particles->triple_shot, position.x + 30, position.y, COLLIDER_PLAYER_SHOT, 2, 3, 0, 0, true, 2);
				App->particles->AddParticle(App->particles->triple_shot, position.x + 10, position.y, COLLIDER_PLAYER_SHOT, 2, -3, 0, 0, true, 2);

				if (score < 0)
					score = 0;
			}
			if (powerup_level == 4)
			{
				App->particles->AddParticle(App->particles->double_shot, position.x + 25, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 1);
				App->particles->AddParticle(App->particles->double_shot, position.x + 35, position.y, COLLIDER_PLAYER_SHOT, 2, 3, 0, 0, true, 1);
				App->particles->AddParticle(App->particles->double_shot, position.x + 45, position.y, COLLIDER_PLAYER_SHOT, 2, 5, 0, 0, true, 1);
				App->particles->AddParticle(App->particles->double_shot, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 2, -3, 0, 0, true, 1);
				App->particles->AddParticle(App->particles->double_shot, position.x, position.y, COLLIDER_PLAYER_SHOT, 2, -5, 0, 0, true, 1);

				if (score < 0)
					score = 0;
			}
			if (powerup_level == 5)
			{
				App->particles->AddParticle(App->particles->triple_shot, position.x + 25, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 2);
				App->particles->AddParticle(App->particles->triple_shot, position.x + 30, position.y, COLLIDER_PLAYER_SHOT, 2, 3, 0, 0, true, 2);
				App->particles->AddParticle(App->particles->triple_shot, position.x + 30, position.y, COLLIDER_PLAYER_SHOT, 2, 6, 0, 0, true, 2);
				App->particles->AddParticle(App->particles->triple_shot, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 2, -3, 0, 0, true, 2);
				App->particles->AddParticle(App->particles->triple_shot, position.x + 10, position.y, COLLIDER_PLAYER_SHOT, 2, -6, 0, 0, true, 2);

				if (score < 0)
					score = 0;
			}
			if (powerup_level == 6)
			{
				App->particles->AddParticle(App->particles->quad_shot, position.x + 25, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 3);
				App->particles->AddParticle(App->particles->quad_shot, position.x + 30, position.y, COLLIDER_PLAYER_SHOT, 2, 3, 0, 0, true, 3);
				App->particles->AddParticle(App->particles->quad_shot, position.x + 35, position.y, COLLIDER_PLAYER_SHOT, 2, 5, 0, 0, true, 3);
				App->particles->AddParticle(App->particles->quad_shot, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 2, -3, 0, 0, true, 3);
				App->particles->AddParticle(App->particles->quad_shot, position.x - 5, position.y, COLLIDER_PLAYER_SHOT, 2, -5, 0, 0, true, 3);

				if (score < 0)
					score = 0;
			}
			if (powerup_level >= 7)
			{
				App->particles->AddParticle(App->particles->quad_shot, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 3);

				//Right
				App->particles->AddParticle(App->particles->quad_shot_right1, position.x + 12, position.y, COLLIDER_PLAYER_SHOT, 2, 3, 0, 0, true, 3);
				App->particles->AddParticle(App->particles->quad_shot_right2, position.x, position.y + 20, COLLIDER_PLAYER_SHOT, 2, 5, 0, 0, true, 3, false, 27);
				App->particles->AddParticle(App->particles->quad_shot_right2, position.x, position.y + 50, COLLIDER_PLAYER_SHOT, 2, 8, 0, 0, true, 3, false, 27);

				//Left
				App->particles->AddParticle(App->particles->quad_shot_left1, position.x, position.y, COLLIDER_PLAYER_SHOT, 2, -3, 0, 0, true, 3, false, -3);
				App->particles->AddParticle(App->particles->quad_shot_left2, position.x, position.y + 20, COLLIDER_PLAYER_SHOT, 2, -5, 0, 0, true, 3, false, -3);
				App->particles->AddParticle(App->particles->quad_shot_left2, position.x, position.y + 50, COLLIDER_PLAYER_SHOT, 2, -8, 0, 0, true, 3, false, -3);

				if (score < 0)
					score = 0;
			}
		}
		if (red == false)
		{
			Mix_PlayChannel(-1, App->audio_2->fx_blue_shoot, 0);
			if (powerup_level <= 1)
			{
				App->particles->AddParticle(App->particles->laser, position.x + 30, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 1);
				App->particles->AddParticle(App->particles->laser, position.x + 30, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false);

				if (score < 0)
					score = 0;
			}
			if (powerup_level == 2)
			{
				App->particles->AddParticle(App->particles->laser, position.x + 30, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 1);
				App->particles->AddParticle(App->particles->laser, position.x + 30, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false);
				App->particles->AddParticle(App->particles->laser, position.x + 30, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false);
				App->particles->AddParticle(App->particles->laser, position.x + 30, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false);
				App->particles->AddParticle(App->particles->laser, position.x + 30, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false);

				if (score < 0)
					score = 0;
			}
			if (powerup_level == 3)
			{
				// row 1
				App->particles->AddParticle(App->particles->laser2, position.x + 13, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 1);
				App->particles->AddParticle(App->particles->laser2, position.x + 45, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1);
				//row 2
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 12);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 45);
				//row 3
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 12);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 45);
				//row 4
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 12);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 45);
				//row 5
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 12);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 45);


				if (score < 0)
					score = 0;
			}
			if (powerup_level == 4)
			{
				// row 1
				App->particles->AddParticle(App->particles->laser2, position.x + 5, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 1);
				App->particles->AddParticle(App->particles->laser2, position.x + 29, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1);
				App->particles->AddParticle(App->particles->laser2, position.x + 52, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1);
				//row 2
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 5);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 29);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 52);
				//row 3
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 12);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 45);
				//row 4
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 12);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 45);
				//row 5
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 12);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 45);
				//row 6
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 5, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 12);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 5, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 45);
			}
			if (powerup_level == 5)
			{
				// row 1
				App->particles->AddParticle(App->particles->laser2, position.x + 5, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 1);
				App->particles->AddParticle(App->particles->laser2, position.x + 29, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1);
				App->particles->AddParticle(App->particles->laser2, position.x + 52, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1);
				//row 2
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 5);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 29);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 52);
				//row 3
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 5);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 29);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 52);
				//row 4
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 5);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 29);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 52);
				//row 5
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 5);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 29);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 52);
				//row 6
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 5, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 5);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 5, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 29);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 5, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 52);

			}
			if (powerup_level == 6)
			{
				// row 1
				App->particles->AddParticle(App->particles->laser2, position.x + 13, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 1);
				App->particles->AddParticle(App->particles->laser2, position.x + 45, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1);
				App->particles->AddParticle(App->particles->laser2, position.x - 10, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1);
				App->particles->AddParticle(App->particles->laser2, position.x + 67, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1);
				//row 2
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 13);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 45);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, -10);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 67);
				//row 3
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 5);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 29);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 52);
				//row 4
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 5);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 29);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 52);
				//row 5
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 5);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 29);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 52);
				//row 6
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 5, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 5);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 5, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 29);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 5, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 52);
			}
			if (powerup_level == 7)
			{
				// row 1
				App->particles->AddParticle(App->particles->laser2, position.x + 13, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 1);
				App->particles->AddParticle(App->particles->laser2, position.x + 45, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1);
				App->particles->AddParticle(App->particles->laser2, position.x - 10, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1);
				App->particles->AddParticle(App->particles->laser2, position.x + 67, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1);
				//row 2
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 13);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 45);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, -10);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 67);
				//row 3
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 13);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 45);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, -10);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 67);
				//row 4
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 13);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 45);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, -10);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 67);
				//row 5
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 13);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 45);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, -10);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 67);
				//row 6
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 5, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 13);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 5, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 45);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 5, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, -10);
				App->particles->AddParticle(App->particles->laser2, position.x, position.y + 48 * 5, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 1, false, 67);
			}
			if (powerup_level >= 8)
			{
				App->particles->AddParticle(App->particles->final_laser, position.x + 5, position.y, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, false, 4);
				App->particles->AddParticle(App->particles->final_laser, position.x, position.y + 48, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 4, false, 5);
				App->particles->AddParticle(App->particles->final_laser, position.x, position.y + 48 * 2, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 4, false, 5);
				App->particles->AddParticle(App->particles->final_laser, position.x, position.y + 48 * 3, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 4, false, 5);
				App->particles->AddParticle(App->particles->final_laser, position.x, position.y + 48 * 4, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 4, false, 5);
				App->particles->AddParticle(App->particles->final_laser, position.x, position.y + 48 * 5, COLLIDER_PLAYER_SHOT, 2, 0, 0, 0, true, 4, false, 5);

				if (score < 0)
					score = 0;
			}
		}
		//Missiles
		if (can_shoot == true && missile_powerup_level != 0)
		{ 
		if (missile_powerup_level == 1)
		{
			App->particles->AddParticle(App->particles->player_light_missile, position.x + 35, position.y, COLLIDER_PLAYER_SHOT, -1, 2, -10, 1, false, 1);
			App->particles->AddParticle(App->particles->player_light_missile, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, -1, -2, -10, 1, false, 1);
		}
		if (missile_powerup_level == 2)
		{
			App->particles->AddParticle(App->particles->player_mid_missiles, position.x + 45, position.y + 35, COLLIDER_PLAYER_SHOT, -1, -2, -15, 1, false, 2);
			App->particles->AddParticle(App->particles->player_mid_missiles, position.x + 5, position.y + 35, COLLIDER_PLAYER_SHOT, -1, 2, -15, 1, false, 2);
			App->particles->AddParticle(App->particles->player_mid_missiles, position.x + 25, position.y - 10, COLLIDER_PLAYER_SHOT, -1, 0, -15, 1, false, 2);
		}
		if (missile_powerup_level == 3)
		{
			App->particles->AddParticle(App->particles->player_mid_missiles, position.x + 55, position.y + 25, COLLIDER_PLAYER_SHOT, -1, -1, -15, 1, false, 2);
			App->particles->AddParticle(App->particles->player_mid_missiles, position.x + 45, position.y + 35, COLLIDER_PLAYER_SHOT, 1, -1, -18, 1, false, 2);
			App->particles->AddParticle(App->particles->player_mid_missiles, position.x - 5, position.y + 35, COLLIDER_PLAYER_SHOT, 1, 1, -18, 1, false, 2);
			App->particles->AddParticle(App->particles->player_mid_missiles, position.x - 15, position.y + 25, COLLIDER_PLAYER_SHOT, -1, 1, -15, 1, false, 2);
		}
		if (missile_powerup_level == 4)
		{
			App->particles->AddParticle(App->particles->heavy_missiles, position.x + 55, position.y + 25, COLLIDER_PLAYER_SHOT, -1, -1, -15, 1, false, 3);
			App->particles->AddParticle(App->particles->heavy_missiles, position.x + 35, position.y + 35, COLLIDER_PLAYER_SHOT, -1, 1, -18, 1, false, 3);
			App->particles->AddParticle(App->particles->heavy_missiles, position.x + 5, position.y + 35, COLLIDER_PLAYER_SHOT, -1, -1, -18, 1, false, 3);
			App->particles->AddParticle(App->particles->heavy_missiles, position.x - 15, position.y + 25, COLLIDER_PLAYER_SHOT, -1, 1, -15, 1, false, 3);
			
		}
		missiles_shot++;
		}
}
//Missiles time control
if (missiles_shot == 2 && can_shoot == true)
{
	can_shoot = false;
	missiles_initial_time = SDL_GetTicks();


}
if (SDL_GetTicks() - missiles_initial_time > 500 && can_shoot == false)
{
	can_shoot = true;
	missiles_shot = 0;
}
	if (bombs == 1)
	{
		bomb_ammo = &bomb1;
		bombammo_w = 16 * 3;
	}
	else if (bombs == 2)
	{
		bomb_ammo = &bomb2;
		bombammo_w = 32 * 3;
	}
	else if (bombs == 3)
	{
		bomb_ammo = &bomb3;
		bombammo_w = 48 * 3;
	}
	else if (bombs == 4)
	{
		bomb_ammo = &bomb4;
		bombammo_w = 64 * 3;
	}
	else if (bombs == 5)
	{
		bomb_ammo = &bomb5;
		bombammo_w = 80 * 3;
	}
	else if (bombs == 6)
	{
		bomb_ammo = &bomb6;
		bombammo_w = 96 * 3;
	}
	else if (bombs == 0)
	{
		bomb_ammo = nullptr;
	}

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), player_w, player_h);

	if (shadowregulator % 2 == 0)
	{
		if (shadowdirection == 0)
			App->shadows->AddShadow(App->shadows->Player, position.x, position.y, 38 * 3, 26 * 3);
		else if (shadowdirection == 1)
			App->shadows->AddShadow(App->shadows->Playerleft, position.x, position.y, 38 * 3, 26 * 3);
		else if (shadowdirection == 2)
			App->shadows->AddShadow(App->shadows->Playerleft1, position.x, position.y, 38 * 3, 26 * 3);
		else if (shadowdirection == 3)
			App->shadows->AddShadow(App->shadows->Playerright, position.x, position.y, 38 * 3, 26 * 3);
		else if (shadowdirection == 4)
			App->shadows->AddShadow(App->shadows->Playerright1, position.x, position.y, 38 * 3, 26 * 3);
	}

	shadowregulator++;

	if (Player != nullptr && godmode == false)
	{
		Player->SetPos(position.x + 17, position.y + 20);
		Player->SetSize(player_w / 2, player_h / 2);
	}
	else if (Playergod != nullptr && godmode == true)
	{
		Playergod->SetPos(position.x + 17, position.y + 20);
		Playergod->SetSize(player_w / 2, player_h / 2);

	}

	// Godmode
	if ((App->input->keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN) || (App->input->gamepad[4] == KEY_STATE::KEY_DOWN && App->input->gpad2))
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

	// Debug purpuses
	if (App->input->keyboard[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN)
	{
		powerup_level++;
	}
	if (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN)
	{
		powerup_level--;
	}
	if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_DOWN)
	{
		if (red != true)
		{
			red = true;
		}
		else
		{
			red = false;
		}
	}
	if (powerup_level >= 8)
	{
		powerup_level = 8;
	}
	if (powerup_level <= 0)
	{
		powerup_level = 0;
	}


	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{

	if (Player != nullptr && Player == c1 && deadplayer == false && c2->type != COLLIDER_POWER_UP)
	{
		if (c2->bullettype == 5)
			score += 480;

		lastscore = score;
		if (score >= hiscore)
		{
			hiscore = score;
		}

		App->particles->AddParticle(App->particles->player_explosion, position.x, position.y, COLLIDER_NONE);
		Mix_PlayChannel(-1, App->audio_2->fx_heavy_ground_explosion, 0);
		Disable();
		position.x = 10000000;
		position.y = 10000000;
		Player->SetPos(10000000, 10000000);
		deadplayer = true;
		allowhiscore = true;
     	}

	if (Player != nullptr && Player == c1 && App->player->deadplayer && deadplayer && c2->type != COLLIDER_POWER_UP && !App->fade->IsFading())
	{
		App->WelcomeScreen->setdown = true;
		if (App->player->lives == 0)
		{
			App->fade->FadeToBlack((Module*)App->map_1, (Module*)App->WelcomeScreen);

		}
		else
		{
			App->map_1->reset_collision = true;
		}
	}
}