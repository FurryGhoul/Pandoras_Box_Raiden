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

};

#endif // __ModuleAudio_H__