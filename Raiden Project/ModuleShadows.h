#ifndef __MODULESHADOWS_H__
#define __MODULESHADOWS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"

#define MAX_ACTIVE_SHADOWS 10000
struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Shadow
{
	Animation anim;
	fPoint position;
	fPoint distance;
	iPoint size;
	Uint32 born = 0;
	Uint32 life = 0;

	Shadow();
	Shadow(const Shadow& p);
	~Shadow();
	bool Update();
	void SetPos(float x, float y)
	{
		position.x = (x + distance.x);
		position.y = (y + distance.y);
	}
};

class ModuleShadows : public Module
{
public:
	ModuleShadows();
	~ModuleShadows();

	bool Init();
	update_status Update();
	bool CleanUp();
	void MoveShadowsRight(bool);
	void AddShadow(const Shadow& shadow, float x, float y, float distancex, float distancey);
	void EraseShadows();

private:

	SDL_Texture* graphics = nullptr;


public:
	Shadow* active[MAX_ACTIVE_SHADOWS];
	Shadow Player;
	Shadow Playerleft;
	Shadow Playerleft1;
	Shadow Playerright;
	Shadow Playerright1;
	Shadow Bonusship;
	Shadow Mine;
	Shadow Kamikazes;
	Shadow MediumFront;
	Shadow MediumBack;
	Shadow bossmain;
	Shadow bossleftwing;
	Shadow bossrightwing;
	Shadow bosscannon;

};

#endif // __MODULESHADOWS_H__