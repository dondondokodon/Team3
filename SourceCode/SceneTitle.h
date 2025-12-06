#pragma once
#include"Scene.h"
#include"Player.h"

class SceneTitle :public ISCENE
{
private:
	Player player;
public:
	virtual void update();
	virtual void render();
	virtual void init();
	virtual void deinit();
	virtual void deleteSprite();
};