#pragma once
#include "Character.h"

class CAMERA
{
private:
	VECTOR2 pos;
	float width;
	float height;

	float stageLimitX;	//ステージの一番右
	float stageLimitY;	//ステージの一番上

	const float DEADZONE_LEFT   = 300.0f;		//カメラが動かない範囲
	const float DEADZONE_RIGHT  = 900.0f;
	const float DEADZONE_TOP    = 200.0f;
	const float DEADZONE_BOTTOM = 540.0f;

public:
	CAMERA();
	void init();
	void update(Character& target);
	void setStageLimit(VECTOR2 xy) { stageLimitX = xy.x;	stageLimitY = xy.y; }
	VECTOR2 getPos() { return pos; }
};

