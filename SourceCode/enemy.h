#pragma once
#include "Character.h"
class Enemy :
    public Character
{
private:
    int hp = 100;
    const int coinReward;   //Œ‚”j‚ÌƒRƒCƒ“
public:
    Enemy();
    virtual void init()override;
    virtual void deinit()override;
    virtual void update()override;
    int getCoinReward()const { return coinReward; }
    bool isAlive()override { return (hp <= 0); }
};

