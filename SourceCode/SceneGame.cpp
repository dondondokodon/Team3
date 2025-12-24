#include"SceneGame.h"
#include<memory>
#include"../GameLib/game_lib.h"
#include"Enemy.h"
#include"EnemyManager.h"

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
		EnemyManager::instance().add(std::make_unique<Enemy>(VECTOR2{ 1000.0f, 500.0f }));
		EnemyManager::instance().init();//ここでやるのキモイからadd関数の中で追加したてのエネミーのinitしてもいいかも
		state++;

	case 2:

		//時間計算（秒）
		frame++;
		if (frame % 60 == 0)
			timer++;
		camera.update(player);
		player.update();
		EnemyManager::instance().update();
		stage.update();

		if (player.lightAttack)
		{
			ProjectileStraight* b = new ProjectileStraight(&projMgr, Projectile::Owner::player, 100, -1);
			b->Launch(player.getDir(), player.getPos());//-player.getPivot());
		}
		player.lightAttack = false;

		projMgr.update();
		debug::setString("time:%d", timer);
		break;
	}
}

void SceneGame::render()
{
	GameLib::clear(1, 0, 1);
	stage.cameraRender(camera);
	EnemyManager::instance().render(camera);
	player.cameraRender(camera);
	projMgr.Render(camera);
}


void SceneGame::deinit()
{

}

void SceneGame::deleteSprite()
{

}