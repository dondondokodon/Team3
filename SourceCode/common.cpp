#include "common.h"
class VECTOR2;

//  定数
const FLOAT PI{ DirectX::XM_PI };
const LONG SCREEN_W{ 1280 };
const LONG SCREEN_H{ 720 };
const LONG GROUND_Y{ 700 };
const BOOL FULLSCREEN{ FALSE };
const LPCWSTR APPLICATION_NAME{ L"C++ project template" };

//  関数ポインタ
float(* const ToRadian)(float) = DirectX::XMConvertToRadians;  // 角度をラジアンに
float(* const ToDegree)(float) = DirectX::XMConvertToDegrees;  // ラジアンを角度に

bool hitCircle(VECTOR2 pos1, float r1, VECTOR2 pos2, float r2)
{
	float distX = pos1.x - pos2.x;
	float distY = pos1.y - pos2.y;
	float distR = r1 + r2;

	return (distX * distX + distY * distY) <= (distR * distR);

}

VECTOR2 normalize(const VECTOR2& v)
{
	float len = sqrt(v.x * v.x + v.y * v.y);
	if (len == 0.0f)
		return { 0.0f, 0.0f };

	return { v.x / len, v.y / len };
}


VECTOR2 rotate(const VECTOR2& v, float rad)
{
	float c = cosf(rad);
	float s = sinf(rad);

	return { v.x * c - v.y * s,
			v.x * s + v.y * c };
}