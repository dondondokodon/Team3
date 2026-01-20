#include "Projectile.h"
#include "ProjectileManager.h"

Projectile::Projectile(ProjectileManager* manager, Faction faction, int damage, kinds ownerId,float LifeLimit,std::shared_ptr<Sprite> s,VECTOR2 TEX_SIZE,VECTOR2 SCALE, VECTOR2 Speed, float Radius) : manager(manager), faction(faction), damage(damage), ownerId(ownerId),lifeLimit(LifeLimit),target(nullptr)
{
	speed = Speed;
	scale = SCALE;
	texSize = TEX_SIZE;
	radius = Radius;
	spr = s;
	//radius = texSize.x * 0.5f;
	manager->Register(this);
}

void Projectile::Destroy()
{
	manager->Remove(this);
}

void Projectile::AnimeUpdate()
{
	animeUpdate(0, 5, 3, true);
}

void Projectile::Launch(VECTOR2 dir, VECTOR2 pos)
{
	direction = dir;
	this->pos = pos;
}

void Projectile::normalize(VECTOR2 pos1, VECTOR2 pos2)
{
	VECTOR2 Vector = pos2 - pos1;
	float len = sqrtf(Vector.x * Vector.x + Vector.y * Vector.y);

	direction.x = Vector.x / len;
	direction.y = Vector.y / len;
}

//ˆø”‚P‚ªUŒ‚‚·‚é‚Ù‚¤
bool Projectile::onHit()
{
	this->Destroy();
	return true;
}
