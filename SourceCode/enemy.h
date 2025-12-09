#pragma once
#include "Character.h"
class Enemy :
    public Character
{
private:
    int hp = 100;
public:
    Enemy();
    void init()override;
    void deinit()override;
    void update()override;
    bool isAlive()override { return (hp <= 0); }
};

