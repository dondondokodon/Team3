#include"SceneGame.h"
#include<memory>
#include"../GameLib/game_lib.h"
#include"Enemy.h"
#include"EnemyManager.h"
#include"common.h"
#include"ProjectileManager.h"
#include"EffektManager.h"
#include"ImageManager.h"
#include"textUI_Manager.h"
#include"SceneMap.h"
#include"audio.h"
#include "Effect.h"
extern int moveTile;	//何マス進んだかをカウント
int timeClear;
bool death;
SceneGame::SceneGame()
{
	state = 0;
	frame = 0;
	timer = 0;
}

void SceneGame::init()
{
	death = false;
	state = 0;
	frame = 0;
	timer = 0;
	player.init();
	//stage01.init();
	//stage02.init();
	EnemyManager::instance().init();
	EffektManager::Instance().init();
	camera.init();
	camera.setStageLimit(VECTOR2{ SCREEN_W + 1500.0f , 720.0f});
	EnemyManager::instance().setCamera(camera);
	coinUi.setSprite(ImageManager::Instance().getSprite(ImageManager::SpriteNum::coin));
	spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::SETUMEI);
	//player.setDef(50);
}

void SceneGame::update()
{
	switch (state)
	{
	case 0:
		state++;

	case 1:
		music::stop();
		music::play(battle,true);
		setBlendMode(Blender::BS_ALPHA);
		//ターゲット設定
		EnemyManager::instance().setTarget(player);
		//エネミーセット　引数がステージ番号
		SwitchEnemyType();	//ここで敵の種類を切り替えてる　デバッグの際は消してOK
		/*EnemyManager::instance().add(std::make_unique<Enemy>(VECTOR2{ 1500.0f, 200.0f }));
		EnemyManager::instance().add(std::make_unique<Enemy>(VECTOR2{ -500.0f, 250.0f }));
		EnemyManager::instance().add(std::make_unique<Enemy>(VECTOR2{ -300.0f, 600.0f }));*/
		SwitchStage();
		//EnemyManager::instance().setStage(stages.back().get()->getStageNo());	//1が最初
		stages.at(0).get()->init();

		state++;

	case 2:

		//時間計算（秒）
		if (!death)
			frame++;
		if (frame % 60 == 0)
			timer++;
		camera.update(player);

		//player　boss　衝突判定
		/*EnemyBoss* b = EnemyManager::instance().getBoss();
		if (b)
		{
			player.setHitWall(b->getHitWall());
		}*/
		player.update();

		//土台の当たり判定
		stages.back().get()->checkFootingCollision(player);

		EnemyManager::instance().update(camera);
		EffektManager::Instance().update(camera);
		//stage01.update();
		//stage02.update();
		stages.at(0).get()->update();

		//デバッグ用
		if (TRG(0) & PAD_SELECT)
		{
			ISCENE::nextScene = SCENE_MAP;
		}

		//2分くらいたったらゲーム終了　マップへ遷移
		if (moveTile != 6 && timer == 60)
		{
			Coin::AddCoinNum(800);
			ISCENE::nextScene = SCENE_MAP;
		}
			

		//倒されたらリザルトへ
		if (player.isDeath())
			ISCENE::nextScene = SCENE_RESULT;
		
		if (Coin::GetCoinNum() < 1)
			death = true;

		textUI_Manager::Instance().update();

		ProjectileManager::Instance().update();
		Collision();
		debug::setString("time:%d", timer);
		debug::setString("Coin:%d", Coin::GetCoinNum());
		break;
	}
}

void SceneGame::render()
{
	GameLib::clear(1, 0, 0);
	stages.at(0).get()->cameraRender(camera);
	EnemyManager::instance().render(camera);
	EffektManager::Instance().render(camera);
	sprite_render(spr.get(), SCREEN_W * 0.5f, SCREEN_H-15,1.0f,1.0f,0.0f,0.0f,1278.0f,30.0f,1278*0.5f,15.0f);
	player.cameraRender(camera);
	player.hitAreaRender(camera);
	ProjectileManager::Instance().Render(camera);
	coinUi.render();
	textUI_Manager::Instance().render(camera);

	// 桁数を求める
	int num = 60-timer;
	int temp = num;
	int digit = 1;
	while (temp >= 10)
	{
		temp /= 10;
		digit *= 10;
	}

	// 大きい桁から取り出す
	int i = 0;
	while (digit > 0)
	{
		int d = num / digit;   // 先頭の桁

		char str = (d + '0');
		std::string strin(1, str);
		text_out(7, strin, SCREEN_W*0.5f + i * 30-20 , SCREEN_H*0.1f - 20, 1.0f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f,TEXT_ALIGN::MIDDLE);
		num %= digit;          // 先頭桁を削除
		digit /= 10;
		i++;
	}
}


void SceneGame::deinit()
{
	//敵のクリア
	EnemyManager::instance().clear();
	player.deinit();

	//球を全削除
	ProjectileManager::Instance().Clear();

	//エフェクトのクリア
	EffektManager::Instance().clear();

	EnemyManager::instance().setCameraNull();

	textUI_Manager::Instance().Clear();

	music::stop();
	music::play(main, true);

	timeClear = timer;

	stages.clear();
}

void SceneGame::deleteSprite()
{

}

