#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#include "Module.h"
#include "Animation.h"
#include "SDL\include\SDL_rect.h"
#include "ModuleTextures.h"

class ModuleFadeToBlack : public Module
{
public:
	ModuleFadeToBlack();
	~ModuleFadeToBlack();

	bool Init();
	update_status Update();
	bool FadeToBlack(Module* module_off, Module* module_on);
	bool IsFading();
	

private:

enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	} 
	current_step = fade_step::none;

	SDL_Texture* graphics = nullptr;
	Animation plates;
	Uint32 start_time = 0;
	Uint32 total_time = 0;
	Module* module_on1;
	Module* module_off1;
	SDL_Rect screen;
	int counter = 0;
	int font = 0;
};

#endif //__MODULEFADETOBLACK_H__