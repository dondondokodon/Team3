#pragma once
#include<vector>
#include<memory>
#include"Enemy.h"
#include"CAMERA.h"
#include"ProjectileManager.h"
#include"EnemySpawnRule.h"

enum class EnemyType
{
	FlyEye,
};

class EnemyManager
{
public:
	void add(std::unique_ptr<Enemy> enemy)
	{
		enemy->init();
		enemies.push_back(std::move(enemy));
	}

	static EnemyManager& instance()
	{
		static EnemyManager inst;
		return inst;
	}

	void update(CAMERA camera);
	void render(CAMERA camera);
	void init();
	void clear();
	//エネミー数取得
	int GetEnemyCount() const { return static_cast<int>(enemies.size()); }
	//エネミー取得
	Enemy* GetEnemy(int index) { return enemies.at(index).get(); }
	void setTarget(Character& t) { target = &t; }

	VECTOR2 setSpawnPos();
	void setCamera(CAMERA& cam) { camera = &cam; }
	void setCameraNull() { camera = nullptr; }
	void Spawn(EnemyType type,VECTOR2 pos);
	//void setSpawnRule(std::unique_ptr<IEnemySpawnRule> rule);
	void setStage(int stageNo);

private:
	std::vector<std::unique_ptr<Enemy>> enemies;
	//コンストラクタ系禁止　シングルトン
	EnemyManager(){}
	EnemyManager(const EnemyManager& e){}
	EnemyManager& operator=(const EnemyManager& e){}
	Character* target;
	std::shared_ptr<Sprite> enemyBullet;
	CAMERA* camera = nullptr;
	std::unique_ptr<IEnemySpawnRule> spawnRule;
};

