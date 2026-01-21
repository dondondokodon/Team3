#include "EnemyManager.h"
#include "ProjectileManager.h"
#include "ProjectileStraight.h"
#include<cstdlib>
#include<memory>
#include"StageSpawnRules.h"
#include"ImageManager.h"
#include"EnemyBoss.h"
#include"HitBox.h"

void EnemyManager::update(CAMERA camera)
{
	if (spawnRule)	spawnRule->update();

	int num = 0;	//ループ回数　デバッグ用
	for (auto it = enemies.begin(); it != enemies.end(); )
	{
		if (target)		//ターゲットがnullじゃなければ
		(*it)->update(camera,target->getPos());
		debug::setString("Enemy[%d]HP:%d", num,(*it)->getHp());
		//ターゲットとして参照している球を全て消す
		if ((*it)->getIsTargetRemoveOn())	ProjectileManager::Instance().targetRemove((*it).get());
		//攻撃
		if ((*it)->getIsAttackOn())
		{
			switch ((*it)->getAttackType())
			{
			case Enemy::ATTACK_TYPE::bulet:
			{
				//球を打つ
				ProjectileStraight* projectile = new ProjectileStraight(&ProjectileManager::Instance(), Projectile::Faction::enemy, (*it)->getATK(), Projectile::kinds::enemy, 1.5f, enemyBullet, VECTOR2{ 44,66 }, VECTOR2{ 1,1 }, VECTOR2{ 8,8 }, (*it)->getRadius());
				projectile->Launch((*it)->shotDir(target->getPos()), (*it)->getPos());
				break;
			}
			case Enemy::ATTACK_TYPE::melle:
			{
				//近接用
				HitBox* melle = new HitBox(&ProjectileManager::Instance(), Projectile::Faction::enemy, (*it)->getATK(), Projectile::kinds::enemy, 0.0f, std::shared_ptr<Sprite>(nullptr), VECTOR2{ 100,100 }, VECTOR2{ 1,1 }, VECTOR2{ 0,0 }, (*it)->getMelleRadius(), (*it).get());
				break;
			}
			}
			
		}
		//死んでたら
		if ((*it)->isDeath())
		{
			(*it)->deinit();
			//it = enemies.erase(it); // eraseは次のiteratorを返す
			removeList.insert(it->get());
		}
		++it;
		++num;
	}

	removeList.clear();
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
	enemyBullet=ImageManager::Instance().getSprite(ImageManager::SpriteNum::EnemyBullet);
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
	pos.y = rand() % 450+100;

	return pos;
}

void EnemyManager::Spawn(EnemyType type, VECTOR2 pos)
{
	switch (type)
	{
	case EnemyType::FlyEye:
		add(std::make_unique<Enemy>(pos));
		break;

	case EnemyType::BOSS:
		add(std::make_unique<EnemyBoss>(pos));
		break;
	}
}

void EnemyManager::setStage(int stageNo)
{
	spawnRule = SpawnRuleFactory::create(stageNo);
}