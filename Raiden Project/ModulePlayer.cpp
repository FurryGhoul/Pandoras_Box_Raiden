#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL.h"

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 150;
	position.y = 150;

	// idle animation (just the ship)
	idle.PushBack({ 3, 2, 22, 28});
	idle.loop = false;
	// move upwards

	up.PushBack({ 53, 2, 19, 28});
	up.PushBack({ 97, 2, 17, 28});
	up.loop = false;
	up.speed = 0.1f;

	// Move down

	down.PushBack({ 131, 2, 19, 28 });
	down.PushBack({ 175, 2, 17, 28 });
	down.loop = false;
	down.speed = 0.1f;
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
	int speed = 2;

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;

		if (current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
			ideling = false;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;

		if (current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
			ideling = false;
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

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT
		&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{ 
		current_animation = &idle;
		ideling = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &idle;
		ideling = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE 
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE 
		&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE && ideling == false)
	{
		current_animation = &idle;
		ideling = true;
	}
	// Draw everything --------------------------------------

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}