#pragma once
#include"Scene.h"
#include"Player.h"
#include"stage.h"
#include "CAMERA.h"
#include "ProjectileManager.h"
#include "ProjectileStraight.h"

class SceneGame:public ISCENE
{
private:
	int frame;
	Player player;
	Stage01 stage;
	CAMERA camera;
	ProjectileManager projMgr;

public:
	virtual void update();
	virtual void render();
	virtual void init();
	virtual void deinit();
	virtual void deleteSprite();

};