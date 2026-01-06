#include "EnemyManager.h"
#include "ProjectileManager.h"
#include "ProjectileStraight.h"

void EnemyManager::update(CAMERA camera)
{
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
			ProjectileStraight* projectile=new ProjectileStraight(&ProjectileManager::Instance(), Projectile::Faction::enemy, (*it)->getATK(),-1,1.5f,enemyBullet,VECTOR2{44,66}, VECTOR2{ 1,1 },VECTOR2{8,8});
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