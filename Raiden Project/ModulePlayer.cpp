#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModuleMap1.h"
#include "ModuleMap2.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemy.h"

ModulePlayer::ModulePlayer()
{
graphics = NULL;
	current_animation = NULL;

	position.x = 305;
	position.y = 620;

	// idle animation (just the ship)
	idle.PushBack({ 3, 2, 22, 28});
	idle.loop = false;
	idle.speed = 1.0f;

	// move right

	right.PushBack({ 53, 2, 19, 28});
	right.loop = false;
	right.speed = 1.0f;
	right1.PushBack({ 97, 2, 17, 28 });
	right1.loop = false;
	right1.speed = 1.0f;
	// Move left

	left.PushBack({ 131, 2, 19, 28 });
	left.loop = false;
	left.speed = 1.0f;
	left1.PushBack({ 175, 2, 17, 28 });
	left1.loop = false;
	left1.speed = 1.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Init()
{
	LOG("Loading player");

	graphics = App->textures->Load("Assets/Player1.png");
	Player = App->collision->AddCollider({0, 0, 66, 70}, COLLIDER_PLAYER, this);
	Player->SetPos(82938, 2323);
	return true;
}


// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	OnCollision(Player, App->enemy->Enemy);

	int speed = 3;

	Player->SetPos(position.x, position.y);

	
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

		if (App->map_1->IsEnabled() && position.x >= 20)
		{
			position.x -= speed;
		}

		if (App->map_2->IsEnabled() && position.x >= 20)
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

		if (App->map_1->IsEnabled() && position.x <= 600)
		{
			position.x += speed;
		}

		if (App->map_2->IsEnabled() && position.x <= 600)
		{
			position.x += speed;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
	}

	 if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;

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

      // TODO 3: Shoot lasers when the player hits SPACE

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{ 
		App->particles->AddParticle(App->particles->laser, position.x + speed + 20, position.y, COLLIDER_PLAYER_SHOT);
	}

	// Draw everything --------------------------------------
	if (current_animation == &idle)
	{
		player_w = 22 * 3;
		player_h = 28 * 3;
	}
	else
	{
		player_w = 17 * 3;
		player_h = 28 * 3;
	}

	

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), player_w, player_h);
   
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (Player != nullptr && Player->CheckCollision(c2->rect))
	{
		App->fade->FadeToBlack((Module*)App->map_1, (Module*)App->WelcomeScreen);
	}
}