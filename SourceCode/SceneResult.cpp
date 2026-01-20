#include "SceneResult.h"

void SceneResult::init()
{
	state = 0;

}

void SceneResult::update()
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
			ISCENE::nextScene = SCENE_TITLE;


		break;

	}

}

void SceneResult::render()
{
	GameLib::clear(0, 1, 1);

}

void SceneResult::deinit()
{
}
