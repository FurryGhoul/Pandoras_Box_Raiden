#include "Globals.h"
#include "Application.h"
#include "ModuleMap2.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleMap1.h"

ModuleWelcomeScreen::ModuleWelcomeScreen() : Module()
{

}
ModuleWelcomeScreen::~ModuleWelcomeScreen()
{

}

bool ModuleWelcomeScreen::Init()
{
	LOG("Loading background assets");

	ground = { 0, 0 ,224 * 4 ,256 * 4};
	Welcome = App->textures->Load("WelcomeScreen.png");
	return true;
}

update_status ModuleWelcomeScreen::Update()
{

	App->render->Blit(Welcome, 160, 0, &ground);
	return UPDATE_CONTINUE;
}

bool ModuleWelcomeScreen::CleanUp()
{
	return true;
}