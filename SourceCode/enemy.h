#pragma once
#include "../GameLib/game_lib.h"
#include "Character.h"
class Enemy :
    public Character
{
private:
    int hp = 100;
    const int coinReward;   //Œ‚”jŽž‚ÌƒRƒCƒ“

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
    virtual void update()override;
    virtual void state();
    int getCoinReward()const { return coinReward; }
    bool isAlive()override { return (hp <= 0); }
};

