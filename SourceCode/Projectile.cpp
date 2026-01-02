#include "Projectile.h"
#include "ProjectileManager.h"

Projectile::Projectile(ProjectileManager* manager, Faction faction, int damage, int ownerId,float LifeLimit) : manager(manager), faction(faction), damage(damage), ownerId(ownerId),lifeLimit(LifeLimit)
{
	manager->Register(this);
}

void Projectile::Destroy()
{
	manager->Remove(this);
}