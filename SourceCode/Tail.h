#pragma once
#include "ProjectileManager.h"
#include "Character.h"

class TailHitCircle : public Projectile
{
public:
    Character* owner;   // ボス or プレイヤー
    VECTOR2 offset;       // 体からの距離
    VECTOR2 dir;        // 向き

    TailHitCircle(
        ProjectileManager* manager,
        int damage,
        Projectile::kinds
        ownerId,
        float LifeLimit,
        std::shared_ptr<Sprite> s,
        VECTOR2 TEX_SIZE,
        VECTOR2 SCALE,
        VECTOR2 Speed, 
        float Dadius,
        Character* owner,
        VECTOR2 offset,
        float radius
    );

    void update() override;
};
