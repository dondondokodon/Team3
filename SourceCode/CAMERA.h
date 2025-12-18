#pragma once
#include "Character.h"

class CAMERA
{
private:
	VECTOR2 pos;
	float width;
	float height;

	float stageLimitX;	//ステージの一番右

	const float DEADZONE_LEFT  = 300.0f;		//カメラが動かない範囲
	const float DEADZONE_RIGHT = 900.0f;
public:
	CAMERA();
	void init();
	void update(Character& target);
	void setStageLimitX(float x) { stageLimitX = x; }
	VECTOR2 getPos() { return pos; }
};

