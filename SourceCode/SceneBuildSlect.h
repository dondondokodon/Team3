#pragma once
#include "Scene.h"
#include "OBJ2D.h"
#include"ImageManager.h"
#include <vector>
#include "Build.h"
#include "Coin.h"

//基底クラス
class BuildCard : public OBJ2D
{
public:
	virtual void update() {};
	//enum kinds
	//{
	//	veryCost,
	//	extraJump,
	//	motionRapid,
	//};

	enum rank
	{
		weak,
		strong
	};

	int value = 0;
	int build = -1;
	int power = -1;
};

////ビルド強
//class strongCard :public BuildCard
//{
//
//};
//
////ビルド弱
//class weakCard :public BuildCard
//{
//
//};

//コストアップ
class VeryCostUpBuild : public BuildCard
{
public:
	VeryCostUpBuild(VECTOR2 pos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::STRONG);
		this->pos = pos;
		scale = { 0.8,0.8 };
		texPos = { 0,0 };
		texSize = { 376,596 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
		//build = BuildCard::kinds::veryCost;
		power = BuildCard::rank::strong;
		value = 500;
	}
	~VeryCostUpBuild() {}

	void update()override
	{ 
		Build::extraVeryCost = true; 
	    Coin::DegCoinNum(value);
	};
	//void render();
};

//ジャンプ追加
class ExtraJumpBuild : public BuildCard
{
public:
	ExtraJumpBuild(VECTOR2 pos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::WEAK);
		this->pos = pos;
		scale = { 0.8,0.8 };
		texPos = { 0,0 };
		texSize = { 368,590 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
		//build = BuildCard::kinds::extraJump;
		power = BuildCard::rank::weak;
		value =200;

	}
	~ExtraJumpBuild() {}

	void update()override
	{
		Build::extraJump = true;
		Coin::DegCoinNum(value);

	};
	//void render();
};

//モーション加速
class MotionRapidBuild : public BuildCard
{
public:
	MotionRapidBuild(VECTOR2 pos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::selectingGetPark);
		this->pos = pos;
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 320,640 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
		//build = BuildCard::kinds::motionRapid;
		power = BuildCard::rank::weak;
		value = 200;

	}
	~MotionRapidBuild() {}

	void update()override 
	{
		Build::extraMotionRapid = true;
		Coin::DegCoinNum(value);
	};
	//void render();
};

//重力低下
class MoonGravityBuild : public BuildCard
{
public:
	MoonGravityBuild(VECTOR2 pos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::selectingGetPark);	//ここ差し替え
		this->pos = pos;
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 320,640 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
		//build = BuildCard::kinds::motionRapid;
		power = BuildCard::rank::weak;
		value = 200;

	}
	~MoonGravityBuild() {}

	void update()override 
	{
		Build::extraMoonGravity = true;
		Coin::DegCoinNum(value);
	};
	//void render();
};

//追撃弾追加
class ExtraBulletBuild : public BuildCard
{
public:
	ExtraBulletBuild(VECTOR2 pos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::selectingGetPark);	//ここ差し替え
		this->pos = pos;
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 320,640 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
		//build = BuildCard::kinds::motionRapid;
		power = BuildCard::rank::strong;
		value = 500;

	}
	~ExtraBulletBuild() {}

	void update()override 
	{
		Build::extraBullet = true; 
		Coin::DegCoinNum(value);
	};
	//void render();
};

class SceneBuildSelect :public ISCENE
{
private:

public:
	void update();
	void render();
	void init();
	void deinit();
	void deleteSprite();
	std::shared_ptr<GameLib::Sprite> spr;

	void inputCardSelect();
	void cardPick();
	void setBuild();

	int GetCardCount()const { return static_cast<int>(showWindow.size()); }
	int GetUsedCardCount()const { return static_cast<int>(soldOut.size()); }

	BuildCard* GetCard(int index) { return showWindow.at(index).get(); }
	BuildCard* GetUsedCard(int index) { return soldOut.at(index).get(); }

	std::vector<std::unique_ptr<BuildCard>>  showWindow;
	std::vector<std::unique_ptr<BuildCard>>  soldOut;
};

