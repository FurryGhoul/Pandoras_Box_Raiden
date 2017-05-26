#include "Enemy_Megatank.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"



Enemy_Megatank::Enemy_Megatank(int x, int y, int path) : Enemy(x, y)
{
	hp = 30;
	points = 1120;

	spritesheet = 9;
	animations = 1;
	megatank = true;

	idle.PushBack({ 71,10,56,53 });

	hit.PushBack({ 242, 10, 56, 53 });

	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 14,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 128,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	spinning.PushBack({ 71,10,56,53 });
	



	spinning.loop = true;
	spinning.speed = 0.9f;

	//DMG SPINNING
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });

	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });

	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });

	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });

	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });

	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });

	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });

	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });

	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });

	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });

	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });

	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });

	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });

	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 356,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 14,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 470,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 128,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 413,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });
	dmgspinning.PushBack({ 71,10,56,53 });



	dmgspinning.loop = true;
	dmgspinning.speed = 0.9f;


	//DECELERATION
	decelaration.PushBack({ 14,10,56,53 });
	decelaration.PushBack({ 14,10,56,53 });
	decelaration.PushBack({ 14,10,56,53 });
	decelaration.PushBack({ 14,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 128,10,56,53 });
	decelaration.PushBack({ 128,10,56,53 });
	decelaration.PushBack({ 128,10,56,53 });
	decelaration.PushBack({ 128,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 14,10,56,53 });
	decelaration.PushBack({ 14,10,56,53 });
	decelaration.PushBack({ 14,10,56,53 });
	decelaration.PushBack({ 14,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 128,10,56,53 });
	decelaration.PushBack({ 128,10,56,53 });
	decelaration.PushBack({ 128,10,56,53 });
	decelaration.PushBack({ 128,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	decelaration.PushBack({ 71,10,56,53 });
	
	decelaration.loop = false;
	decelaration.speed = 0.5f;
	
	dmgdecelaration.PushBack({ 356,10,56,53 });
	dmgdecelaration.PushBack({ 356,10,56,53 });
	dmgdecelaration.PushBack({ 14,10,56,53 });
	dmgdecelaration.PushBack({ 14,10,56,53 });
	dmgdecelaration.PushBack({ 413,10,56,53 });
	dmgdecelaration.PushBack({ 413,10,56,53 });
	dmgdecelaration.PushBack({ 71,10,56,53 });
	dmgdecelaration.PushBack({ 71,10,56,53 });
	dmgdecelaration.PushBack({ 470,10,56,53 });
	dmgdecelaration.PushBack({ 470,10,56,53 });
	dmgdecelaration.PushBack({ 128,10,56,53 });
	dmgdecelaration.PushBack({ 128,10,56,53 });
	dmgdecelaration.PushBack({ 413,10,56,53 });
	dmgdecelaration.PushBack({ 413,10,56,53 });
	dmgdecelaration.PushBack({ 71,10,56,53 });
	dmgdecelaration.PushBack({ 71,10,56,53 });
	dmgdecelaration.PushBack({ 413,10,56,53 });
	dmgdecelaration.PushBack({ 413,10,56,53 });
	dmgdecelaration.PushBack({ 71,10,56,53 });
	dmgdecelaration.PushBack({ 71,10,56,53 });
	dmgdecelaration.PushBack({ 413,10,56,53 });
	dmgdecelaration.PushBack({ 413,10,56,53 });
	dmgdecelaration.PushBack({ 14,10,56,53 });
	dmgdecelaration.PushBack({ 14,10,56,53 });
	dmgdecelaration.PushBack({ 356,10,56,53 });
	dmgdecelaration.PushBack({ 356,10,56,53 });
	dmgdecelaration.PushBack({ 71,10,56,53 });
	dmgdecelaration.PushBack({ 71,10,56,53 });
	dmgdecelaration.PushBack({ 413,10,56,53 });
	dmgdecelaration.PushBack({ 413,10,56,53 });
	dmgdecelaration.PushBack({ 128,10,56,53 });
	dmgdecelaration.PushBack({ 128,10,56,53 });
	dmgdecelaration.PushBack({ 470,10,56,53 });
	dmgdecelaration.PushBack({ 470,10,56,53 });
	dmgdecelaration.PushBack({ 71,10,56,53 });
	dmgdecelaration.PushBack({ 71,10,56,53 });
	dmgdecelaration.PushBack({ 413,10,56,53 });
	dmgdecelaration.PushBack({ 413,10,56,53 });

	dmgdecelaration.loop = false;
	dmgdecelaration.speed = 0.5f;

	movement.PushBack({ 0.0f, 1.0f }, 10000);

	collider = App->collision->AddCollider({ 0, 0, 48 * 3, 45 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = 50;
	//animation = &decelaration;
}


void Enemy_Megatank::MoveShoot()
{
	w = 56 * 3;
	h = 53 * 3;

	collider->SetSize(w, h);

	position = original_pos + movement.GetCurrentPosition();
	position.x += left_right_mod;

	++charge;


	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f)
	{
		if (hp >= 10)
		{
			if (stop == false)
			{
				animation = &decelaration;
				spinning.Reset();
				spin = false;
				if (decelaration.Finished())
				{
					stop = true;
				}
				if (ishit == true)
				{
					animation = &hit;
					ishit = false;
				}

			}

			else if (stop = true)
			{
				animation = &spinning;
				decelaration.Reset();
				spin = true;
				if (spinning.Finished())
				{
					stop = false;
				}
				if (ishit == true)
				{
					animation = &hit;
					ishit = false;
				}
			}
		}
		if (hp < 10)
		{
			if (stop == false)
			{
				animation = &dmgdecelaration;
				dmgspinning.Reset();
				spin = false;
				if (dmgdecelaration.Finished())
				{
					stop = true;
				}
				if (ishit == true)
				{
					animation = &hit;
					ishit = false;
				}

			}

			else if (stop = true)
			{
				animation = &dmgspinning;
				dmgdecelaration.Reset();
				spin = true;
				if (dmgspinning.Finished())
				{
					stop = false;
				}
				if (ishit == true)
				{
					animation = &hit;
					ishit = false;
				}
			}
		}
	}

	
	if (spin == true)
	{
		charge++;
		if (charge % 110 == 0)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + 69, position.y + 45, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y - 4);
			App->particles->AddParticle(App->particles->enemyshot, position.x + 69, position.y + 45, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
		}
		if (charge % 115 == 0)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + 69, position.y + 45, COLLIDER_ENEMY_SHOT, 0, distance.x - 4, distance.y - 4);
			App->particles->AddParticle(App->particles->enemyshot, position.x + 69, position.y + 45, COLLIDER_ENEMY_SHOT, 0, distance.x + 4, distance.y);
		}
		if (charge % 120 == 0)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + 69, position.y + 45, COLLIDER_ENEMY_SHOT, 0, distance.x + 4, distance.y - 4);
			App->particles->AddParticle(App->particles->enemyshot, position.x + 69, position.y + 45, COLLIDER_ENEMY_SHOT, 0, distance.x - 4, distance.y);
		}
		if (charge % 125 == 0)
		{
			App->particles->AddParticle(App->particles->enemyshot, position.x + 69, position.y + 45, COLLIDER_ENEMY_SHOT, 0, distance.x + 6, distance.y + 1);
			App->particles->AddParticle(App->particles->enemyshot, position.x + 69, position.y + 45, COLLIDER_ENEMY_SHOT, 0, distance.x - 6, distance.y + 1);
		}
		if (charge == 126)
		{
			charge = 109;
			//charge++;
		}
	}	
}