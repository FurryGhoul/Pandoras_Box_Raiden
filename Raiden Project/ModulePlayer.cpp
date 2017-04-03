#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"

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
	int speed = 3;

	if (App->input->keyboard[SDL_SCANCODE_A])
	{
		position.x -= speed;

		if (current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
			ideling = false;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_D])
	{
		position.x += speed;

		if (current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
			ideling = false;
		}
	}

     if (App->input->keyboard[SDL_SCANCODE_S])
	{
		position.y += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_W])
	{
		position.y -= speed;

	}

	// TODO 3: Shoot lasers when the player hits SPACE

	if (App->input->keyboard[SDL_SCANCODE_S]
		&& App->input->keyboard[SDL_SCANCODE_W])
	{ 
		current_animation = &idle;
		ideling = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_D]
		&& App->input->keyboard[SDL_SCANCODE_A])
	{
		current_animation = &idle;
		ideling = false;
	}
	if (!(App->input->keyboard[SDL_SCANCODE_S] || App->input->keyboard[SDL_SCANCODE_D] || App->input->keyboard[SDL_SCANCODE_W] || App->input->keyboard[SDL_SCANCODE_A]) && ideling == false)
	{
		current_animation = &idle;
		ideling = true;
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE])
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
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), player_w, player_h);

	return UPDATE_CONTINUE;
}