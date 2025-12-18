#pragma once
#include "Projectile.h"
class ProjectileStraight :
    public Projectile
{
    ProjectileStraight(VECTOR2 Pos, VECTOR2 direction);
    void init()  override;
    void deinit()override;
    void update()override;
};

