#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 21

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class Module;
class ModuleMap1;
class ModuleMap2;
class ModuleAudio1;
class ModuleAudio2;
class ModuleWelcomeScreen;
class ModuleStageClear1;
class ModuleFadeToBlack;
class ModulePlayer;
class ModuleParticles;
class ModuleCollision;
class ModuleEnemies;
class ModulePlayer2;
class ModulePowerUps;
class ModuleFonts;
class ModuleShadows;
class ModuleGroundExplosion;
class ModuleGroundEnemies;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleAudio1 * audio;
	ModuleMap1 * map_1;
	ModuleMap2* map_2;
	ModuleAudio2* audio_2;

	ModuleWelcomeScreen* WelcomeScreen;
	ModuleStageClear1* StageClear1;
	ModuleFadeToBlack* fade;
	ModulePlayer* player;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModuleEnemies* enemies;
	ModulePlayer2* player2;
	ModulePowerUps* powerups;
	ModuleFonts* fonts;
	ModuleShadows* shadows;
	ModuleGroundExplosion* gexplosion;
	ModuleGroundEnemies* genemies;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__