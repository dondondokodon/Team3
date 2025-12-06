#pragma once
#include<memory>
#include "../GameLib/game_lib.h"
#include"common.h"
using namespace GameLib;
using namespace input;

enum hitPrimitive
{
	circle,
	rect,
	line
};

class OBJ2D
{
protected:
	VECTOR2 pos;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;
	VECTOR2 speed;
	VECTOR2 offset;
	int angle;
	std::shared_ptr<GameLib::Sprite> spr;
	
	int act;
	int timer;
	int anime;
	int animeTimer;
	int anime_state;
	float radius;     // ”¼Œa

public:
	void setSprite(std::shared_ptr<Sprite> s)
	{
		spr = s;
	}

	virtual void render()
	{
		if (!spr) return;
		sprite_render(spr.get(), pos.x, pos.y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle, color.x, color.y, color.z, color.w);
	}

	virtual void init() {}
	virtual void deinit() {}
	virtual void update() =0;
	bool animeUpdate(int animeNo, int total, int frame, bool loop);

	int                 hitPrimitive;//•¨‚ÌŒ`
	VECTOR2 getPos() { return pos; }
	VECTOR2 getScale() { return scale; }
	bool getRadius() { return radius; }
	int getAct() { return act; }
	int getAnime() { return anime; }


	void setScale(VECTOR2 Scale) { scale = Scale; }
	void setAct(int Act) { act = Act; }
	void setColor(VECTOR4 c) { color = c; }

	
	void setSpeed(VECTOR2 Speed) { speed = Speed; }
};
