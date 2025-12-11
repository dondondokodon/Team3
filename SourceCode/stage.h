#pragma once
#include"../GameLib/game_lib.h"
#include"OBJ2D.h"
//抽象クラス 背景
class Stage : public OBJ2D
{
public:
	Stage(){};
	virtual ~Stage() {};
	virtual void update() = 0;
	virtual void init() = 0;
	virtual void deinit() = 0;
};

//ステージ１
class Stage01 : public Stage
{
public:
	Stage01();
	~Stage01();
	void update();
	void init();
	void deinit();
	int a;
};