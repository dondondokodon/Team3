#pragma once
#include"Player.h"

//インターフェイス
class IEnemySpawnRule
{
protected:
	int spawnNum = 0;
public:
	virtual ~IEnemySpawnRule() = default;
	virtual void update() = 0;
	void setSpawnNum(int num) { spawnNum = num; }
	int getSpawnNum(){ return spawnNum; }
};
