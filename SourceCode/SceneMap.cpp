#include"SceneMap.h"
#include "../GameLib/game_lib.h"

void SceneMap::update()
{
	if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
		ISCENE::nextScene = SCENE_GAME;

}

void SceneMap::render()
{
	GameLib::clear(1, 1, 0);
}

void SceneMap::init()
{

}

void SceneMap::deinit()
{

}

void SceneMap::deleteSprite()
{

}