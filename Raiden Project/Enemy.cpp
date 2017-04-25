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

	if (collider != nullptr && bonusplane == true)
		collider->SetPos(position.x + 54, position.y + 60);

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
			App->render->Blit(sprites, position1.x, position1.y, &(animation1->GetCurrentFrame()), w1, h1);
		}
	}
	if (animations >= 3)
	{
		if (animation != nullptr)
		{
			App->render->Blit(sprites, position2.x, position2.y, &(animation2->GetCurrentFrame()), w2, h2);
		}
	}
	if (animations >= 4)
	{
		if (animation != nullptr)
		{
			App->render->Blit(sprites, position3.x, position3.y, &(animation3->GetCurrentFrame()), w3, h3);
		}
	}

}

void Enemy::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y,COLLIDER_NONE);
	
}