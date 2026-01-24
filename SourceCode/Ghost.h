#pragma once
#include "OBJ2D.h"
#include "Player.h"

//Žc‘œ
class Ghost :
    public OBJ2D
{
public:
    Ghost(Player& player);
    Ghost(Character& chara);
    ~Ghost();
    virtual void init()override;
    virtual void deinit()override;
    virtual void update()override;
    virtual bool Remove();
};

