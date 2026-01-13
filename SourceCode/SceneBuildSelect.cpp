#include "SceneBuildSlect.h"
#include "Build.h"
#include "../GameLib/game_lib.h"
using namespace input;

void SceneBuildSelect::init()
{
	state = 0;
	spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::InShop);

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
	if (!spr) return;
	sprite_render(spr.get(), 0, 0, 1, 1, 0, 0, 1280, 720, 0, 0, 0, 1, 1, 1, 1);


}


void SceneBuildSelect::deinit()
{

}

void SceneBuildSelect::deleteSprite()
{
	//delete player
}