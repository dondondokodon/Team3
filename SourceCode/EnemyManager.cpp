#include "EnemyManager.h"

void EnemyManager::update(CAMERA camera)
{
	int num = 0;	//ループ回数　デバッグ用
	for (auto it = enemies.begin(); it != enemies.end(); )
	{
		(*it)->update(camera);
		debug::setString("Enemy[%d]HP:%d", num,(*it)->getHp());
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