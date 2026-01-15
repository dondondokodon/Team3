#pragma once
#include "Projectile.h"
#include "Character.h"
#include "common.h"

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

//いったんやめる
//きもいけどプレイヤーとエイリアンのしっぽやるためだけにこれにする
//class Player_HitBox
//{
//private:
//    VECTOR2 pos;
//    VECTOR2 scale;
//    float radius;
//    Character* target;
//    Player_HitBox(){}
//
//public:
//
//    static Player_HitBox& Instance()
//    {
//        static Player_HitBox instance;
//        return instance;
//    }
//
//    void setTarget(Character* t) { target = t; }
//
//    bool HitCheck(const Character c)
//    {
//        return hitCircle(pos, radius, c.getPos(), c.getRadius());
//    }
//};

