#include"SceneTitle.h"
#include "../GameLib/game_lib.h"
#include "audio.h"
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
		music::play(main, true);
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

	
	text_out(1, "0123456789", 500, 500, 1, 1, 1 ,0,0);
}


void SceneTitle::deinit()
{
	music::stop();
}

void SceneTitle::deleteSprite()
{
	//delete player
}