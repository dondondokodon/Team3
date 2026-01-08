#include "EnemyManager.h"
#include "ProjectileManager.h"
#include "ProjectileStraight.h"
#include<cstdlib>
#include<memory>
#include"StageSpawnRules.h"

void EnemyManager::update(CAMERA camera)
{
	if (spawnRule)	spawnRule->update();

	int num = 0;	//ループ回数　デバッグ用
	for (auto it = enemies.begin(); it != enemies.end(); )
	{
		if (target)		//ターゲットがnullじゃなければ
		(*it)->update(camera,target->getPos());
		debug::setString("En9emy[%d]HP:%d", num,(*it)->getHp());
		//攻撃
		if ((*it)->getIsAttackOn())
		{
			//球を打つ
			ProjectileStraight* projectile=new ProjectileStraight(&ProjectileManager::Instance(), Projectile::Faction::enemy, (*it)->getATK(),Projectile::kinds::enemy,1.5f,enemyBullet,VECTOR2{44,66}, VECTOR2{ 1,1 },VECTOR2{8,8}, (*it)->getRadius());
			projectile->Launch((*it)->shotDir(target->getPos()), (*it)->getPos());
		}
		//死んでたら
		if ((*it)->isDeath())
		{
			(*it)->deinit();
			it = enemies.erase(it); // eraseは次のiteratorを返す
		}
		else
		{
			++it;
			++num;
		}
	}
}


void EnemyManager::render(CAMERA camera)
{
	for (auto& e : enemies)
	{
		e->cameraRender(camera);
		e->hitAreaRender(camera);
	}
}

void EnemyManager::init()
{
	enemyBullet.reset(sprite_load(L"./Data/Images/bullet.png"));
	for (auto& e : enemies)
	{
		e->init();
	}
}

void EnemyManager::clear()
{
	for (auto& e : enemies)
	{
		e->deinit();
	}
	enemies.clear(); 
}

VECTOR2 EnemyManager::setSpawnPos()
{
	VECTOR2 pos;
	float SPAWN_MARGIN=200;
	int rnd_SPAWN_MARGIN = rand() % 400+500;

	//プレイヤーが右にいるなら左から沸く
	if (target->getPos().x - camera->getPos().x > SCREEN_W * 0.5f)
	{
		pos.x = camera->getPos().x - SPAWN_MARGIN- rnd_SPAWN_MARGIN;	//左画面端
	}
	else
	{
		pos.x = camera->getPos().x + SPAWN_MARGIN+SCREEN_W + rnd_SPAWN_MARGIN;	//右画面端
	}

	//yはランダム
	pos.y = rand() % 600+50;

	return pos;
}

void EnemyManager::Spawn(EnemyType type, VECTOR2 pos)
{
	switch (type)
	{
	case EnemyType::FlyEye:
		add(std::make_unique<Enemy>(pos));
		break;
	}
}

void EnemyManager::setStage(int stageNo)
{
	spawnRule = SpawnRuleFactory::create(stageNo);
}