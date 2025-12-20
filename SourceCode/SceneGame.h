#pragma once
#include"Scene.h"
#include"Player.h"
#include"Enemy.h"
#include"stage.h"
#include "CAMERA.h"
class SceneGame:public ISCENE
{
private:
	int frame;
	Player player;
	Stage01 stage;
	CAMERA camera;
	Enemy enemy;
public:
	virtual void update();
	virtual void render();
	virtual void init();
	virtual void deinit();
	virtual void deleteSprite();

};