#pragma once
#include "Projectile.h"
#include "Character.h"
class HitBox:public Projectile
{
public:
    HitBox(ProjectileManager* manager, Projectile::Faction faction, int damage, Projectile::kinds ownerId, float LifeLimit, std::shared_ptr<Sprite> s, VECTOR2 TEX_SIZE, VECTOR2 SCALE, VECTOR2 Speed, float Radius,Character* Target=nullptr);
    void init()  override;
    void deinit()override;
    void update()override;
    void render()override;
    void Launch(VECTOR2 dir, VECTOR2 pos);
};

