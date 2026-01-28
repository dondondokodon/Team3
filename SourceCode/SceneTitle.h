#pragma once
#include"Scene.h"
#include"OBJ2D.h"
#include"ImageManager.h"
#include<vector>

class titleSprite : public OBJ2D
{
public:
	titleSprite() {};
	virtual ~titleSprite() {}
	void update()override {}
};

class trampSprite : public titleSprite
{
public:
	trampSprite(VECTOR2 Pos, int Number, int Flip)
	{
		pos = Pos;
		scale = { 1,1 };
		texSize = { 743 ,509 };
		texPos = { texSize.x * Number,0 };
		pivot = { texSize.x * 0.5f ,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		angle = 0;
		act = 0;
		timer = 0;
		anime = 0;
		animeTimer = 0;
		anime_state = 0;
		radius = 0;
		number = Number;
		flip = Flip;
	}

	int number;
	enum trampNumber
	{
		S5 = 0,
		H5,
		H6,
		S7,
		H8
	};

	virtual ~trampSprite(){}
	void update()override;
	int getNumber()const { return number; }
	void trampImpulse(VECTOR2 Direction, float Impulse);
	VECTOR2 setDirection(VECTOR2 Pos);
	int flip;
	void addPos(VECTOR2 Pos) { pos += Pos; }
	void multipleSpeed(float Speed) { speed.x *= Speed; speed.y *= Speed;}

};



class titleText :public titleSprite
{
public:
	titleText(VECTOR2 Pos, VECTOR2 number)
	{
		pos = Pos;
		scale = { 1,1 };
		texSize = { 743 ,509 };
		texPos = { texSize.x * number.x ,texSize.y * number.y };
		pivot = { texSize.x * 0.5f ,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		angle = 0;
		act = 0;
		timer = 0;
		anime = 0;
		animeTimer = 0;
		anime_state = 0;
		radius = 0;
	}
	~titleText(){}
	void update() {};
};

class play : public titleSprite
{
public:
	play(VECTOR2 Pos, VECTOR2 number)
	{
		spr = nullptr;
		pos = Pos;
		scale = { 1,1 };
		texSize = { 743 ,509 };
		texPos = { texSize.x * number.x ,texSize.y * number.y };
		pivot = { texSize.x * 0.5f ,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		angle = 0;
		act = 0;
		timer = 0;
		anime = 0;
		animeTimer = 0;
		anime_state = 0;
		radius = 0;
	}
	~play() {}

	void update();
};

class TutorialButton : public titleSprite
{
public:
	TutorialButton(VECTOR2 Pos, VECTOR2 number)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::tutorialButton);;
		pos = Pos;
		scale = { 1,1 };
		texSize = { 399 ,39 };
		texPos = { texSize.x * number.x ,texSize.y * number.y };
		pivot = { texSize.x * 0.5f ,texSize.y * 0.5f };
		color = { 1,1,1,1 };
		speed = { 0,0 };
		offset = { 0,0 };
		angle = 0;
		act = 0;
		timer = 0;
		anime = 0;
		animeTimer = 0;
		anime_state = 0;
		radius = 0;
	}
	~TutorialButton() {}

	void update();
};

class SceneTitle :public ISCENE
{
private:
	std::vector<std::unique_ptr<titleSprite>> selectButton;
	std::vector<std::unique_ptr<titleSprite>> titleSprites;
	std::vector<std::unique_ptr<trampSprite>> trampCard;
	int selectIndex = 0;
	bool allowSelect = false;
public:
	std::shared_ptr<GameLib::Sprite> spr;

	int getButtonCount()const { return selectButton.size(); }
	titleSprite* getButton(int index) { return selectButton.at(index).get(); }

	virtual void update();
	virtual void render();
	virtual void init();
	virtual void deinit();
	virtual void deleteSprite();

	void selecting();
	//void pickButton();
};
