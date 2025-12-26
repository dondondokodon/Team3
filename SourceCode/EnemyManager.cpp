#include "EnemyManager.h"

void EnemyManager::update()
{
	for (auto& e : enemies)
	{
		e->update();
	}
	//“–‚½‚è”»’è
	//€–S”»’è
		//€‚ñ‚¾‚ç”jŠü

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