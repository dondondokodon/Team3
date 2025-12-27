#include"SceneGame.h"
#include<memory>
#include"../GameLib/game_lib.h"
#include"Enemy.h"
#include"EnemyManager.h"
#include"common.h"

void SceneGame::init()
{
	state = 0;
	frame = 0;
	timer = 0;
	player.init();
	stage.init();
	EnemyManager::instance().init();
	camera.init();
	camera.setStageLimitX(SCREEN_W + 500);
}

void SceneGame::update()
{
	switch (state)
	{
	case 0:
		state++;

	case 1:
		setBlendMode(Blender::BS_ALPHA);
		//エネミーセット固定
		EnemyManager::instance().add(std::make_unique<Enemy>(VECTOR2{ 1500.0f, 200.0f }));
		state++;

	case 2:

		//時間計算（秒）
		frame++;
		if (frame % 60 == 0)
			timer++;
		camera.update(player);
		player.update();
		EnemyManager::instance().update(camera);
		stage.update();

		if (player.lightAttack)
		{
			int useCoin = Coin::GetRatioCoin(0.01f);
			ProjectileStraight* b = new ProjectileStraight(&projMgr, Projectile::Faction::player, Coin::calcDamage(2, useCoin), -1);
			Coin::DegCoinNum(useCoin);
			b->Launch(player.getDir(), player.getPos());
		}
		player.lightAttack = false;

		projMgr.update();
		Collision();
		debug::setString("time:%d", timer);
		debug::setString("Coin:%d", Coin::GetCoinNum());
		debug::setString("RewardCoin:%d", Coin::RewardCoin());
		break;
	}
}

void SceneGame::render()
{
	GameLib::clear(1, 0, 1);
	stage.cameraRender(camera);
	EnemyManager::instance().render(camera);
	player.cameraRender(camera);
	player.hitAreaRender(camera);
	projMgr.Render(camera);
}


void SceneGame::deinit()
{

}

void SceneGame::deleteSprite()
{

}

void SceneGame::Collision()
{
	//player→enemy
	EnemyManager& enemyManager = EnemyManager::instance();
	int playerProjectileCount = projMgr.GetPlayerProjectileCount();
	int enemyCount = enemyManager.GetEnemyCount();
	for (int i = 0;i < playerProjectileCount; i++)
	{
		Projectile* p = projMgr.GetPlayerProjectile(i);

		for (int j = 0; j < enemyCount; j++)
		{
			Enemy* e = enemyManager.GetEnemy(j);

			if (hitCircle(p->getPos(), p->getRadius(), e->getPos(), e->getRadius()))
			{
				p->Destroy();
				e->degHp(p->getDamage());
				if (e->isDeath())
				{
					Coin::AddCoinNum(Coin::RewardCoin());
				}
			}
		}
	}


	//enemy→player
	int EnemyProjectileCount = projMgr.GetEnemyProjectileCount();
	for (int i = 0; i < EnemyProjectileCount; i++)
	{
		Projectile* e = projMgr.GetEnemyProjectile(i);

		for (int j = 0; j < enemyCount; j++)
		{

			if (hitCircle(player.getPos(), player.getRadius(), e->getPos(), e->getRadius()))
			{
				e->Destroy();

			}
		}
	}
}
