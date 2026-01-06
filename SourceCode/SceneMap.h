#pragma once
#include"Scene.h"
#include"../GameLib/game_lib.h"
#include "CAMERA.h"



class Tile
{
protected:
	VECTOR2 WorldPos;
	VECTOR2 LocalPos;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;
	VECTOR2 speed;
	VECTOR2 offset;
	VECTOR2 direction;
	int angle;

	std::shared_ptr<GameLib::Sprite> spr;

	int act;
	int timer;
	int anime;
	int animeTimer;
	int anime_state;
	float radius;     // 半径

public:
	void setSprite(std::shared_ptr<Sprite> s)
	{
		spr = s;
	}

	virtual void render()
	{
		if (!spr) return;
		sprite_render(spr.get(), LocalPos.x, LocalPos.y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle, color.x, color.y, color.z, color.w);
	}

	//void cameraRender(CAMERA& camera);

	virtual void init() {}
	virtual void deinit() {}
	virtual void update() = 0;
	bool animeUpdate(int animeNo, int total, int frame, bool loop);

	int                 hitPrimitive;//物の形
	VECTOR2 getWorldPos() { return WorldPos; }
	void addWorldPos(VECTOR2 pos) { WorldPos += pos; }
	VECTOR2 getScale() { return scale; }
	float getRadius() { return radius; }
	int getAct() { return act; }
	int getAnime() { return anime; }
	VECTOR2 getSpeed() { return speed; }
	VECTOR2 getPivot() { return pivot; }
	//VECTOR2 getDir() { return direction; }

	void setScale(VECTOR2 Scale) { scale = Scale; }
	void setAct(int Act) { act = Act; }
	void setColor(VECTOR4 c) { color = c; }

};

//マップ移動
//class Map //: public CAMERA
//{
//private:
//	VECTOR2 pos = {};
//	float speed = 0;
//	VECTOR2 normalized = {};
//public:
//	float calcCamera(Tile& tile);
//	void updateTile(Tile& tile, float len);
//	//void render();
//};

class Map_Tile : public Tile
{
public:
	Map_Tile()
	{
		WorldPos = {};
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 1280,720 };
		pivot = { 0,0 };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
	}
	~Map_Tile(){}
	void update();
	//void render();
};

//ビルド選択画面
class Build_Tile : public Tile
{
public:
	void update();
	//void render();
};

//店
class Shop_Tile : public Tile
{
public:
	Shop_Tile(VECTOR2 WPos)
	{
		spr = std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load((L"./Data/Images/shop.png")));
		WorldPos = WPos;
		LocalPos = WPos;	//後で消す
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 64,64 };
		pivot = { 0,0 };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
	}
	~Shop_Tile() {}

	//std::shared_ptr<GameLib::Sprite> spr = std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load(L"./Data/Images/shop.png"));
	void update();
	//void render();
};

//雑魚敵戦
class Battle1_Tile : public Tile
{
public:
	Battle1_Tile(VECTOR2 WPos)
	{
		spr = std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load((L"./Data/Images/battle.png")));
		WorldPos = WPos;
		LocalPos = WPos;	//後で消す
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 64,64 };
		pivot = { 0,0 };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
	}
	~Battle1_Tile() {}

	void update();
	//void render();
};

//中ボス
class Battle2_Tile : public Tile
{
public:
	void update();
	void render();
};

//本ボス
class Battle3_Tile : public Tile
{
public:
	void update();
	void render();
};

//////////////////////////////////////////
//////////////////////////////////////////
enum SELECT
{
	map = 0,	//マップ移動
	build,		//ビルド選択画面
	shop,		//店
	battle1,	//雑魚敵戦
	battle2,	//中ボス
	battle3		//本ボス
};

//シーン
class SceneMap :public ISCENE
{
public:
	virtual void update();
	virtual void render();
	virtual void init();
	virtual void deinit();
	virtual void deleteSprite();

	void ShopAndBattle();		//店・雑魚敵戦
	void BattleAndBattle();		//雑魚敵戦・雑魚敵戦
	void MiddleBoss();			//中ボス
	void LastBoss();			//本ボス

	//数取得
	int GetTileCount()const { return static_cast<int>(tiles.size()); }

	//本体取得
	Tile* GetTile(int index) { return tiles.at(index).get(); }

	//全削除
	void Clear();

private:
	Map_Tile Map;
	//Tile* Battle;// = new Battle1_Tile({ 100, 360 });
	//Tile* Shop;// = new Battle1_Tile({ 100, 360 });
	//Tile* Build = new Build_Tile;

	//マスを入れる配列
	std::vector<std::unique_ptr<Tile>>	tiles;
};
