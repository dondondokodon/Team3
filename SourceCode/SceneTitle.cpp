#include"SceneTitle.h"
#include "../GameLib/game_lib.h"
using namespace input;

void SceneTitle::init()
{
	state = 0;
	
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
		

		break;

	}
}

void SceneTitle::render()
{
	GameLib::clear(0, 0, 1);

	
	text_out(7, "!", 500, 500);
}


void SceneTitle::deinit()
{

}

void SceneTitle::deleteSprite()
{
	//delete player
}