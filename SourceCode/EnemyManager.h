#pragma once
#include<vector>
#include<memory>
#include"Enemy.h"
#include"CAMERA.h"
#include"ProjectileManager.h"
class EnemyManager
{
public:
	void add(std::unique_ptr<Enemy> enemy)
	{
		enemies.push_back(std::move(enemy));
	}

	static EnemyManager& instance()
	{
		static EnemyManager inst;
		return inst;
	}

	void update();
	void render(CAMERA camera);
	void init();
	void clear();

private:
	std::vector<std::unique_ptr<Enemy>> enemies;
	//コンストラクタ系禁止　シングルトン
	EnemyManager(){}
	EnemyManager(const EnemyManager& e){}
	EnemyManager& operator=(const EnemyManager& e){}
};

