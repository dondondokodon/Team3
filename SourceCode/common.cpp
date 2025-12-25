#include "common.h"

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