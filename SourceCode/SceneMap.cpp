#include"SceneMap.h"
#include "../GameLib/game_lib.h"

void SceneMap::init()
{
	state = 0;
}


void SceneMap::update()
{
	switch (state)
	{
	case 0:
		state++;

	case 1:
		state++;

	case 2:
		//デバッグ用
		if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
			ISCENE::nextScene = SCENE_GAME;

		break;
	}

}

void SceneMap::render()
{
	GameLib::clear(1, 1, 0);
}

void SceneMap::deinit()
{

}

void SceneMap::deleteSprite()
{

}