#pragma once
#include "OBJ2D.h"
class Character :
    public OBJ2D
{
public:
	virtual void init()    = 0;
	virtual void deinit()  = 0;
	virtual void update()  = 0;
	virtual bool isAlive() = 0;
public:
	int atk = 0;	//UŒ‚—Í
};

