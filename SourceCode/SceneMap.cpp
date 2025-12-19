#include"SceneMap.h"
#include "../GameLib/game_lib.h"
#include "Build.h"

int choice;

void SceneMap::init()
{
	state = 0;
	choice = map;
}


void SceneMap::update()
{
	switch (state)
	{
	case 0:
		state++;

	case 1:
		setBlendMode(Blender::BS_ALPHA);
		state++;

	case 2:
		switch (choice)
		{
		case map:
			Map_Tile::update();

			break;

		case build:
			Build_Tile::update();

			break;

		}
		break;
	}

}

void SceneMap::render()
{
	GameLib::clear(0, 1, 0);
	Map_Tile::render();
	Build_Tile::render();
}

void SceneMap::deinit()
{

}

void SceneMap::deleteSprite()
{

}

void Map_Tile::update()
{
	//デバッグ用
	if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
		ISCENE::nextScene = SCENE_GAME;
	if (GameLib::input::TRG(0) & GameLib::input::PAD_SELECT)
		choice = build;

	debug::setString("map");
}

void Map_Tile::render()
{

}

void Build_Tile::update()
{
	if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
	{
		Build::extraJump = true;
		ISCENE::nextScene = SCENE_GAME;

	}
	if (GameLib::input::TRG(0) & GameLib::input::PAD_SELECT)
		choice = map;


	debug::setString("build");

}

void Build_Tile::render()
{

}