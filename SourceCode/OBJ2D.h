#pragma once
#include<memory>
#include "../GameLib/game_lib.h"
#include"common.h"

class CAMERA;

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
	VECTOR2 direction;
	int angle;
	std::shared_ptr<GameLib::Sprite> spr;
	
	int act;
	int timer;
	int anime;
	int animeTimer;
	int anime_state;
	float radius;     // îºåa

public:
	void setSprite(std::shared_ptr<Sprite> s)
	{
		spr = s;
	}

	std::shared_ptr<Sprite> getSprite() { return spr; }

	virtual void render()
	{
		if (!spr) return;
		sprite_render(spr.get(), pos.x, pos.y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle, color.x, color.y, color.z, color.w);
	}

	void hitAreaRender(CAMERA& camera);
	

	void cameraRender(CAMERA& camera);

	virtual void init() {}
	virtual void deinit() {}
	virtual void update() =0;
	bool animeUpdate(int animeNo, int total, int frame, bool loop);

	int                 hitPrimitive;//ï®ÇÃå`
	VECTOR2 getPos() { return pos; }
	VECTOR2 getScale() { return scale; }
	float getRadius() { return radius; }
	VECTOR2 getTexPos() { return texPos; }
	VECTOR2 getTexSize() { return texSize; }
	VECTOR2 getOffset() { return offset; }
	int getAct() { return act; }
	int getAnime() { return anime; }
	VECTOR2 getSpeed() { return speed; }
	VECTOR2 getPivot() { return pivot; }
	VECTOR2 getDir() { return direction; }

	void setScale(VECTOR2 Scale) { scale = Scale; }
	void setAct(int Act) { act = Act; }
	void setColor(VECTOR4 c) { color = c; }

	void setPosition(VECTOR2 p) { pos = p; }
	void setSpeed(VECTOR2 Speed) { speed = Speed; }
};

void gravity(OBJ2D* obj);	//èdóÕ
void friction(OBJ2D* obj);	//ñÄéC