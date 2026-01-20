#include "SceneResult.h"
#include "SceneMap.h"
#include "Coin.h"

extern bool resetMap;
void SceneResult::init()
{
	resetMap = true;
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
		//SceneMap::Instance().Clear();

		debug::setString("result");

		break;

	}

}

void SceneResult::render()
{
	GameLib::clear(0, 0.5, 0.5);

}

void SceneResult::deinit()
{
	Coin::SetCoinNum(1500);

}
