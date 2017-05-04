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
	iPoint position1;
	iPoint position2;
	iPoint position3;
	fPoint distance;
	iPoint distance1;
	iPoint distance2;
	uint hp;
	uint points;
	int h;
	int w;
	int h1;
	int w1;
	int h2;
	int w2;
	int h3;
	int w3;
	int spriteshit;
	int animations; // How much animations does the enemy have
	bool bonusplane = false; // Bollean to detect if the enemy is a bonus plane and adapt the hitbox
	bool medalplane = false; //Boolean to detect if the enemy rewards a medal when killed
	bool lightshooter = false;
	int left_right_mod = 0; // Integer to modify the position of the enemy
public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void MoveShoot() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider); 
};

#endif // __ENEMY_H__