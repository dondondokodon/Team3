#pragma once
#include "OBJ2D.h"
class Character :
    public OBJ2D
{
public:
	virtual ~Character() {}
	virtual void init()    = 0;
	virtual void deinit()  = 0;
	virtual void update(){}	//エネミーで違うUpdate使うからフック
	virtual bool isDeath() = 0;
public:
	int atk = 0;	//攻撃力
};

