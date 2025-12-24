#include "Projectile.h"
#include "ProjectileManager.h"

Projectile::Projectile(ProjectileManager* manager, Faction faction, int damage, int ownerId) : manager(manager), faction(faction), damage(damage), ownerId(ownerId)
{
	manager->Register(this);
}

void Projectile::Destroy()
{
	manager->Remove(this);
}