#pragma once
#include "Scene.h"
#include "common.h"
#include<memory>

class SceneTutorial :
    public ISCENE
{
private:
	std::shared_ptr<Sprite> spr;
	VECTOR2 texPos;
	int buttonCount = 0;
	int loopCount = 0;
public:
	SceneTutorial() {}
	virtual ~SceneTutorial() {}
	void update() override;
	void render() override;
	void init() override;
	void deinit() override;
	void deleteSprite() override;
};

