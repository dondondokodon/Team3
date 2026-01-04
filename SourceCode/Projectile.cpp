#include "Projectile.h"
#include "ProjectileManager.h"

Projectile::Projectile(ProjectileManager* manager, Faction faction, int damage, int ownerId,float LifeLimit,std::shared_ptr<Sprite> s,VECTOR2 TEX_SIZE,VECTOR2 SCALE) : manager(manager), faction(faction), damage(damage), ownerId(ownerId),lifeLimit(LifeLimit)
{
	scale = SCALE;
	texSize = TEX_SIZE;
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