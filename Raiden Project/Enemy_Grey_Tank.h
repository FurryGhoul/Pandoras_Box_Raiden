#include "Enemy.h"
#include "Turret.h"
class Enemy_Grey_Tank : public Enemy
{
private:
	//Tank animations
	Animation downup;
	Animation leftright;
	Animation neutraldiagonalleft;
	Animation downdiagonalleft;
	Animation updiagonalleft;
	Animation neutraldiagonalright;
	Animation downdiagonalright;
	Animation updiagonalright;

	Animation _downup;
	Animation _leftright;
	Animation _neutraldiagonalleft;
	Animation _downdiagonalleft;
	Animation _updiagonalleft;
	Animation _neutraldiagonalright;
	Animation _downdiagonalright;
	Animation _updiagonalright;

	Animation hitdownup;
	Animation hitleftright;
	Animation hitneutraldiagonalleft;
	Animation hitdowndiagonalleft;
	Animation hitupdiagonalleft;
	Animation hitneutraldiagonalright;
	Animation hitdowndiagonalright;
	Animation hitupdiagonalright;
	//Turret animations
	Animation noturret;
	Animation s;
	Animation n;
	Animation e;
	Animation w11;
	Animation se1;
	Animation ne1;
	Animation sw1;
	Animation nw1;
	Animation se2;
	Animation ne2;
	Animation sw2;
	Animation nw2;
	Animation se3;
	Animation ne3;
	Animation sw3;
	Animation nw3;

	Animation hits;
	Animation hitn;
	Animation hite;
	Animation hitw11;
	Animation hitse1;
	Animation hitne1;
	Animation hitsw1;
	Animation hitnw1;
	Animation hitse2;
	Animation hitne2;
	Animation hitsw2;
	Animation hitnw2;
	Animation hitse3;
	Animation hitne3;
	Animation hitsw3;
	Animation hitnw3;
	double param;
	double angle;
	bool ne = false;
	bool se = false;
	bool nw = false;
	bool sw = false;
	bool turretalive = true; // Bool to see if the turret is still alive
	int shooting = 0;
	int time_controll = 0;





	fPoint original_pos;

	Path movement;
public:
	Enemy_Grey_Tank(int, int, int path);

	void MoveShoot();
};
