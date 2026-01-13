#pragma once
#include "Scene.h"
#include "OBJ2D.h"
#include"ImageManager.h"

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
	

};

//基底クラス
class BuildCard : public OBJ2D
{
public:
	virtual void update() {};
};

//ビルド0
class Build0 : public BuildCard
{
public:
	Build0(VECTOR2 pos)
	{
		spr = std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load((L"./Data/Images/build0.png")));
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
	~Build0() {}

	void update()override;
	//void render();
};
