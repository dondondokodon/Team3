#include "StageSpawnRules.h"
#include "EnemyManager.h"

std::unique_ptr<IEnemySpawnRule> SpawnRuleFactory::create(int stageNo)
{
	//ステージ番号に応じて生成
	switch (stageNo)
	{
	case 1:
		return std::make_unique<Statge1SpawnRule>();

	case 2:
		return std::make_unique<Stage2SpawnRule>();

	default:
		return nullptr;
	}
}


//ステージ１
void Statge1SpawnRule::update()
{
	//最大数チェック  最大数ならリターン
	if (EnemyManager::instance().GetEnemyCount() >= 4)	return;

	//沸き位置設定
	VECTOR2 pos = EnemyManager::instance().setSpawnPos();

	//生成
	EnemyManager::instance().Spawn(EnemyType::FlyEye, pos);
}



//ステージ２
void Stage2SpawnRule::update()
{
	//最大数チェック  最大数ならリターン
	if (EnemyManager::instance().GetEnemyCount() >= 1)	return;

	//沸き位置設定
	VECTOR2 pos = EnemyManager::instance().setSpawnPos();

	//生成
	EnemyManager::instance().Spawn(EnemyType::BOSS, pos);
}