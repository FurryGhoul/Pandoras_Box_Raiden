#pragma once
#include "Enemy.h"
//	YOU SHOULD ONLY SPAWN KAMIKAZES IN X 0 OR X 352*3. Depending on the path you can decide the Y
class Light_Shooter_Kamikaze : public Enemy
{
private:
	Animation flys;
	Animation flyn;
	Animation flye;
	Animation flyw;
	Animation flyse1;
	Animation flyne1;
	Animation flysw1;
	Animation flynw1;
	Animation flyse2;
	Animation flyne2;
	Animation flysw2;
	Animation flynw2;
	Animation flyse3;
	Animation flyne3;
	Animation flysw3;
	Animation flynw3;
	Animation last_anim;
	fPoint original_pos;
	Path movement;
	double param;
	double angle;
	bool ne = false;
	bool se = false;
	bool nw = false;
	bool sw = false;
	bool shooting = false;
	int shoot_time = 0;
	int time;
	bool time_got = false;
	bool get_vector;
	fPoint vector;

	bool once = false; //vector has to be taken at least one
	
	bool close; //The enemy is close to the player
	bool come_right; //the enemy goes to the right
	bool anim_calculated = false; //just calculate animation once
	int anim_chill = 0;
	bool clock = false;
	Animation* pclock[16]; //array of animations in clock order
	bool spining = false;
	int anim_difference = 0; // number of animations needed to get to animation
	int anims_done = 0; //number of animations done
	int anim_doing = 0; //animation being done
public:
	Light_Shooter_Kamikaze(int x, int y, int path, bool pcome_right);
	void MoveShoot();
};

