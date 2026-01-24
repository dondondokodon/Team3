#pragma once
#include "Ghost.h"

class Effect:public Ghost
{
public:
	Effect(Character& chara);
	~Effect();
	void init()override;
	void deinit()override;
	void update()override;
	bool Remove();
protected:
	bool isRemove=false;
	Character* owner;
};

class EffectP :public Effect
{
public:
	EffectP(Character& chara);
	~EffectP();
	void init()override;
	void deinit()override;
	void update()override;
};

