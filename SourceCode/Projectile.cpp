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
	if (!animeCount)
	{
		if (animeUpdate(0, 5, 3, true))
		{
			animeCount++;
			anime_state = 0;
		}
	}
	else
	{
		if (animeUpdate(1, 5, 3, true))
		{
			anime_state = 0;
			animeCount = 0;
		}
	}
}