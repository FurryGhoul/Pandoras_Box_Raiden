#include "Enemy_Light_Shooter_Kamikaze.h"
#include "Enemy_Light_Shooter.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"



Light_Shooter_Kamikaze::Light_Shooter_Kamikaze(int x, int y, int path) : Enemy(x, y)
{
	hp = 1;
	points = 130;
	light_kamikaze = true;
	// Anmiation pushback's

	//South to East
	flys.PushBack({ 16, 58, 27, 20 });
	flyse1.PushBack({ 291, 23, 26, 21 });
	flyse2.PushBack({ 250, 19, 26, 25 });
	flyse3.PushBack({ 211, 18, 22, 25 });

	// East to North
	flye.PushBack({ 178, 20, 20, 23 });
	flyne1.PushBack({ 136, 19, 24, 24 });
	flyne2.PushBack({ 100, 18, 26, 24 });
	flyne3.PushBack({ 58, 18, 27, 22 });

	//North to West
	flyn.PushBack({ 16, 18, 27, 20}); 
	flynw1.PushBack({ 291, 54, 24, 24 });
	flynw2.PushBack({ 243, 53, 27, 25 });
	flynw3.PushBack({ 205, 56, 27, 23 });

	//West to South
	flyw.PushBack({ 174, 55, 20, 23 });
	flysw1.PushBack({ 134, 55, 22, 25 });
	flysw2.PushBack({ 98, 54, 22, 25 });
	flysw3.PushBack({ 54, 56, 25, 25 });
}


Light_Shooter_Kamikaze::~Light_Shooter_Kamikaze()
{
}
