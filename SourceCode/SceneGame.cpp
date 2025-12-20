#include"SceneGame.h"
#include"../GameLib/game_lib.h"

void SceneGame::init()
{
	state = 0;
	frame = 0;
	timer = 0;
	player.init();
	stage.init();
	enemy.init();
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
		state++;

	case 2:

		//éûä‘åvéZÅiïbÅj
		frame++;
		if (frame % 60 == 0)
			timer++;
		camera.update(player);
		player.update();
		enemy.update();
		stage.update();

		debug::setString("time:%d", timer);
		break;
	}
}

void SceneGame::render()
{
	GameLib::clear(1, 0, 1);
	stage.cameraRender(camera);
	enemy.cameraRender(camera);
	player.cameraRender(camera);
}


void SceneGame::deinit()
{

}

void SceneGame::deleteSprite()
{

}