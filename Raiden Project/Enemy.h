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
	Uint32 hittime = 0;
	bool ishit;
	bool ishit2;
	bool ishit3;
	bool ishit4;
	fPoint distance;
	fPoint distance1;
	fPoint distance2;
	int hp;
	bool getvector = true; //For kamikazes
	bool deployed = false; //For boss kamikazes
	bool allowbombtime = true; //allows timer
	bool bombimmunity = false;
	Uint32 btime = 0;
	Uint32 btime2 = 0;
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
	int gspritesheet;
	int animations; // How much animations does the enemy have
	bool bonusplane = false; // Bollean to detect if the enemy is a bonus plane and adapt the hitbox and drop a powerup
	bool medalbox = false; //Boolean to detect if the enemy rewards a medal when killed
	bool kamikaze = false;
	bool powerupbox = false;
	bool lightshooter = false;
	bool mediumshooter = false; // Bollean to detect if the enemy is a medium plane and adapt the hitbox
	bool light_kamikaze = false;
	bool ship = false; //Boolena to detect if the enemy is a ship
	float left_right_mod = 0; // Integer to modify the position of the enemy
	bool tank = false; //Boolean to detect if the enemy is  a tank
	bool longmegatank = false; //Boolena to detect if the enemy is a megatank
	bool shiptank = false; //Boolena to detect if the enemy is a ship tank
	bool megatank = false;
	bool bossmain = false;
	bool bossleftwing = false;
	bool bossrightwing = false;
	bool bosscannon = false;
	bool turretexploded = false; // Bool to know if a tank's turret has already exploded or not
	bool greytank = false;
	bool mine = false;
	bool trainlocomotive = false;
	bool traincoach = false;
	int modifier = 0;

public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void MoveShoot() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider); 
};

#endif // __ENEMY_H__