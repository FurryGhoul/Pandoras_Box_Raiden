#include "Globals.h"
#include "Application.h"
#include "ModuleAudio_2.h"
#include "ModuleMap2.h"
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
	ModuleAudio2::Load("Assets/song_2.ogg");

	if (Mix_PlayMusic(music2, -1) == -1)
	{
		LOG("An error has ocurred while reproducing the audio %s", SDL_GetError())
	}
	return true;
}
update_status ModuleAudio2::Update()
{
	if (App->map_2->IsEnabled() && playing == false)
	{
 		Init();
		playing = true;
	}
	if (!(App->map_2->IsEnabled()) && playing == true)
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

