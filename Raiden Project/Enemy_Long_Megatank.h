
#include "Enemy.h"
class Enemy_Long_Megatank : public Enemy
{
private:
	Animation shellstart;
	Animation transformation;
	Animation transformation2;
	Animation transformation3;
	Animation transformation4;
	Animation finalform;
	Animation stop;

	Animation hitshell;
	Animation hittransformation;
	Animation hittransformation2;
	Animation hittransformation3;
	Animation hittransformation4;
	Animation hitfinalform;

	Animation dmgshell;
	Animation dmgtransformation;
	Animation dmgtransformation2;
	Animation dmgtransformation3;
	Animation dmgtransformation4;
	Animation dmgfinalform;
	Animation dmgstop;
	fPoint original_pos;

	Path movement;

	int shoot_time = 0;
	int time_controll = 0;
	bool shooting = false;
	bool shell = false;
	bool step1 = false;
	bool step2 = false;
	bool step3 = false;
public:
	Enemy_Long_Megatank(int x, int y, int path);

	void MoveShoot();
};

