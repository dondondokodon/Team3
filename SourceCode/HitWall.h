#pragma once
#include "../GameLib/game_lib.h"
class HitWall
{
public:
	float x;
	float top;
	float bottom;
	float dirX;
	HitWall()
	{
		x      = -1000.0f;
		top    = 0.0f;
		bottom = 0.0f;
		dirX   = 1;
	}
};

