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

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 305;
	position.y = 620;

	// idle animation (just the ship)
	idle.PushBack({ 3, 2, 22, 28});
	idle.loop = false;
	// move upwards

	right.PushBack({ 3, 2, 22, 28 });
	right.PushBack({ 53, 2, 19, 28});
	right.PushBack({ 97, 2, 17, 28});
	right.loop = false;
	right.speed = 0.1f;

	// Move down

	left.PushBack({ 3, 2, 22, 28 });
	left.PushBack({ 131, 2, 19, 28 });
	left.PushBack({ 175, 2, 17, 28 });
	left.loop = false;
	left.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Init()
{
	LOG("Loading player");

	graphics = App->textures->Load("Assets/Player1.png");
	
	return true;
}


// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	//App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 3;
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (App->map_1->IsEnabled() && position.x >= 20)
		{
			position.x -= speed;
		}

		if (App->map_2->IsEnabled() && position.x >= 20)
		{
			position.x -= speed;
		}

		if (current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		if (App->map_1->IsEnabled() && position.x <= 600)
		{
			position.x += speed;
		}

		if (App->map_2->IsEnabled() && position.x <= 600)
		{
			position.x += speed;
		}

		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
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

	// TODO 3: Shoot lasers when the player hits SPACE

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
		current_animation = &idle;
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{ 
		App->particles->AddParticle(App->particles->laser, position.x + speed + 21, position.y - 18);
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


	if (App->map_1->IsEnabled() || App->map_2->IsEnabled())
	{ 
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), player_w, player_h);
    }
	return UPDATE_CONTINUE;
}