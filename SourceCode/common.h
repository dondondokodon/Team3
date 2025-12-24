#pragma once

#include "../GameLib/game_lib.h"
using namespace GameLib;

//  シーンのラベル
enum
{
	SCENE_NONE = -1,
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_MAP,
	//SCENE_TUTORIAL,
	
	SCENE_MAX
};

//  定数
extern const FLOAT PI;
extern const LONG SCREEN_W;
extern const LONG SCREEN_H;
extern const BOOL FULLSCREEN;
extern const LPCWSTR APPLICATION_NAME;
extern const LONG GROUND_Y;

//  関数ポインタ
extern float(* const ToRadian)(float);// 角度をラジアンに
extern float(* const ToDegree)(float);// ラジアンを角度に

bool hitCircle(VECTOR2 pos1, float r1, VECTOR2 pos2, float r2);