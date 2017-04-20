#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "Path.h"
struct SDL_Texture;
struct Collider;

class Enemy : public Path
{
protected:
	Animation* animation = nullptr;
	Animation* animation1 = nullptr;
	Animation* animation2 = nullptr;
	Animation* animation3 = nullptr;
	Collider* collider = nullptr;

public:
	iPoint position;
	int h;
	int w;
	int spriteshit;
	int animations; // How much animations does the enemy have

public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void MoveShoot() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider); 
};

#endif // __ENEMY_H__