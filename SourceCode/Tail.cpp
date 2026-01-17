#include "Tail.h"

TailHitCircle::TailHitCircle(ProjectileManager* manager,
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
    float radius) :Projectile(manager, Projectile::Faction::enemy,damage, ownerId, LifeLimit, s, TEX_SIZE, SCALE, Speed, Dadius),owner(owner),offset(offset)
{
    texPos = { 0,0 };
    pivot = { texSize.x*0.5f,texSize.y*0.5f };
    color = { 1,1,1,1 };
    angle = 0;
}


void TailHitCircle::update()
{
    if (!owner) { Destroy(); return; }

    dir = { owner->getDir().x ,0.0f};               // ëOå„ï˚å¸
    VECTOR2 up = { dir.y, -dir.x };      // è„ï˚å¸

    pos =
        owner->getPos()
        + dir * offset.x   // ëOå„
        + up * offset.y;  // è„â∫
}
