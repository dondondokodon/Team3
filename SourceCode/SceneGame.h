#pragma once
#include"Scene.h"

class SceneGame:public ISCENE
{
	virtual void update();
	virtual void render();
	virtual void init();
	virtual void deinit();
	virtual void deleteSprite();
};