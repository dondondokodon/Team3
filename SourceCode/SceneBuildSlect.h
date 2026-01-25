#pragma once
#include "Scene.h"
#include "OBJ2D.h"
#include"ImageManager.h"
#include <vector>
#include "Build.h"
#include "Coin.h"

extern class buffDebuff;

//基底クラス
class BuildCard : public OBJ2D
{
public:
	virtual void update() {};
	enum kinds
	{
		VERYCOST,
		EXTRAJUMP,
		MOTIONRAPID,
		MOONGRAVITY,
		EXTRABULLET
	};

	enum rank
	{
		weak,
		strong
	};

	int getRank()const { return power; }
	int getPrice()const { return price; }

	int price = 0;
	int build = -1;
	int power = -1;

	static BuildCard& Instance()
	{
		static BuildCard instance;
		return instance;
	}
	void Register(std::unique_ptr<buffDebuff> effect) { effects.emplace_back(std::move(effect)); }
	void buffDebuffRender();
	void Clear() { effects.clear(); }

	int GetEffectCount()const { return effects.size(); }
	buffDebuff* GetEffect(int index) { return effects.at(index).get(); }

	//カードの効果を表示させるための配列
	std::vector<std::unique_ptr<buffDebuff>> effects;
};

//追加のスプライト
class extraSprite : public OBJ2D
{
public:
	extraSprite(std::shared_ptr<GameLib::Sprite> spr, VECTOR2 pos, VECTOR2 scale, VECTOR2 texPos, VECTOR2 texSize, VECTOR4 color, VECTOR2 speed, VECTOR2 offset, VECTOR2 direction)
	{
		this->spr = spr;
		this->pos = pos;
 		this->scale = scale;
		this->texPos = texPos;
		this->texSize = texSize;
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		this->color = color;
		this->speed = speed;
		this->offset = offset;
		this->direction = direction;
	}
	extraSprite() {}
	~extraSprite() {}

	std::string ShowPrice;
	VECTOR2 textPos;
	VECTOR4 textColor;

	void update()override {}
};

class buffDebuff : public OBJ2D
{
public:

	buffDebuff() {}
	virtual ~buffDebuff() {}

	void addPos(VECTOR2 Pos) { pos += Pos; }
	void update()override {}
};

class buff : public buffDebuff
{
public:

	buff(VECTOR2 Pos, int line, int row)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::buff);
		pos = Pos;
		scale = VECTOR2{ 1,1 };
		texSize = VECTOR2{ 285,277 };
		texPos = VECTOR2{ texSize.x * line, texSize.y * row };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = VECTOR4{ 1,1,1,1 };
		speed = VECTOR2{ 0,0 };
		offset = VECTOR2{ 0,0 };
		direction = VECTOR2{ 0,0 };


	}
	virtual ~buff() {};

};

class debuff : public buffDebuff
{
public:

	debuff(VECTOR2 Pos, int line, int row)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::debuff);
		pos = Pos;
		scale = VECTOR2{ 1,1 };
		texSize = VECTOR2{ 285,280 };
		texPos = VECTOR2{ texSize.x * line, texSize.y * row };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = VECTOR4{ 1,1,1,1 };
		speed = VECTOR2{ 0,0 };
		offset = VECTOR2{ 0,0 };
		direction = VECTOR2{ 0,0 };


	}
	virtual ~debuff() {};

};
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
		build = BuildCard::kinds::VERYCOST;
		power = BuildCard::rank::strong;
		price = 500;
		BuildCard::Instance().Register(std::make_unique<buff>(VECTOR2{ pos.x, pos.y - 130 }, 0, 0));
		BuildCard::Instance().Register(std::make_unique<debuff>(VECTOR2{ pos.x, pos.y + 120 }, 0, 0));

	}
	~VeryCostUpBuild() {}

	void update()override
	{ 
		Build::extraVeryCost = true;
		Coin::DegCoinNum(price);
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
		build = BuildCard::kinds::EXTRAJUMP;
		power = BuildCard::rank::weak;
		price = 200;
		BuildCard::Instance().Register(std::make_unique<buff>(VECTOR2{ pos.x, pos.y - 130 }, 0, 0));
		BuildCard::Instance().Register(std::make_unique<debuff>(VECTOR2{ pos.x, pos.y + 120 }, 0, 0));
	}
	~ExtraJumpBuild() {}

	void update()override
	{
		Build::extraJump = true;
		Coin::DegCoinNum(price);
	};
	//void render();
};

//モーション加速
class MotionRapidBuild : public BuildCard
{
public:
	MotionRapidBuild(VECTOR2 pos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::WEAK);
		this->pos = pos;
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 368,590 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
		build = BuildCard::kinds::MOTIONRAPID;
		power = BuildCard::rank::weak;
		price = 200;
		BuildCard::Instance().Register(std::make_unique<buff>(VECTOR2{ pos.x, pos.y - 130 }, 0, 0));
		BuildCard::Instance().Register(std::make_unique<debuff>(VECTOR2{ pos.x, pos.y + 120 }, 0, 0));

	}
	~MotionRapidBuild() {}

	void update()override 
	{
		Build::extraMotionRapid = true;
		Coin::DegCoinNum(price);
	};
	//void render();
};

//重力低下
class MoonGravityBuild : public BuildCard
{
public:
	MoonGravityBuild(VECTOR2 pos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::WEAK);	//ここ差し替え
		this->pos = pos;
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 368,590 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
		build = BuildCard::kinds::MOONGRAVITY;
		power = BuildCard::rank::weak;
		price = 200;
		BuildCard::Instance().Register(std::make_unique<buff>(VECTOR2{ pos.x, pos.y - 130 }, 0, 0));
		BuildCard::Instance().Register(std::make_unique<debuff>(VECTOR2{ pos.x, pos.y + 120 }, 0, 0));
	}
	~MoonGravityBuild() {}

	void update()override 
	{
		Build::extraMoonGravity = true;
		Coin::DegCoinNum(price);
	};
	//void render();
};

//追撃弾追加
class ExtraBulletBuild : public BuildCard
{
public:
	ExtraBulletBuild(VECTOR2 pos)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::STRONG);	//ここ差し替え
		this->pos = pos;
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 376,596 };
		pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		direction = { 0,0 };
		build = BuildCard::kinds::EXTRABULLET;
		power = BuildCard::rank::strong;
		price = 500;
		BuildCard::Instance().Register(std::make_unique<buff>(VECTOR2{ pos.x, pos.y - 130 }, 0, 0));
		BuildCard::Instance().Register(std::make_unique<debuff>(VECTOR2{ pos.x, pos.y + 120 }, 0, 0));

	}
	~ExtraBulletBuild() {}

	void update()override 
	{
		Build::extraBullet = true;
		Coin::DegCoinNum(price);
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
	//extraSprite* selectingMessage = new extraSprite{ VECTOR2{SCREEN_W * 0.5f,200.0f},VECTOR2{1,1},{0,0}, VECTOR2{684,93},VECTOR4{1,1,1,1},VECTOR2{0,0},VECTOR2{0,0},VECTOR2{0,0} };
	CoinUi money;

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

