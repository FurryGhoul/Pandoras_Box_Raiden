#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleShadows.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMap1.h"
#include "ModuleMap2.h"
#include "ModuleStageClear1.h"

ModuleShadows::ModuleShadows()
{
	for (uint i = 0; i < MAX_ACTIVE_SHADOWS; ++i)
		active[i] = nullptr;
}

ModuleShadows::~ModuleShadows()
{}

// Load assets
bool ModuleShadows::Init()
{
	LOG("Loading shadows");
	graphics = App->textures->Load("Assets/Shadows.png");

	//Player's shadow
	Player.anim.PushBack({ 32, 65, 12, 11 });
	Player.anim.loop = true;
	Player.anim.speed = 1.0f;
	Player.size.x = 12 * 3;
	Player.size.y = 11 * 3;
	//Player's left shadow
	Playerleft.anim.PushBack({ 59, 65, 12, 11 });
	Playerleft.anim.loop = true;
	Playerleft.anim.speed = 1.0f;
	Playerleft.size.x = 12 * 3;
	Playerleft.size.y = 11 * 3;
	//Player's left shadow 1
	Playerleft1.anim.PushBack({ 47, 65, 12, 11 });
	Playerleft1.anim.loop = true;
	Playerleft1.anim.speed = 1.0f;
	Playerleft1.size.x = 12 * 3;
	Playerleft1.size.y = 11 * 3;
	//Player's right shadow
	Playerright.anim.PushBack({ 7, 65, 12, 11 });
	Playerright.anim.loop = true;
	Playerright.anim.speed = 1.0f;
	Playerright.size.x = 12 * 3;
	Playerright.size.y = 11 * 3;
	//Player's right shadow 1
	Playerright1.anim.PushBack({ 20, 65, 12, 11 });
	Playerright1.anim.loop = true;
	Playerright1.anim.speed = 1.0f;
	Playerright1.size.x = 12 * 3;
	Playerright1.size.y = 11 * 3;
	//Bonus ship´s shadow
	Bonusship.anim.PushBack({ 0, 0, 28, 27 });
	Bonusship.anim.loop = true;
	Bonusship.anim.speed = 1.0f;
	Bonusship.size.x = 28 * 3;
	Bonusship.size.y = 27 * 3;
	//Mine's shadow
	Mine.anim.PushBack({ 30, 0, 11, 19 });
	Mine.anim.loop = true;
	Mine.anim.speed = 1.0f;
	Mine.size.x = 11 * 3;
	Mine.size.y = 19 * 3;
	//Kamikaze's shadow
	Kamikazes.anim.PushBack({ 44, 1, 17, 14 });
	Kamikazes.anim.loop = true;
	Kamikazes.anim.speed = 1.0f;
	Kamikazes.size.x = 17 * 3;
	Kamikazes.size.y = 14 * 3;
	//Mediumshooter front shadow
	MediumFront.anim.PushBack({ 66, 0, 41, 30 });
	MediumFront.anim.loop = true;
	MediumFront.anim.speed = 1.0f;
	MediumFront.size.x = 41 * 3;
	MediumFront.size.y = 30 * 3;
	//Mediumshooter back shadow
	MediumBack.anim.PushBack({ 111, 0, 41, 30 });
	MediumBack.anim.loop = true;
	MediumBack.anim.speed = 1.0f;
	MediumBack.size.x = 41 * 3;
	MediumBack.size.y = 30 * 3;
	//Boss main shadow
	bossmain.anim.PushBack({ 20, 33, 44, 22 });
	bossmain.anim.loop = true;
	bossmain.anim.speed = 1.0f;
	bossmain.size.x = 44 * 3;
	bossmain.size.y = 22 * 3;
	//Boss left wing shadow
	bossleftwing.anim.PushBack({ 4, 46, 15, 9 });
	bossleftwing.anim.loop = true;
	bossleftwing.anim.speed = 1.0f;
	bossleftwing.size.x = 15 * 3;
	bossleftwing.size.y = 9 * 3;
	//Boss right wing shadow
	bossrightwing.anim.PushBack({ 65, 46, 15, 9 });
	bossrightwing.anim.loop = true;
	bossrightwing.anim.speed = 1.0f;
	bossrightwing.size.x = 15 * 3;
	bossrightwing.size.y = 9 * 3;
	//Boss cannon
	bosscannon.anim.PushBack({ 83, 58, 14, 8 });
	bosscannon.anim.loop = true;
	bosscannon.anim.speed = 1.0f;
	bosscannon.size.x = 14 * 3;
	bosscannon.size.y = 8 * 3;
	return true;
}

// Unload assets
bool ModuleShadows::CleanUp()
{
	LOG("Unloading shadows");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_SHADOWS; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleShadows::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_SHADOWS; ++i)
	{
		Shadow* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
			continue;
		}

			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), p->size.x, p->size.y);
	}

	return UPDATE_CONTINUE;
}


void ModuleShadows::AddShadow(const Shadow& shadow, float x, float y, float distancex, float distancey)
{
	for (uint i = 0; i < MAX_ACTIVE_SHADOWS; ++i)
	{
		if (active[i] == nullptr)
		{
			Shadow* p = new Shadow(shadow);
			p->born = SDL_GetTicks();
			p->position.x = (x + distancex);
			p->position.y = (y + distancey);
			p->size = shadow.size;

			active[i] = p;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

void ModuleShadows::MoveShadowsRight(bool right)
{
	if (right == true)
	{
		for (uint i = 0; i < MAX_ACTIVE_SHADOWS; ++i)
		{
			if (active[i] != nullptr)
			{
				active[i]->position.x += App->map_1->xscrollspeed;
			}
		}
	}

	if (right == false)
	{
		for (uint i = 0; i < MAX_ACTIVE_SHADOWS; ++i)
		{
			if (active[i] != nullptr)
			{
				active[i]->position.x -= App->map_1->xscrollspeed;
			}
		}
	}
}
void ModuleShadows::EraseShadows()
{
	for (uint i = 0; i < MAX_ACTIVE_SHADOWS; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

}

Shadow::Shadow()
{
	position.SetToZero();
}

Shadow::Shadow(const Shadow& p) :
	anim(p.anim), position(p.position), born(p.born), life(p.life)
{}

Shadow::~Shadow()
{}

bool Shadow::Update()
{

	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
		{
			ret = false;
		}

	}
	else if (anim.Finished())
			ret = false;

	return ret;
}
