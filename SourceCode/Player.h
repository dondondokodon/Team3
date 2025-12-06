#pragma once
#include "OBJ2D.h"
class Player :
    public OBJ2D
{
public:
	Player();
	void init();
	void deinit();
	void update();
};

