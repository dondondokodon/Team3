#pragma once

class PlayerEffect
{
public:
	static bool attackCoinUp;
	static bool defDef;
	static void Reset()
	{
		attackCoinUp = false;
		defDef = false;
	}
};
