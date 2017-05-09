#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 10000

#include "Module.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )
enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_POWER_UP,
	COLLIDER_TANK,
	COLLIDER_GOD,
	COLLIDER_BOMB,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	int bullettype = 0;
	int damage = 0;
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr, int bullettype = 0, int damage = 0) :
		rect(rectangle),
		type(type),
		callback(callback),
		bullettype(bullettype),
		damage(damage)
	{}

	void SetPos(int x, int y)
	{
 		rect.x = x;
		rect.y = y;
	}

	void SetSize(int w, int h)
	{
		rect.w = w;
		rect.h = h;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();
	//update_status PostUpdate();
	bool CleanUp();
	void Erase_Non_Player_Colliders();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr, int bullettype = 0, int damage = 0);
	
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
};

#endif // __ModuleCollision_H__