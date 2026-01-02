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
	void ScaleReverse()		//速度に応じてスケール反転
	{
		if (!speed.x)		return;	//スピードがなければ即リターン

		//画像が左向きの時　右向きの時はscaleの符号を反転
		if (speed.x > 0)
		{
			if (scale.x > 0)		scale.x = -scale.x;
		}
		else
		{
			if (scale.x < 0)		scale.x = -scale.x;
		}
	}
	int getATK() { return atk; }

	

protected:
	int atk = 0;	//攻撃力
};

