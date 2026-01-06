#pragma once
#include "OBJ2D.h"
#include "Player.h"

//Žc‘œ
class Ghost :
    public OBJ2D
{
public:
    Ghost(Player& player);
    ~Ghost();
    void init()override;
    void deinit()override;
    void update()override;
    bool Remove();
};

