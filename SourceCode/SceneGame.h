#pragma once
#include <memory>
#include"Scene.h"
#include"Player.h"
#include"stage.h"
#include "CAMERA.h"
#include "ProjectileManager.h"
#include "ProjectileStraight.h"
#include "Coin.h"

class SceneGame:public ISCENE
{
private:
	int frame;
	Player player;
	Stage01 stage;
	CAMERA camera;
	CoinUi coinUi;

public:
	SceneGame();
	virtual void update();
	virtual void render();
	virtual void init();
	virtual void deinit();
	virtual void deleteSprite();
	void Collision();
};