#include "PowerUp.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"


PowerUp::PowerUp(int x, int y, double pcenterx, double pcentery, double pangle ) : position(x, y), center(pcenterx,pcentery), angle(pangle)
{}


PowerUp::~PowerUp()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* PowerUp::GetCollider() const
{
	return collider;
}

void PowerUp::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (animation != nullptr)
	{ 
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()), w, h);
	}
}

void PowerUp::OnCollision(Collider* collider)
{
	  
}