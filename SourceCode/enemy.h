#pragma once
#include "../GameLib/game_lib.h"
#include "Character.h"
class Enemy :
    public Character
{
private:
    int hp = 100;
    const int coinReward;   //Œ‚”jŽž‚ÌƒRƒCƒ“
public:
    Enemy();
    Enemy(VECTOR2 Pos);
    virtual void init()override;
    virtual void deinit()override;
    virtual void update()override;
    int getCoinReward()const { return coinReward; }
    bool isAlive()override { return (hp <= 0); }
};

