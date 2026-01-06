#include"SceneMap.h"
#include "../GameLib/game_lib.h"
#include "Build.h"

int choice;
int moveTile = 0;	//何マス進んだかをカウント
int i;				//どのマスにいるか

void SceneMap::init()
{
	i = 0;
	ShopAndBattle();	//後でランダムで出るようにしたら完成？
	state = 0;
	choice = map;
	Map.setSprite(std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load((L"./Data/Images/map.png"))));
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

		if (GameLib::input::TRG(0) & GameLib::input::PAD_UP)	//W
		{
			i--;
			if (i < 0)
				i = GetTileCount() -1;

		}

		if (GameLib::input::TRG(0) & GameLib::input::PAD_DOWN)	//S
		{
			i++;
			if (i > GetTileCount() -1)
				i = 0;

		}
		Tile*  nowTile = GetTile(i);

		nowTile->update();

		debug::setString("inTile:%d", GetTileCount());
		debug::setString("moveTile:%d", moveTile);
		break;
	}

}

void SceneMap::render()
{
	GameLib::clear(0, 1, 0);
	Map.render();
	for (int i = 0; i <= GetTileCount()-1; i++)
	{
		Tile* tile = GetTile(i);
		tile->render();
	}
}

void SceneMap::deinit()
{
	moveTile++;
}

void SceneMap::deleteSprite()
{

}


/// <summary>
/// /////////////////////////////////////////
/// </summary>

//いらんかも
void Map_Tile::update()
{

	//if (GameLib::input::TRG(0) & GameLib::input::PAD_SELECT)
	//	choice = battle1;

	//debug::setString("map");
}


/// <summary>
/// //////////////////////////////////////////////
/// </summary>
void Battle1_Tile::update()
{
	if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
	{
		Build::extraJump = true;
		ISCENE::nextScene = SCENE_GAME;

	}
	if (GameLib::input::TRG(0) & GameLib::input::PAD_SELECT)
		choice = map;


	debug::setString("battle");

}

void Shop_Tile::update()
{
	if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
	{
		Build::extraJump = true;
		ISCENE::nextScene = SCENE_GAME;

	}
	if (GameLib::input::TRG(0) & GameLib::input::PAD_SELECT)
		choice = map;


	debug::setString("shop");

}


void SceneMap::ShopAndBattle()		//店・雑魚敵戦
{
	tiles.emplace_back(std::make_unique<Shop_Tile>(VECTOR2{ 100,360 - 100 }));
	tiles.emplace_back(std::make_unique<Battle1_Tile>(VECTOR2{ 100,360 + 100 }));

}
