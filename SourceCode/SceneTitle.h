#pragma once
#include"Scene.h"
#include"Player.h"
#include"stage.h"

class SceneTitle :public ISCENE
{
private:
	Player player;
	Stage01 stage;
public:
	virtual void update();
	virtual void render();
	virtual void init();
	virtual void deinit();
	virtual void deleteSprite();
};