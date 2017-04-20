#pragma once
#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"


#define MAX_ENEMIES 100

enum ENEMY_TYPES
{
	NO_TYPE,
    LIGHT_SHOOTER,
	BONUS_SHIP,
	TANK,
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	bool AddEnemy(ENEMY_TYPES type, int x, int y);

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
	SDL_Texture* sprites2;
	SDL_Texture* sprites3;
	
	
};

#endif // __ModuleEnemies_H__