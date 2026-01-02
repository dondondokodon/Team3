#pragma once
#include "Projectile.h"
class ProjectileStraight :
    public Projectile
{
public:
    ProjectileStraight(ProjectileManager* manager, Faction faction, int damage, int ownerId, float LifeLimit);
    void init()  override;
    void deinit()override;
    void update()override;
    void render()override;
    void Launch(VECTOR2 dir, VECTOR2 pos);
};

