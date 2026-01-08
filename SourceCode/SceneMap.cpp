#include"SceneMap.h"
#include "../GameLib/game_lib.h"
#include "Build.h"
#include"ImageManager.h"


int moveTile = 0;	//何マス進んだかをカウント
int move5 = 0;
int nemuturai = 0;
int i;				//どのマスにいるか

void SceneMap::init()
{
	i = 0;
	//ShopAndBattle();	//後でランダムで出るようにしたら完成？
	state = 0;
	Map.setSprite(ImageManager::Instance().getSprite(ImageManager::SpriteNum::Map));
}


void SceneMap::update()
{
	switch (state)
	{
	case 0:
		state++;

	case 1:
		setBlendMode(Blender::BS_ALPHA);
		if (!moveTile)
			startBattle();
		else
		{
			if (moveTile % 5 == 0)
			{
				move5++;
				if (move5 % 3 == 0)
					LastBoss();
				else
					MiddleBoss();

			}
			else//ぜ～んぶ仮置き
			{
				if (moveTile % 2 == 0)
					ShopAndBattle();
				else if (moveTile % 3 == 0)
					BattleAndEvent();
				else
					ShopAndEvent();
			}
		}

		if (moveTile > 2)
			nemuturai++;

		state++;

	case 2:

		routePick();

		pos.x = 200 * nemuturai;

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

	for (int i = 0; i <= GetMovedTileCount()-1; i++)
	{
		Tile* tile = GetMovedTile(i);
		tile->render();
	}
}

void SceneMap::deinit()
{
	if (!moveTile)
		posMemory_y0 = GetTile(0)->getWorldPos().y;

	nextSpawn();
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
		//Build::extraJump = true;
		ISCENE::nextScene = SCENE_GAME;

	}

	
	//debug::setString("battle");

}

void Battle2_Tile::update()
{
	if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
	{
		//Build::extraJump = true;
		ISCENE::nextScene = SCENE_GAME;

	}

	
	//debug::setString("battle");

}
void Battle3_Tile::update()
{
	if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
	{
		//Build::extraJump = true;
		ISCENE::nextScene = SCENE_GAME;

	}

	
	//debug::setString("battle");

}

void Shop_Tile::update()
{
	if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
	{
		Build::extraJump = true;
		//Build::extraCost = true;
		Build::extraVeryCost = true;
		Build::extraMotionRapid = true;
		ISCENE::nextScene = SCENE_GAME;

	}

	//debug::setString("shop");

}

void Event_Tile::update()
{
	if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
	{
		Build::extraJump = true;
		//Build::extraCost = true;
		Build::extraVeryCost = true;
		Build::extraMotionRapid = true;
		ISCENE::nextScene = SCENE_GAME;

	}

	//debug::setString("shop");

}

void SceneMap::startBattle()		//いっちゃん最初
{
	tiles.emplace_back(std::make_unique<Battle1_Tile>(VECTOR2{ 100,360 }));

}

void SceneMap::BattleAndEvent()		//雑魚敵戦・イベント
{
	tiles.emplace_back(std::make_unique<Event_Tile>(VECTOR2{ posMemory_x,posMemory_y1 }));
	tiles.emplace_back(std::make_unique<Battle1_Tile>(VECTOR2{ posMemory_x,posMemory_y2 }));
}

void SceneMap::ShopAndEvent()		//店・イベント
{
	tiles.emplace_back(std::make_unique<Shop_Tile>(VECTOR2{ posMemory_x,posMemory_y1 }));
	tiles.emplace_back(std::make_unique<Event_Tile>(VECTOR2{ posMemory_x,posMemory_y2 }));

}

void SceneMap::ShopAndBattle()		//店・雑魚敵戦
{
	tiles.emplace_back(std::make_unique<Shop_Tile>(VECTOR2{ posMemory_x,posMemory_y1 }));
	tiles.emplace_back(std::make_unique<Battle1_Tile>(VECTOR2{ posMemory_x,posMemory_y2 }));

}

void SceneMap::MiddleBoss()			//中ボス
{
	tiles.emplace_back(std::make_unique<Battle2_Tile>(VECTOR2{ posMemory_x,posMemory_y0 }));

}

void SceneMap::LastBoss()			//本ボス
{
	tiles.emplace_back(std::make_unique<Battle3_Tile>(VECTOR2{ posMemory_x,posMemory_y0 }));

}

void SceneMap::inputSelect()
{

	if (GameLib::input::TRG(0) & GameLib::input::PAD_UP)	//W
	{
		i--;
		if (i < 0)
			i = GetTileCount() - 1;

	}

	if (GameLib::input::TRG(0) & GameLib::input::PAD_DOWN)	//S
	{
		i++;
		if (i > GetTileCount() - 1)
			i = 0;

	}

	

}

void SceneMap::routePick()
{
	inputSelect();

	Tile* nowTile = GetTile(i);

	nowTile->setScale({ 1.2,1.2 });
	nowTile->update();

	for (int i = 0; i <= GetTileCount() - 1; i++)
	{
		Tile* tile = GetTile(i);

		tile->setLocalPos(WorldToLocal(tile->getWorldPos()));

		if (tile != nowTile)
			tile->setScale({ 1,1 });
	}

	for (int i = 0; i <= GetMovedTileCount() - 1; i++)
	{
		Tile* tile = GetMovedTile(i);

		tile->setLocalPos(WorldToLocal(tile->getWorldPos()));

		tile->update();
		if (tile != nowTile)
			tile->setScale({ 1,1 });

	}
}

void SceneMap::nextSpawn()
{

	Tile* nowTile1 = GetTile(GetTileCount() - 1);	//最後
	posMemory_x = nowTile1->getWorldPos().x + 200;	//x座標は共有

	Tile* nowTile2 = 0;
	if (GetTileCount() != 1)
		nowTile2 = GetTile(GetTileCount() - 2);	//一個前

	if (GetTileCount() == 1)
	{
		posMemory_y1 = nowTile1->getWorldPos().y + 100;
		posMemory_y2 = nowTile1->getWorldPos().y - 100;

	}
	else
	{
		posMemory_y1 = nowTile1->getWorldPos().y;
		posMemory_y2 = nowTile2->getWorldPos().y;

	}


	for (int i = 0; i <= GetTileCount() - 1; i++)	//別の配列に譲渡
	{
		movedTiles.push_back(std::move(tiles[i]));
	}

	tiles.clear();
}
