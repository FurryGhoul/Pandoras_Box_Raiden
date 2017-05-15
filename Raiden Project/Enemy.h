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
	fPoint position;
	fPoint position1;
	fPoint position2;
	fPoint position3;
	bool ishit;
	bool ishit2;
	fPoint distance;
	fPoint distance1;
	fPoint distance2;
	int hp;
	bool getvector = true; //For kamikazes
	Uint32 bombhittime; //time between allowed bomb hits
	bool allowbombtime = true; //allows timer
	bool bombimmunity = false;
	int hitbybomb = 0;
	uint points;
	int h;
	int w;
	int h1;
	int w1;
	int h2;
	int w2;
	int h3;
	int w3;
	int spritesheet;
	int animations; // How much animations does the enemy have
	bool bonusplane = false; // Bollean to detect if the enemy is a bonus plane and adapt the hitbox and drop a powerup
	bool medalbox = false; //Boolean to detect if the enemy rewards a medal when killed
	bool kamikaze = false;
	bool powerupbox = false;
	bool lightshooter = false;
	bool mediumshooter = false; // Bollean to detect if the enemy is a medium plane and adapt the hitbox
	float left_right_mod = 0; // Integer to modify the position of the enemy
	bool tank = false; //Boolean to detect if the enemy is  a tank
	bool megatank = false; //Boolena to detect if the enemy is a megatank

public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void MoveShoot() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider); 
};

#endif // __ENEMY_H__