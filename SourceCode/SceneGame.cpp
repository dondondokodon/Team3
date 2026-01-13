#include"SceneGame.h"
#include<memory>
#include"../GameLib/game_lib.h"
#include"Enemy.h"
#include"EnemyManager.h"
#include"common.h"
#include"ProjectileManager.h"
#include"EffektManager.h"
#include"ImageManager.h"

SceneGame::SceneGame()
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
	stage01.init();
	//stage02.init();
	EnemyManager::instance().init();
	EffektManager::Instance().init();
	camera.init();
	camera.setStageLimit(VECTOR2{ SCREEN_W + 1500.0f , 720.0f});
	EnemyManager::instance().setCamera(camera);
	coinUi.setSprite(ImageManager::Instance().getSprite(ImageManager::SpriteNum::coin));

}

void SceneGame::update()
{
	switch (state)
	{
	case 0:
		state++;

	case 1:
		setBlendMode(Blender::BS_ALPHA);
		//ターゲット設定
		EnemyManager::instance().setTarget(player);
		//エネミーセット　引数がステージ番号
		EnemyManager::instance().setStage(2);	//1が最初
		/*EnemyManager::instance().add(std::make_unique<Enemy>(VECTOR2{ 1500.0f, 200.0f }));
		EnemyManager::instance().add(std::make_unique<Enemy>(VECTOR2{ -500.0f, 250.0f }));
		EnemyManager::instance().add(std::make_unique<Enemy>(VECTOR2{ -300.0f, 600.0f }));*/
		state++;

	case 2:

		//時間計算（秒）
		frame++;
		if (frame % 60 == 0)
			timer++;
		camera.update(player);
		player.update();
		EnemyManager::instance().update(camera);
		EffektManager::Instance().update(camera);
		stage01.update();
		//stage02.update();

		//デバッグ用
		if (TRG(0) & PAD_SELECT)
		{
			ISCENE::nextScene = SCENE_MAP;

		}

		ProjectileManager::Instance().update();
		Collision();
		debug::setString("time:%d", timer);
		debug::setString("Coin:%d", Coin::GetCoinNum());
		break;
	}
}

void SceneGame::render()
{
	GameLib::clear(1, 0, 1);
	stage01.cameraRender(camera);
	//stage02.cameraRender(camera);
	EnemyManager::instance().render(camera);
	EffektManager::Instance().render(camera);
	player.cameraRender(camera);
	player.hitAreaRender(camera);
	ProjectileManager::Instance().Render(camera);
	coinUi.render();
}


void SceneGame::deinit()
{
	//敵のクリア
	EnemyManager::instance().clear();
	player.deinit();

	//球を全削除
	ProjectileManager::Instance().Clear();

	EnemyManager::instance().setCameraNull();
}

void SceneGame::deleteSprite()
{

}

void SceneGame::Collision()
{
	//player→enemy
	EnemyManager& enemyManager = EnemyManager::instance();
	int playerProjectileCount = ProjectileManager::Instance().GetPlayerProjectileCount();
	int enemyCount = enemyManager.GetEnemyCount();
	for (int i = 0;i < playerProjectileCount; i++)
	{
		Projectile* p = ProjectileManager::Instance().GetPlayerProjectile(i);

		for (int j = 0; j < enemyCount; j++)
		{
			Enemy* e = enemyManager.GetEnemy(j);
			if (e->getInvincibleTimer() <= 0)		//無敵時間中は当たり判定を取らない
			{
				//当たり判定
				if (hitCircle(p->getPos(), p->getRadius(), e->getPos(), e->getRadius()))
				{
					p->Destroy();
					e->degHp(p->getDamage());
					e->setInvincibleTimer(1.5f);
					e->setHitFlag(true);

					//軽攻撃なら
					if (p->GetOwnerId() == Projectile::kinds::light)
						Coin::AddCoinNum(Coin::LightAttackReward());

					//重攻撃なら
					if (p->GetOwnerId() == Projectile::kinds::heavy)
						Coin::AddCoinNum(Coin::HeavyAttackReward());

					if (e->isDeath())
					{


					}
				}
			}
			//debug::setString("Coin:%d", playerProjectileCount);
		}
	}


	//enemy→player
	if (player.getInvincibleTimer() <= 0)		//無敵時間中のみ
	{
		int EnemyProjectileCount = ProjectileManager::Instance().GetEnemyProjectileCount();
		for (int i = 0; i < EnemyProjectileCount; i++)
		{
			Projectile* e = ProjectileManager::Instance().GetEnemyProjectile(i);
			for (int j = 0; j < enemyCount; j++)
			{
				//当たり判定
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
