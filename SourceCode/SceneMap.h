#pragma once
#include"Scene.h"
#include"../GameLib/game_lib.h"
#include"OBJ2D.h"


class SceneMap :public ISCENE
{
public:
	virtual void update();
	virtual void render();
	virtual void init();
	virtual void deinit();
	virtual void deleteSprite();

};

//マップ移動
class Map_Tile : public OBJ2D
{
public:
	static void update();
	static void render();
};

//ビルド選択画面
class Build_Tile : public OBJ2D
{
public:
	static void update();
	static void render();
};

enum SELECT
{
	map = 0,	//マップ移動
	build		//ビルド選択画面
};