#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

ModuleRender::ModuleRender() : Module()
{}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	tex = App->textures->Load("Tilemaptest.png");
	
	// TODO 9: load a texture "test.png" to test is everything works well

	return ret;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(App->render->renderer,0, 0, 0, 255);

	if (SDL_RenderClear(App->render->renderer) == -1)
	{
		LOG("An error has ocurred when clearing the screen %s", SDL_GetError());
	}


	SDL_Rect rect;
	rect.h = 3266;
	rect.w = 352;
	App->render->Blit(tex, xmap, ymap, &rect);
	// TODO 7: Clear the screen to black before starting every frame
	
	// TODO 10: Blit our test texture to check functionality

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	// TODO 8: Switch buffers so we actually render
	SDL_RenderPresent(App->render->renderer);
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if(renderer != nullptr)
	{ 
		SDL_DestroyRenderer(renderer);
    }
	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	
	if(section != nullptr)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}
	
	rect.w *= 4;
	rect.h *= 4;
	
	if(SDL_RenderCopy(renderer, texture, NULL, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}