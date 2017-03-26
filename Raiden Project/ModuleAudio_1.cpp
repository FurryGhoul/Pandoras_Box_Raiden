#include "Globals.h"
#include "Application.h"
#include "ModuleAudio_1.h"

ModuleAudio1::ModuleAudio1() : Module()
{

}

ModuleAudio1::~ModuleAudio1()
{

}

bool ModuleAudio1::Init()
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
	ModuleAudio1::Load("song.ogg");

	if (Mix_PlayMusic(music, -1) == -1)
	{
		LOG("An error has ocurred while reproducing the audio %s", SDL_GetError())
	}
	return true;
}

Mix_Music* const ModuleAudio1::Load(const char* path)
{

	music = Mix_LoadMUS(path);
	if (music == NULL)
	{
		LOG("An error has ocurred when loading the sound: %s", SDL_GetError())
	}

	return music;
}
bool ModuleAudio1::CleanUp()
{
	Mix_CloseAudio();
	Mix_FreeMusic(music);
	return true;
}
