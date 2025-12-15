#pragma once
#include "../GameLib/game_lib.h"

class CAMERA
{
private:
	VECTOR2 pos;
	float width;
	float height;

	float stageLimitX;	//ステージの一番右

	const float DEADZONE_LEFT  = 300.0f;		//カメラが動かない範囲
	const float DEADZONE_RIGHT = 500.0f;
public:
	CAMERA();
	void update(Character& target);
	void cameraRender(OBJ2D* obj);
	void setStageLimitX(float x) { stageLimitX = x; }
	VECTOR2 getPos() { return pos; }
};

