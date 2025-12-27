#pragma once
#include "../GameLib/game_lib.h"
#include "Character.h"
class Enemy :
    public Character
{
private:
    int hp = 100;
    const float maxSpeedX;
    const int coinReward;   //Œ‚”j‚ÌƒRƒCƒ“
    bool moveInCamera;      //ƒJƒƒ‰‚Ì’†‚É“ü‚ë‚¤‚Æ‚·‚é“®‚«‚ÌğŒ
    enum STATE
    {
        IDLE_INIT,
        IDLE,
        ATTACK1_INIT,
        ATTACK1,
        WALK_INIT,
        WALK,
    };
public:
    Enemy();
    Enemy(VECTOR2 Pos);
    virtual void init()override;
    virtual void deinit()override;
    virtual void update(CAMERA& camera);
    virtual void state();
    int getCoinReward()const { return coinReward; }
    bool isDeath()override { return (hp <= 0); }
    void degHp(int damage) { hp += -damage; }
    int getHp()const { return hp; }
    void moveHorizontalInCamera(CAMERA& camera);
    void Destroy();
};

