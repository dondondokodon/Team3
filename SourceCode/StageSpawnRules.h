#pragma once
#include "EnemySpawnRule.h"
#include<memory>

//ステージ番号に応じてスポーンルールを生成する
class SpawnRuleFactory
{
public:
	static std::unique_ptr<IEnemySpawnRule> create(int stageNo);
};

//ステージ１
class Statge1SpawnRule :public IEnemySpawnRule
{
public:
	void update()override;
};

//ステージ２
class Stage2SpawnRule :public IEnemySpawnRule
{
	void update()override;
};