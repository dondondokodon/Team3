#pragma once
#include <memory>
#include"Scene.h"
#include"Player.h"
#include"stage.h"
#include "CAMERA.h"
#include "ProjectileManager.h"
#include "ProjectileStraight.h"
#include "Coin.h"
#include <vector>

class SceneGame:public ISCENE
{
private:
	int frame;
	Player player;
	//Stage01 stage01;
	//Stage02 stage02;
	CAMERA camera;
	CoinUi coinUi;
	std::vector<std::unique_ptr<Stage>>	stages;

public:
	SceneGame();
	virtual void update();
	virtual void render();
	virtual void init();
	virtual void deinit();
	virtual void deleteSprite();
	void Collision();
	void SwitchStage();
	void SwitchEnemyType();
};