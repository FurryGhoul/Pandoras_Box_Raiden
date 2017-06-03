#pragma once
#ifndef __ModuleGroundEnemies_H__
#define __ModuleGroundEnemies_H__

#include "Module.h"


#define MAX_GROUND_ENEMIES 10000

enum GENEMY_TYPES
{
	GNO_TYPE,
	SHIP_TANK,
	SHIP,
	LONG_MEGATANK,
	BOX_MEDAL,
	BOX_POWERUP,
	MEGATANK,
	TANK,
	GREY_TANK,
	TRAIN_LOCOMOTIVE,
	TRAIN_COACH,
};

class Enemy;

struct GroundEnemyInfo
{
	GENEMY_TYPES type = GENEMY_TYPES::GNO_TYPE;
	int x, y;
	int _path;// integer to define which path the enemy follows

};

class ModuleGroundEnemies : public Module
{
public:

	ModuleGroundEnemies();
	~ModuleGroundEnemies();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void EraseGroundEnemies();
	void OnCollision(Collider* c1, Collider* c2);
	bool AddGroundEnemy(int path, GENEMY_TYPES type, int x, int y);
	void MoveGroundEnemiesRight(bool); // The bool is used to know if the enemies should be moved to the right (true) or to the left (false)
	void SpawnGroundEnemy(const GroundEnemyInfo& info);

private:

	GroundEnemyInfo queue[MAX_GROUND_ENEMIES];
	Enemy* enemies[MAX_GROUND_ENEMIES];
	SDL_Texture* sprites;
	SDL_Texture* sprites2;
	SDL_Texture* sprites3;
	SDL_Texture* sprites4;
	SDL_Texture* sprites5;
	SDL_Texture* sprites6;
	SDL_Texture* sprites7;
	SDL_Texture* sprites8;
	SDL_Texture* sprites9;
	SDL_Texture* sprites10;
	SDL_Texture* sprites11;
	SDL_Texture* sprites12;
	SDL_Texture* sprites13;


};

#endif // __ModuleGroundEnemies_H__