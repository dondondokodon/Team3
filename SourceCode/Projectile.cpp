#include "Projectile.h"
#include "ProjectileManager.h"

Projectile::Projectile(ProjectileManager* manager, Faction faction, int damage, kinds ownerId,float LifeLimit,std::shared_ptr<Sprite> s,VECTOR2 TEX_SIZE,VECTOR2 SCALE, VECTOR2 Speed, float Radius) : manager(manager), faction(faction), damage(damage), ownerId(ownerId),lifeLimit(LifeLimit)
{
	speed = Speed;
	scale = SCALE;
	texSize = TEX_SIZE;
	radius = Radius;
	spr = s;
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