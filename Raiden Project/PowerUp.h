#pragma once
#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "p2Point.h"
#include "Animation.h"
#include "Path.h"

struct SDL_Texture;
struct Collider;

class PowerUp : public Path
{
protected:
	Animation* animation = nullptr;
	Collider* collider = nullptr;

public:
	fPoint position;
	int h;
	int w;
	float left_right_mod = 0;
	bool bluep = false;
	bool redp = false;

public:
	PowerUp(int x, int y);
	virtual ~PowerUp();

	const Collider* GetCollider() const;

	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);
	virtual void Move(){}
};

#endif // __POWERUP_H__