#pragma once
#include"Scene.h"
#include"OBJ2D.h"


class titleSprite : public OBJ2D
{
public:
	titleSprite()
	{
		pos = {};
		scale = { 1,1 };
		texPos = { 0,0 };
		texSize = { 1280, 720 };
		pivot = { 0,0 };
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
	void init();
	virtual ~titleSprite(){}
	virtual void update() override {}

};

class SceneTitle :public ISCENE
{
private:
	titleSprite tramp[5];
public:
	std::shared_ptr<GameLib::Sprite> spr;

	virtual void update();
	virtual void render();
	virtual void init();
	virtual void deinit();
	virtual void deleteSprite();
};
