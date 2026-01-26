#pragma once
#include "Scene.h"
#include<memory>
#include "Events.h"
#include "Coin.h"

extern bool resetMap;


class SceneEvent :public ISCENE
{
private:
	std::unique_ptr<Events> event;
	std::shared_ptr<GameLib::Sprite> spr;
	CoinUi coinUi;
public:
	void update()override;
	void render()override;
	void init()override;
	void deinit()override;
	void deleteSprite()override {};
};