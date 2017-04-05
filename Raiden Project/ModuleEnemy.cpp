#include "ModuleEnemy.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModuleMap1.h"
#include "ModuleMap2.h"
#include "ModuleCollision.h"
ModuleEnemy::ModuleEnemy()
{

	graphics = NULL;
	current_animation = NULL;

	position.x = 305;
	position.y = 620;

	// idle animation (just the enemy ship)
	idle.PushBack({ 179, 1, 23, 30 });
	idle.loop = false;
	idle.speed = 1.0f;

}


ModuleEnemy::~ModuleEnemy()
{
}

// Load assets
bool ModuleEnemy::Init()
{
	LOG("Loading enemy");

	graphics = App->textures->Load("Assets/Light Shooter.png");
	//Enemy = App->collision->AddCollider({ 0, 0, 66, 70 }, COLLIDER_ENEMY, this);
	//Enemy->SetPos(82038, 2323);
	return true;
}

// Unload assets
bool ModuleEnemy::CleanUp()
{
	LOG("Unloading enemy");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleEnemy::Update()
{
	
	// Draw everything --------------------------------------
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), enemy_w, enemy_h);

	return UPDATE_CONTINUE;
}