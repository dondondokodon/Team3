#include"SceneTitle.h"
#include "../GameLib/game_lib.h"

void SceneTitle::init()
{
	state = 0;
	player.init();
	stage.init();
}

void SceneTitle::update()
{
	switch (state)
	{
	case 0:
		state++;

	case 1:
		state++;

	case 2:
		//デバッグ用
		if (TRG(0) & PAD_START)
			ISCENE::nextScene = SCENE_MAP;
		player.update();
		stage.update();

		break;

	}
}

void SceneTitle::render()
{
	GameLib::clear(0, 0, 1);

	stage.render();
	player.render();

}


void SceneTitle::deinit()
{

}

void SceneTitle::deleteSprite()
{
	//delete player
}