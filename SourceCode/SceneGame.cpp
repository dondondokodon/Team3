#include"SceneGame.h"
#include<memory>
#include"../GameLib/game_lib.h"
#include"Enemy.h"
#include"EnemyManager.h"
#include"common.h"
#include"ProjectileManager.h"
#include"EffektManager.h"

SceneGame::SceneGame():projMgr(ProjectileManager::Instance())
{
	state = 0;
	frame = 0;
	timer = 0;
}

void SceneGame::init()
{
	state = 0;
	frame = 0;
	timer = 0;
	player.init();
	stage.init();
	EnemyManager::instance().init();
	EffektManager::Instance().init();
	camera.init();
	camera.setStageLimitX(SCREEN_W + 500);
	playerBullet = std::shared_ptr<GameLib::Sprite>(sprite_load(L"./Data/Images/1213_coin6x6.png"));
}

void SceneGame::update()
{
	switch (state)
	{
	case 0:
		state++;

	case 1:
		setBlendMode(Blender::BS_ALPHA);
		//É^Å[ÉQÉbÉgê›íË
		EnemyManager::instance().setTarget(player);
		//ÉGÉlÉ~Å[ÉZÉbÉgå≈íË
		EnemyManager::instance().add(std::make_unique<Enemy>(VECTOR2{ 1500.0f, 200.0f }));
		EnemyManager::instance().add(std::make_unique<Enemy>(VECTOR2{ -500.0f, 250.0f }));
		EnemyManager::instance().add(std::make_unique<Enemy>(VECTOR2{ -300.0f, 600.0f }));
		state++;

	case 2:

		//éûä‘åvéZÅiïbÅj
		frame++;
		if (frame % 60 == 0)
			timer++;
		camera.update(player);
		player.update();
		EnemyManager::instance().update(camera);
		EffektManager::Instance().update(camera);
		stage.update();

		//åyçUåÇ
		if (player.lightAttack)
		{
			int useCoin = Coin::GetRatioCoin(0.01f);
			ProjectileStraight* b = new ProjectileStraight(&projMgr, Projectile::Faction::player, Coin::calcDamage(2, useCoin), -1,0.7f, playerBullet,VECTOR2{6,6},VECTOR2{3,3}, VECTOR2{ 15,15 });
			Coin::DegCoinNum(useCoin);
			b->Launch(player.getDir(), player.getPos());
		}
		player.lightAttack = false;

		//èdçUåÇ
		if (player.heavyAttack)
		{
			int useCoin = Coin::GetRatioCoin(0.1f);
			VECTOR2 bulletScale = (player.getAct()==Player::HEAVY_ATTACK2)? VECTOR2{ 17.0f,17.0f}:VECTOR2{ 8.0f,8.0f };
			ProjectileStraight* projectile = new ProjectileStraight(&projMgr, Projectile::Faction::player, Coin::calcDamage(10, useCoin), -1, 0.5f, playerBullet, VECTOR2{ 6,6 }, bulletScale, VECTOR2{ 10,10 });
			Coin::DegCoinNum(useCoin);
			projectile->Launch(player.getDir(), player.getPos());
		}
		player.heavyAttack = false;

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
	EffektManager::Instance().render(camera);
	player.cameraRender(camera);
	player.hitAreaRender(camera);
	projMgr.Render(camera);
}


void SceneGame::deinit()
{
	//ìGÇÃÉNÉäÉA
	EnemyManager::instance().clear();
}

void SceneGame::deleteSprite()
{

}

void SceneGame::Collision()
{
	//playerÅ®enemy
	EnemyManager& enemyManager = EnemyManager::instance();
	int playerProjectileCount = projMgr.GetPlayerProjectileCount();
	int enemyCount = enemyManager.GetEnemyCount();
	for (int i = 0;i < playerProjectileCount; i++)
	{
		Projectile* p = projMgr.GetPlayerProjectile(i);

		for (int j = 0; j < enemyCount; j++)
		{
			Enemy* e = enemyManager.GetEnemy(j);
			if (e->getInvincibleTimer() <= 0)		//ñ≥ìGéûä‘íÜÇÕìñÇΩÇËîªíËÇéÊÇÁÇ»Ç¢
			{
				//ìñÇΩÇËîªíË
				if (hitCircle(p->getPos(), p->getRadius(), e->getPos(), e->getRadius()))
				{
					p->Destroy();
					e->degHp(p->getDamage());
					e->setInvincibleTimer(1.5f);
					if (e->isDeath())
					{
						Coin::AddCoinNum(Coin::RewardCoin());
					}
				}
			}
		}
	}


	//enemyÅ®player
	if (player.getInvincibleTimer() <= 0)		//ñ≥ìGéûä‘íÜÇÃÇ›
	{
		int EnemyProjectileCount = projMgr.GetEnemyProjectileCount();
		for (int i = 0; i < EnemyProjectileCount; i++)
		{
			Projectile* e = projMgr.GetEnemyProjectile(i);
			for (int j = 0; j < enemyCount; j++)
			{
				//ìñÇΩÇËîªíË
				if (hitCircle(player.getPos(), player.getRadius(), e->getPos(), e->getRadius()))
				{
					e->Destroy();
					Coin::DegCoinNum(e->getDamage());
					player.setInvincibleTimer(1.5f);
				}
			}
		}
	}
}
