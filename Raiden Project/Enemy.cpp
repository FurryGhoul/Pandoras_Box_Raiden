#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

Enemy::Enemy(int x, int y) : position(x, y)
{

}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (animations >= 1)
	{ 
	    if (animation != nullptr)
		{ 
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()),w,h);
		}
	}
	if (animations >= 2)
	{
		if (animation != nullptr)
		{
			App->render->Blit(sprites, position.x, position.y, &(animation1->GetCurrentFrame()), w, h);
		}
	}
	if (animations >= 3)
	{
		if (animation != nullptr)
		{
			App->render->Blit(sprites, position.x, position.y, &(animation2->GetCurrentFrame()), w, h);
		}
	}
	if (animations >= 4)
	{
		if (animation != nullptr)
		{
			App->render->Blit(sprites, position.x, position.y, &(animation3->GetCurrentFrame()), w, h);
		}
	}

}

void Enemy::OnCollision(Collider* collider)
{
	
	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
}