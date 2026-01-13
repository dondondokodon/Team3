#include "SceneBuildSlect.h"

#include "../GameLib/game_lib.h"
using namespace input;

void SceneBuildSelect::init()
{
	state = 0;

}

void SceneBuildSelect::update()
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
			ISCENE::nextScene = SCENE_GAME;
		debug::setString("Build");

		break;

	}
}

void SceneBuildSelect::render()
{
	GameLib::clear(0, 0.6, 1);



}


void SceneBuildSelect::deinit()
{

}

void SceneBuildSelect::deleteSprite()
{
	//delete player
}