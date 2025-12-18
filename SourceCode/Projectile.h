#pragma once
#include "OBJ2D.h"
class Projectile :public OBJ2D
{
public:
	Projectile()
	{

	}
	virtual ~Projectile(){}
	void kill() { alive = false; }
protected:
	int lifeLimit;
	int damage;
	bool alive;
	VECTOR2 dir;//Œü‚«
};

