#include"SceneMap.h"
#include "../GameLib/game_lib.h"
#include "Build.h"
#include"audio.h"


int moveTile = 0;	//何マス進んだかをカウント
int move5 = 0;
int nemuturai = 0;
int i;				//どのマスにいるか
bool resetMap = false;

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
		//music::play(main, true);
		setBlendMode(Blender::BS_ALPHA);

		if (resetMap)
			Clear();
		resetMap = false;

		if (!moveTile)
			startBattle();
		else
		{
			if (moveTile % 5 == 0)
			{
				//move5++;
				//if (move5 % 3 == 0)
					LastBoss();
				//else
				//	MiddleBoss();

			}
			else//ぜ～んぶ仮置き　後でランダムにしたい
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

		//pos.x = 200 * nemuturai;

		debug::setString("moved:%d", movedTiles.size());
		debug::setString("moveTile:%d", moveTile);
		break;
	}

}

void SceneMap::render()
{
	GameLib::clear(0, 1, 0);
	Map.render();
	routeMapping();
	for (int i = 0; i < GetTileCount(); i++)
	{
		Tile* tile = GetTile(i);
		tile->render();
	}

	for (int i = 0; i < GetMovedTileCount(); i++)
	{
		Tile* tile = GetMovedTile(i);
		tile->render();
	}

	for (int i = 0; i < GetNonMovedTileCount(); i++)
	{
		Tile* tile = GetNonMovedTile(i);
		tile->render();
	}

}

void SceneMap::deinit()
{
	if (!moveTile)
		posMemory_y0 = GetTile(0)->getWorldPos().y;

	//music::stop();

	nextSpawn();
	moveTile++;
}

void SceneMap::deleteSprite()
{

}







//全削除
void SceneMap::Clear()
{
	tiles.clear();
	movedTiles.clear();
	nonMovedTiles.clear();
	moveTile = 0;	//何マス進んだかをカウント
	move5 = 0;
	nemuturai = 0;
	i = 0;				//どのマスにいるか

	Build::extraJump = false;
	Build::extraCost = false;
	Build::extraVeryCost = false;
	Build::extraMotionRapid = false;
	Build::extraMoonGravity = false;
	Build::extraBullet = false;


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
	ISCENE::nextScene = SCENE_GAME;
	debug::setString("battle");

}

void Battle2_Tile::update()
{
	ISCENE::nextScene = SCENE_GAME;	
	debug::setString("battle");

}
void Battle3_Tile::update()
{
	ISCENE::nextScene = SCENE_GAME;
	debug::setString("battle");

}

void Shop_Tile::update()
{
	ISCENE::nextScene = SCENE_BUILD;
	debug::setString("shop");

}

void Event_Tile::update()
{
	ISCENE::nextScene = SCENE_EVENT;
	debug::setString("event");

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

void SceneMap::inputTileSelect()
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
	inputTileSelect();

	Tile* nowTile = GetTile(i);

	nowTile->setScale({ 1.2,1.2 });

	if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
	{
		nowTile->update();

	}

	for (int i = 0; i < GetTileCount(); i++)
	{
		Tile* tile = GetTile(i);

		tile->setLocalPos(WorldToLocal(tile->getWorldPos()));

		if (tile != nowTile)
			tile->setScale({ 1,1 });
	}

	for (int i = 0; i < GetMovedTileCount(); i++)
	{
		Tile* tile = GetMovedTile(i);

		tile->setLocalPos(WorldToLocal(tile->getWorldPos()));

		//tile->update();
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

	movedTiles.push_back(std::move(tiles[i]));

	for (auto& t : tiles)
	{
		if (t) nonMovedTiles.push_back(std::move(t));
	}

	tiles.clear();
}

void SceneMap::routeMapping()
{
	Tile* preTile = GetTile(i);
	Tile* nowTile = GetTile(i);
	if (!movedTiles.empty())
		preTile = GetMovedTile(GetMovedTileCount() - 1);

	primitive::line(
		preTile->getWorldPos(), 
		nowTile->getWorldPos(),
		VECTOR4{1,1,1,1},
		7);

	Signpost();
}

void SceneMap::Signpost()
{
	int lest = GetMovedTileCount();
	for (int i = 0; i < GetMovedTileCount(); i++)
	{
		if (lest < 2)
			return;

		lest--;
		primitive::line(GetMovedTile(i)->getWorldPos(), GetMovedTile(i + 1)->getWorldPos(),VECTOR4{1,1,1,1}, 5);
	}
}
