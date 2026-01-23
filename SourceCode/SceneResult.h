#pragma once
#include"Scene.h"
#include"stage.h"
class SceneResult :public ISCENE
{
private:
	resultScene sprite;
	static std::string textTime;

public:
	void update()override;
	void render()override;
	void init()override;
	void deinit()override;
	void deleteSprite()override {};
};