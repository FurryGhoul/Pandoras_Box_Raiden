#pragma once
#ifndef __PATH_H__
#define __PATH_H__

#include "p2Point.h"
#include "Animation.h"
#define MAX_STEPS 100

struct Step
{
	uint frames = 1;
	fPoint speed;
	Animation* animation = nullptr;
};

class Path
{
public:
	bool loop = true;
	Step steps[MAX_STEPS];
	fPoint accumulated_speed = { 0.0f, 0.0f };

private:
	uint current_frame = 0;
	uint last_step = 0;

public:

	void PushBack(fPoint speed, uint frames, Animation* animation = nullptr)
	{
		steps[last_step].animation = animation;
		steps[last_step].frames = frames;
		steps[last_step++].speed = speed;
	}

	fPoint GetCurrentPosition(Animation** current_animation = nullptr)
	{
		current_frame += 1;

		uint count = 0;
		uint i = 0;
		bool need_loop = true;
		for (; i < last_step; ++i)
		{
			count += steps[i].frames;
			if (current_animation != nullptr)
				*current_animation = steps[i].animation;
			if (count >= current_frame)
			{
				accumulated_speed += steps[i].speed;
				need_loop = false;
				break;
			}
		}

		if (need_loop && loop)
			current_frame = 0;

		return fPoint((int)accumulated_speed.x, (int)accumulated_speed.y);
	}
	int GetCurrentStep()
	{
		int i = 0;
		int count = 0;
		while(i < last_step)
		{
			
			count += steps[i].frames;
			if (count >= current_frame)
			{
				break;
			}
			++i;
		}
		return i;
	}
	void Reset()
	{
		current_frame = 0;
	}
};

#endif // __PATH_H__