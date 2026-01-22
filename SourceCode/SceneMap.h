#pragma once
#include"Scene.h"
#include"../GameLib/game_lib.h"
#include "CAMERA.h"
#include"ImageManager.h"



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
	int type;

	std::shared_ptr<GameLib::Sprite> spr;


	int act;
	int timer;
	int anime;
	int animeTimer;
	int anime_state;
	float radius;     // 半径

public:
	virtual ~Tile() = default;

	void setSprite(std::shared_ptr<Sprite> s)
	{
		spr = s;
	}

	virtual void render()
	{
		if (!spr) return;
		sprite_render(spr.get(), LocalPos.x, LocalPos.y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle, color.x, color.y, color.z, color.w);
	}

	enum kinds
	{
		battle = 0,
		middle,
		last,
		shop,
		event
	};

	//void cameraRender(CAMERA& camera);

	virtual void init() {}
	virtual void deinit() {}
	virtual void update() = 0;
	bool animeUpdate(int animeNo, int total, int frame, bool loop);


	VECTOR2 getWorldPos() { return WorldPos; }
	void addWorldPos(VECTOR2 pos) { WorldPos += pos; }
	void addLocalPos(VECTOR2 pos) { LocalPos += pos; }
	VECTOR2 getScale() { return scale; }
	float getRadius() { return radius; }
	int getAct() { return act; }
	int getAnime() { return anime; }
	VECTOR2 getSpeed() { return speed; }
	VECTOR2 getPivot() { return pivot; }
	//VECTOR2 getDir() { return direction; }

	void setLocalPos(VECTOR2 LPos) { LocalPos = LPos; }
	void setScale(VECTOR2 Scale) { scale = Scale; }
	void setAct(int Act) { act = Act; }
	void setColor(VECTOR4 c) { color = c; }

};


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

//店
class Shop_Tile : public Tile
{
public:
	Shop_Tile(VECTOR2 WPos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Shop);
		WorldPos = WPos;
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 64,64 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
		type = Tile::kinds::shop;

	}
	~Shop_Tile() {}

	void update();
	//void render();
};

//イベントマス
class Event_Tile : public Tile
{
public:
	Event_Tile(VECTOR2 WPos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Event);
		WorldPos = WPos;
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 64,64 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
		type = Tile::kinds::event;

	}
	~Event_Tile() {}

	void update();
	//void render();
};

//雑魚敵戦
class Battle1_Tile : public Tile
{
public:
	Battle1_Tile(VECTOR2 WPos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Battle);
		WorldPos = WPos;
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 64,64 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
		type = Tile::kinds::battle;

	}
	~Battle1_Tile() {}

	void update();
	//void render();
};

//中ボス
class Battle2_Tile : public Tile
{
public:
	Battle2_Tile(VECTOR2 WPos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::MiddleBoss);
		WorldPos = WPos;
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 64,64 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
		type = Tile::kinds::middle;

	}
	~Battle2_Tile() {}

	void update();
	//void render();
};

//本ボス
class Battle3_Tile : public Tile
{
public:
	Battle3_Tile(VECTOR2 WPos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::LastBoss);
		WorldPos = WPos;
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 64,64 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
		type = Tile::kinds::last;

	}
	~Battle3_Tile() {}

	void update();
	//void render();
};

//////////////////////////////////////////
//////////////////////////////////////////


//シーン
class SceneMap :public ISCENE
{
public:
	//カメラ用
	VECTOR2 pos = {};

	virtual void update();
	virtual void render();
	virtual void init();
	virtual void deinit();
	virtual void deleteSprite();

	void startBattle();			//いっちゃん最初
	void ShopAndBattle();		//店・雑魚敵戦
	void BattleAndEvent();		//雑魚敵戦・イベント
	void ShopAndEvent();		//店・イベント
	void MiddleBoss();			//中ボス
	void LastBoss();			//本ボス

	//ルート分岐関連
	void inputTileSelect();
	void routePick();
	void nextSpawn();
	void routeMapping();
	void Signpost();

	//数取得
	int GetTileCount()const { return static_cast<int>(tiles.size()); }
	int GetMovedTileCount()const { return static_cast<int>(movedTiles.size()); }
	int GetNonMovedTileCount()const { return static_cast<int>(nonMovedTiles.size()); }


	//本体取得
	Tile* GetTile(int index) { return tiles.at(index).get(); }
	Tile* GetMovedTile(int index) { return movedTiles.at(index).get(); }
	Tile* GetNonMovedTile(int index) { return nonMovedTiles.at(index).get(); }

	//全削除
	void Clear();

	VECTOR2 WorldToLocal(VECTOR2 WPos) { return WPos - pos; }

private:
	Map_Tile Map;

	float posMemory_x;
	float posMemory_y0;

	float posMemory_y1;
	float posMemory_y2;

	//マスを入れる配列
	std::vector<std::unique_ptr<Tile>>	tiles;
	//通らなかったマスを入れる配列
	std::vector<std::unique_ptr<Tile>> nonMovedTiles;
	//移動後のマスを入れる配列
	std::vector<std::unique_ptr<Tile>>  movedTiles;

};
