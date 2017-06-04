#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio_1.h"
#include "ModuleMap1.h"
#include "ModuleMap2.h"
#include "ModuleAudio_2.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleStageClear1.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModulePlayer2.h"
#include "ModulePowerUps.h"
#include "ModuleFonts.h"
#include "ModuleShadows.h"
#include "ModuleGroundExplosion.h"
#include "ModuleGroundEnemies.h"

Application::Application()
{	

	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = textures = new ModuleTextures();
	modules[3] = fonts = new ModuleFonts();
	modules[4] = input = new ModuleInput();
	modules[5] = audio_2 = new ModuleAudio2();
	modules[6] = map_1 = new ModuleMap1();
	modules[7] = WelcomeScreen = new ModuleWelcomeScreen();
	modules[8] = StageClear1 = new ModuleStageClear1();
	modules[9] = fade = new ModuleFadeToBlack();	
	modules[10] = gexplosion = new ModuleGroundExplosion();
	modules[11] = genemies = new ModuleGroundEnemies();
	modules[12] = shadows = new ModuleShadows();
	modules[13] = enemies = new ModuleEnemies();
	modules[14] = particles = new ModuleParticles();
	modules[15] = powerups = new ModulePowerUps();
	modules[16] = player2 = new ModulePlayer2();
	modules[17] = player = new ModulePlayer();
	modules[18] = collision = new ModuleCollision();
	modules[19] = fade = new ModuleFadeToBlack();
	modules[20] = audio = new ModuleAudio1();
}	

Application::~Application()
{
	for(int i = 0; i < NUM_MODULES; ++i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		if (modules[i]->IsEnabled())
		ret = modules[i]->PreUpdate();

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		if (modules[i]->IsEnabled())
		ret = modules[i]->Update();

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		if (modules[i]->IsEnabled())
		ret = modules[i]->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}