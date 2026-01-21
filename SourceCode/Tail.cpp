#include "Tail.h"
#include "ImageManager.h"
#include "ProjectileManager.h"

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
    alive    = true;
    velocity = { 0.0f,0.0f };
    spr      = ImageManager::Instance().getSprite(ImageManager::SpriteNum::bossUltTail);

    spawnHitBox();
}

void Tail::spawnHitBox()
{
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
    debug::setString("Pos:%f:%f", pos.x, pos.y);
}

void Tail::setDeath()
{
   alive = false; 
   ProjectileManager::Instance().targetRemove(this);
}

void Tail::deinit()
{

}

bool Tail::isDeath()
{
    if (alive)   return false;
    return true;
}

void Tail::setFunction(int num)
{
    ac->hasHit = false;
    act = 0;
 
    if (noneFlag)
    {
        move = move = &Tail::moveNone;
        return;
    }

    static moveAlg inputFunc[MAX] = {
        &Tail::moveUp,
        &Tail::moveDown,
        &Tail::moveRight,
        &Tail::moveLeft,
    };

    if (num < MAX)
    {
        ProjectileManager::Instance().targetRemove(this);
        spawnHitBox();
        move = inputFunc[num];
    }
    else
    {
        move = &Tail::moveNone;
    }
}

void Tail::moveUp(CAMERA& camera)
{
    switch (act)
    {
    case 0:
    {
        float left = camera.getPos().x+offset.x;
        float right = camera.getPos().x + SCREEN_W-offset.x;

        pos.x = rand() % (int)(right - left) + left;
        pos.y = camera.getPos().y + SCREEN_H + offset.y;//画面外ちょい下

        /* pos = { rand() % 700 + 200.0f - camera.getPos().x,SCREEN_H + 2400.0f };
         velocity = { rand() % 20 - 10.0f,-20.0f };*/

        exitPos = camera.getPos().y;
        velocity = { rand() % 10 -5.0f,-20.0f};
        act++;
    }
    case 1:
        if (pos.y < exitPos)
        {
            setFunction(rand() % MAX);
        }
        break;
    }
}

void Tail::moveDown(CAMERA& camera)
{
    switch (act)
    {
    case 0:
    {
        float left  = camera.getPos().x + offset.x;
        float right = camera.getPos().x + SCREEN_W - offset.x;

        pos.x = rand() % (int)(right - left) + left;
        pos.y = camera.getPos().y + SCREEN_H - offset.y;//画面外ちょい上
    
        exitPos = SCREEN_H + offset.y;
        velocity = { rand() % 10 - 5.0f,20.0f };
        act++;
    }
    case 1:
        if (pos.y > exitPos)
        {
            setFunction(rand() % MAX);
        }
        break;
    }
}

void Tail::moveRight(CAMERA& camera)
{
    switch (act)
    {
    case 0:
    {
        float top = camera.getPos().y + SideOffset.y;
        float bottom = camera.getPos().y + SCREEN_H + SideOffset.y;

        pos.x = camera.getPos().x - SideOffset.x;    //画面外ちょい左
        pos.y = rand() % (int)(bottom - top) + top;

        exitPos = camera.getPos().x + SCREEN_W + SideOffset.x;
        velocity = { 20.0f,rand() % 10 - 5.0f };
        act++;
    }
    case 1:
        if (pos.x > exitPos)
        {
            setFunction(rand() % MAX);
        }
        break;
    }
}

void Tail::moveLeft(CAMERA& camera)
{
    switch (act)
    {
    case 0:
    {
        float top = camera.getPos().y + SideOffset.y;
        float bottom = camera.getPos().y + SCREEN_H + SideOffset.y;

        pos.x = camera.getPos().x + SCREEN_W + SideOffset.x;    //画面外ちょい左
        pos.y = rand() % (int)(bottom - top) + top;

        exitPos = camera.getPos().x - SideOffset.x;
        velocity = { -20.0f,rand() % 10 - 5.0f };
        act++;
    }
    case 1:
        if (pos.x < exitPos)
        {
            setFunction(rand() % MAX);
        }
        break;
    }
}

void Tail::moveNone(CAMERA& camera)
{
    switch (act)
    {
    case 0:
        pos = { -2000.0f,2000.0f };
        velocity = { 0.0f,0.0f };
        act++;
    case 1:
        break;
    }
}

void Tail::setNone(bool set)
{
    noneFlag = set;
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


