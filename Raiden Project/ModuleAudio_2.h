#ifndef __ModuleAudio_H2__
#define __ModuleAudio_H2__

#include "Module.h"
#include "Globals.h"

#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )
typedef unsigned char Uint8;

class ModuleAudio2 : public Module
{
public:

	ModuleAudio2();
	~ModuleAudio2();

	bool Init();
	Mix_Music* const Load(const char* path);
	update_status Update();
	bool CleanUp();
	bool Close();
public:
	Mix_Music* music2;
	
	bool playing = false;
	Mix_Chunk* fx_shoot;
	Mix_Chunk* fx_light_explosion;
	Mix_Chunk* fx_heavy_explosion;
	Mix_Chunk* fx_light_ground_explosion;
	Mix_Chunk* fx_heavy_ground_explosion;
	Mix_Chunk* fx_bomb_explosion;
	Mix_Chunk* fx_bomb_drop;
	Mix_Chunk* fx_medal;
	Mix_Chunk* fx_blue_shoot;
	Mix_Chunk* fx_coin;
	Mix_Chunk* fx_coin1;
	Mix_Chunk* fx_coin2;
	Mix_Chunk* fx_coin3;
	Mix_Chunk* fx_coin4;

};

#endif // __ModuleAudio_H__