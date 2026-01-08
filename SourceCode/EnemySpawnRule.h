#pragma once
#include"Player.h"

//インターフェイス
class IEnemySpawnRule
{
public:
	virtual ~IEnemySpawnRule() = default;

	virtual void update() = 0;

};
