#include "Projectile.h"
#include "ProjectileManager.h"

Projectile::Projectile(ProjectileManager* manager, Owner owner, int damage, int ownerId) : manager(manager), owner(owner), damage(damage), ownerId(ownerId)
{
	manager->Register(this);
}

void Projectile::Destroy()
{
	manager->Remove(this);
}