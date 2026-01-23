#pragma once
#include "Scene.h"


class SceneEvent :public ISCENE
{
private:
	
public:
	void update()override;
	void render()override;
	void init()override;
	void deinit()override;
	void deleteSprite()override {};
};