#include "Globals.h"
#include "Application.h"
#include "ModuleAudio_2.h"
#include "ModuleMap1.h"
#include "ModuleRender.h"
ModuleAudio2::ModuleAudio2() : Module()
{

}

ModuleAudio2::~ModuleAudio2()
{

}

bool ModuleAudio2::Init()
{
	if (Mix_Init(MIX_INIT_OGG) == 0)
	{
		LOG("An error has ocurred while initializing the audio: %s", SDL_GetError())
			return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		LOG("An error has ocurred while opening the audio has ocurred: %s", SDL_GetError())
	}
	ModuleAudio2::Load("Assets/Sound effects/song_2.ogg");

	if (Mix_PlayMusic(music2, -1) == -1)
	{
		LOG("An error has ocurred while reproducing the audio %s", SDL_GetError())
	}

     if (Mix_PlayMusic(music2, -1) == -1)
	{
		LOG("An error has ocurred while reproducing the audio %s", SDL_GetError())
	}
	fx_shoot = Mix_LoadWAV("Assets/Sound effects/red_shot1.wav");
	fx_blue_shoot = Mix_LoadWAV("Assets/Sound effects/blue_shot.wav");
	fx_light_explosion = Mix_LoadWAV("Assets/Sound effects/Light explosion.wav");
	fx_heavy_explosion = Mix_LoadWAV("Assets/Sound effects/Heavy air explosion.wav");
	fx_light_ground_explosion = Mix_LoadWAV("Assets/Sound effects/Light ground explosion.wav");
	fx_heavy_ground_explosion = Mix_LoadWAV("Assets/Sound effects/Heavy ground explosion.wav");
	fx_bomb_explosion = Mix_LoadWAV("Assets/Sound effects/Bomb's explosion.wav");
	fx_bomb_drop = Mix_LoadWAV("Assets/Sound effects/Bomb drop.wav");
	fx_medal = Mix_LoadWAV("Assets/Sound effects/Medal.wav");
	//fx_coin = Mix_LoadWAV("Assets/Sound effects/credit.wav");

	return true;
}
update_status ModuleAudio2::Update()
{
	if (App->render->camera.y > -12000 && playing == false && App->map_1->IsEnabled())
	{
		Init();
		playing = true;
	}
	if (App->render->camera.y < -12000 && playing == true || !App->map_1->IsEnabled())
	{
		playing = false;
		Close();
	}

	return UPDATE_CONTINUE;
}

Mix_Music* const ModuleAudio2::Load(const char* path)
{

	music2 = Mix_LoadMUS(path);
	if (music2 == NULL)
	{
		LOG("An error has ocurred when loading the sound: %s", SDL_GetError())
	}

	return music2;
}
bool ModuleAudio2::CleanUp()
{
	Mix_CloseAudio();
	Mix_FreeMusic(music2);
	return true;
}

bool ModuleAudio2::Close()
{
	Mix_CloseAudio();
	return true;
}

