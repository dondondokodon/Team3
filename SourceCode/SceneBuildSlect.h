#pragma once
#include "Scene.h"
#include "OBJ2D.h"
#include"ImageManager.h"
#include <vector>

//基底クラス
class BuildCard : public OBJ2D
{
public:
	virtual void update() {};
};

//ビルド0
class VeryCostUpBuild : public BuildCard
{
public:
	VeryCostUpBuild(VECTOR2 pos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::veryCostUp);
		this->pos = pos;
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 320,640 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
	}
	~VeryCostUpBuild() {}

	void update()override;
	//void render();
};

//ビルド1
class ExtraJumpBuild : public BuildCard
{
public:
	ExtraJumpBuild(VECTOR2 pos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::extraJump);
		this->pos = pos;
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 320,640 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
	}
	~ExtraJumpBuild() {}

	void update()override;
	//void render();
};

//ビルド2
class MotionRapidBuild : public BuildCard
{
public:
	MotionRapidBuild(VECTOR2 pos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::motionRapid);
		this->pos = pos;
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 320,640 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
	}
	~MotionRapidBuild() {}

	void update()override;
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
	int GetCardCount()const { return static_cast<int>(showWindow.size()); }
	int GetUsedCardCount()const { return static_cast<int>(soldOut.size()); }

	BuildCard* GetCard(int index) { return showWindow.at(index).get(); }
	BuildCard* GetUsedCard(int index) { return soldOut.at(index).get(); }

	std::vector<std::unique_ptr<BuildCard>>  showWindow;
	std::vector<std::unique_ptr<BuildCard>>  soldOut;
};

