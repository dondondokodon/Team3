#pragma once

#include "../GameLib/game_lib.h"
using namespace GameLib;

//  シーンのラベル
enum
{
	SCENE_NONE = -1,
	SCENE_TITLE,
	SCENE_TUTORIAL,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_GAMEOVER,
	SCENE_MOVIE,
	SCENE_MAX
};

//  定数
extern const FLOAT PI;
extern const LONG SCREEN_W;
extern const LONG SCREEN_H;
extern const BOOL FULLSCREEN;
extern const LPCWSTR APPLICATION_NAME;

//  関数ポインタ
extern float(* const ToRadian)(float);// 角度をラジアンに
extern float(* const ToDegree)(float);// ラジアンを角度に