void SceneGame::Collision()
{
	//player→enemy
	EnemyManager& enemyManager = EnemyManager::instance();
	int playerProjectileCount  = ProjectileManager::Instance().GetPlayerProjectileCount();
	int enemyCount             = enemyManager.GetEnemyCount();
	int pursuitCount           = ProjectileManager::Instance().GetPursuitProjectileCount();

	for (int i = 0; i < playerProjectileCount; i++)
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
					//p->Destroy();
					EffektManager::Instance().Register(new Effect(*e));	//ヒットエフェクト

					//if (p->onHit())
					{
						e->degHp(e->calcProtectingDamage(p->getDamage()));
						e->setInvincibleTimer(3.5f);
						e->setHitFlag(true);
						//textUI_Manager::Instance().spawnAddText(player);
						//textUI_Manager::Instance().spawnDegText(*e);

						//軽攻撃なら
						if (p->GetOwnerId() == Projectile::kinds::light)
						{
							p->onHit();
							music::play(P_lightA);
							Coin::AddCoinNum(Coin::LightAttackReward());
							Coin::AddGotCoin(Coin::LightAttackReward());
							textUI_Manager::Instance().spawnAddText(player, Coin::LightAttackReward());
						}

						//重攻撃なら
						if (p->GetOwnerId() == Projectile::kinds::heavy)
						{
							music::play(P_HeavyA);
							Coin::AddCoinNum(Coin::HeavyAttackReward());
							Coin::AddGotCoin(Coin::HeavyAttackReward());
							textUI_Manager::Instance().spawnAddText(player, Coin::HeavyAttackReward());
						}

						//攻撃を当てたら追撃	現在当ててもコインの返還は無し
						if (p->GetOwnerId() != Projectile::kinds::pursuit && Build::extraBullet)
						{
							p->onHit();
							int useCoin = Coin::GetRatioCoin(0.005f);
							ProjectileStraight* b = new ProjectileStraight(&ProjectileManager::Instance(), Projectile::Faction::player, Coin::calcDamage(2, useCoin), Projectile::kinds::pursuit, player.getPursuitLife(), ImageManager::Instance().getSprite(ImageManager::SpriteNum::PlayerBullet), player.getPursuitSize(), player.getPursuitScale(), player.getPursuitSpeed(), player.getPursuitRadius());
							//Coin::DegCoinNum(useCoin);
							music::play(tranpFly);
							b->normalize(player.getPos(), e->getPos());
							b->Launch(b->getDir(), player.getPos());
						}

						if (e->isDeath())
						{


						}
					}
					
				}

			}
			//debug::setString("Coin:%d", playerProjectileCount);
		}
	}

	//追尾弾
	for (int l = 0; l < pursuitCount; l++)
	{
		Projectile* k = ProjectileManager::Instance().GetPursuitProjectile(l);
		for (int j = 0; j < enemyCount; j++)
		{
			Enemy* e = enemyManager.GetEnemy(j);
			if (e->getInvincibleTimer() <= 0)		//無敵時間中は当たり判定を取らない
			{
				//当たり判定
				if (hitCircle(k->getPos(), k->getRadius(), e->getPos(), e->getRadius()))
				{
					EffektManager::Instance().Register(new Effect(*e));	//ヒットエフェクト

					if (k->onHit())
					{
						textUI_Manager::Instance().spawnAddText(player, 15);
						e->degHp(e->calcProtectingDamage(k->getDamage()));
						e->setInvincibleTimer(1.5f);
						e->setHitFlag(true);
						if (k->GetOwnerId() == Projectile::kinds::pursuit)
						{
							Coin::AddCoinNum(15);
							Coin::AddGotCoin(15);
						}
						music::play(P_lightA);
					}
					
					if (e->isDeath())
					{


					}


				}

			}


		}
	}

	//enemy→player
	if (player.getInvincibleTimer() <= 0&&player.getAct()!=Player::ACT::DEATH)		//無敵時間中のみ
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
					EffektManager::Instance().Register(new EffectP(player));	//ヒットエフェクト
					//e->Destroy();
					if (e->onHit())
					{
						music::play(P_hit);
						CAMERA::shake(VECTOR2{ rand() % 10 - 5.0f, -static_cast<float>(rand() % 20) });
						Coin::DegCoinNum(player.calcProtectingDamage(e->getDamage()));
						textUI_Manager::Instance().spawnDegText(player, -player.calcProtectingDamage(e->getDamage()));
						player.setInvincibleTimer(1.5f);
					}
				}
			}
		}
	}

	//boss->player体の判定
	EnemyBoss* b = EnemyManager::instance().getBoss();
	if (b)
	{
		if (player.getInvincibleTimer()<=0 && player.getAct() != Player::ACT::DEATH&&b->getAct()!=EnemyBoss::STATE::DEATH)
		{
			if (hitCircle(player.getPos(), player.getRadius(), b->getPos(), b->getRadius()))
			{
				EffektManager::Instance().Register(new EffectP(player));	//ヒットエフェクト
				music::play(P_hit);
				CAMERA::shake(VECTOR2{ rand() % 10 - 5.0f, -static_cast<float>(rand() % 20) });
				Coin::DegCoinNum(player.calcProtectingDamage(b->getATK()));
				textUI_Manager::Instance().spawnDegText(player, -b->getATK());
				player.setInvincibleTimer(5.5f);
			}
		}
	}
}

void SceneGame::SwitchStage()
{
	if (moveTile > 3)
		stages.emplace_back(std::make_unique<Stage02>());
	else
		stages.emplace_back(std::make_unique<Stage01>());
}

void SceneGame::SwitchEnemyType()
{
	if (moveTile == 6)
		EnemyManager::instance().setStage(2);	//2がぼす

	else
		EnemyManager::instance().setStage(1);	//1がざこ
}

