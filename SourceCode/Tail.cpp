#include "Tail.h"
#include "ImageManager.h"

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
    pos      = { 0.0f,3000.0f};
    scale    = { -1.0f,1.0f };
    color    = { 1.0f,1.0f,1.0f,1.0f };
    texPos   = { 0.0f,0.0f };
    texSize  = { 1280.0f,50.0f };
    pivot    = {texSize.x,texSize.y*0.5f };
    angle    = 0;
    ac       = std::make_shared<AttackContext>();
    //alive  = false;
    velocity = { 0.0f,0.0f };
    spr      = ImageManager::Instance().getSprite(ImageManager::SpriteNum::bossUltTail);

    constexpr int NUM = 17;
    constexpr float INTERVAL = 80.0f;

    for (int i = 0;i < NUM;i++)
    {
        new TailBigActionHitBox(&ProjectileManager::Instance(),
            100,
            Projectile::kinds::enemy,
            999,
            nullptr,
            { 50.0f,50.0f },
            { 1.0f,1.0f },
            { 0.0f,0.0f },
            25.0f,
            this,
            { i * INTERVAL,0.0f },
            40.0f,
            this,
            ac
        );
    }
}

void Tail::update(CAMERA& camera)
{
    if(move)
    (this->*move)(camera);
    pos += velocity;
    angle = atan2(velocity.y, velocity.x);
}

void Tail::deinit()
{

}

bool Tail::isDeath()
{
    return false;
}

void Tail::setFunction(int num)
{
    static moveAlg inputFunc[MAX] = {
        &Tail::moveUp
    };

    if (num < MAX)
    {
        move         = inputFunc[num];
        ac->hasHit   = false;
        act          = 0;
    }
}

void Tail::moveUp(CAMERA& camera)
{
    switch (act)
    {
    case 0:
        pos = { rand() % 700 + 200.0f - camera.getPos().x,SCREEN_H + 2400.0f };
        velocity = { rand() % 20 - 10.0f,-20.0f };
        act++;
        
    case 1:
        break;
    }
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
    if (!target||target->isDeath()) { Destroy(); return; }

    pos = target->getPos() + rotate(offset, target->getAngle());
}

