#pragma once
#include<memory>
#include "ProjectileManager.h"
#include "Character.h"

class AttackContext
{
public:
    bool hasHit = false;
};

//ATTACK2で使うもの
class TailHitCircle : public Projectile
{
public:
    Character* owner;   // ボス or プレイヤー
    VECTOR2 offset;       // 体からの距離
    VECTOR2 dir;        // 向き
    std::shared_ptr<AttackContext> ac;   //当たったかどうか

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
        float radius,
        Character* Target,
        std::shared_ptr<AttackContext> ac
    );

    void update() override;
    bool onHit()override;
};

//大技で使う　描画あり
class Tail:public Character
{
private:
    VECTOR2 velocity;
    bool alive;

public:
    void init();
    void update();
};

class TailBigActionHitBox :public TailHitCircle
{
public:

    TailBigActionHitBox(
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
        float radius,
        Character* Target,
        std::shared_ptr<AttackContext> ac
    );

    //void init();
    void update();
};

