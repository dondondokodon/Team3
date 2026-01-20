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
    float radius,
    Character* Target,
    std::shared_ptr<AttackContext> ac) :Projectile(manager, Projectile::Faction::enemy,damage, ownerId, LifeLimit, s, TEX_SIZE, SCALE, Speed, Dadius),owner(owner),offset(offset),ac(ac)
{
    texPos = { 0,0 };
    pivot = { texSize.x*0.5f,texSize.y*0.5f };
    color = { 1,1,1,1 };
    angle = 0;
    target = Target;
}


void TailHitCircle::update()
{
    if (!owner) { Destroy(); return; }

    dir = { owner->getDir().x ,0.0f};               // 前後方向
    VECTOR2 up = { dir.y, -dir.x };      // 上方向

    //pos =
    //    owner->getPos()
    //    + dir * offset.x   // 前後
    //    + up * offset.y;  // 上下

    pos = owner->getPos()+offset;
}

bool TailHitCircle::onHit()
{
    if (ac->hasHit)   return false;

    ac->hasHit = true;
    Projectile::onHit();
    return true;
}


//Tailクラス
void Tail::init()
{
    Character::init();
    alive = false;
    velocity = { 0.0f,0.0f };

    constexpr int NUM = 5;
    constexpr float INTERVAL = 80.0f;

    for (int i = 0;i < NUM;i++)
    {
       /* TailBigActionHitBox(ProjectileManager::Instance(),
            

        )*/
    }
}

void Tail::update()
{
    pos + velocity;
    angle = atan2(velocity.y, velocity.x);
}


//Tailクラスで使う当たり判定
TailBigActionHitBox::TailBigActionHitBox(
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
):TailHitCircle(manager,damage,ownerId,LifeLimit,s,TEX_SIZE,SCALE,Speed,Dadius,owner,offset,radius,Target,ac)
{

}

void TailBigActionHitBox::update()
{
    if (!target) { Destroy(); return; }

    pos = target->getPos() + rotate(offset, target->getAngle());
}