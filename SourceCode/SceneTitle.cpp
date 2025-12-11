#include"SceneTitle.h"
#include "../GameLib/game_lib.h"

void SceneTitle::update()
{
	player.update();
}

void SceneTitle::render()
{
	GameLib::clear(0, 0, 1);

	player.render();
//	stage.render();
}

void SceneTitle::init()
{
	player.init();
	stage.init();
}

void SceneTitle::deinit()
{

}

void SceneTitle::deleteSprite()
{

}