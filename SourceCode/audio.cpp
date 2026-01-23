#include "Audio.h"
#include "../GameLib/game_lib.h"
using namespace GameLib;

void audio_init()
{
	//BGM
	music::load(main, L"./Data/Musics/main.wav");
	music::load(result, L"./Data/Musics/result.wav");
	music::load(battle, L"./Data/Musics/battle.wav");

	//SE
	music::load(coinGet, L"./Data/Sounds/コイン獲得時のエフェクト.wav");
	music::load(P_jump, L"./Data/Sounds/ジャンプ　自機.wav");
	music::load(P_jump2, L"./Data/Sounds/自機キャラのジャンプ.wav");
	music::load(P_doge, L"./Data/Sounds/回避サウンド.wav");
	music::load(P_lightA, L"./Data/Sounds/軽攻撃サウンド.wav");
	music::load(P_hit, L"./Data/Sounds/自機被弾.wav");
	music::load(P_HeavyA, L"./Data/Sounds/重攻撃サウンド.wav");
	music::load(B_jumpA1, L"./Data/Sounds/ボスとびかかり.wav");
	music::load(B_jumpA2, L"./Data/Sounds/ボスとびかかり2.wav");		
	music::load(B_Jump,L"./Data/Sounds/ボスのジャンプ時のサウンド.wav");
	music::load(B_tailA,L"./Data/Sounds/ボスの尻尾突き.wav");
	music::load(B_hit,L"./Data/Sounds/ボスの被弾.wav");
	music::load(B_Shout,L"./Data/Sounds/ボスの咆哮2.wav");
	music::load(titlePic,L"./Data/Sounds/タイトル決定音.wav");
	music::load(tranpFly,L"./Data/Sounds/トランプが飛ぶ音.wav");
	music::load(buttonPic,L"./Data/Sounds/ボタンの選択音.wav");
	music::load(result1,L"./Data/Sounds/リザルト表示.wav");
	music::load(result3,L"./Data/Sounds/リザルト表示3.wav");
	music::load(buy,L"./Data/Sounds/購入音.wav");
	music::load(zako2_A,L"./Data/Sounds/雑魚キャラ２の打撃.wav");
	music::load(zakoFlyA,L"./Data/Sounds/飛ぶ雑魚キャラの飛ばす攻撃.wav");
	music::load(pic,L"./Data/Sounds/選択音.wav");
	music::load(bigAttack,L"./Data/Sounds/大技の溜め.wav");
	music::load(score,L"./Data/Sounds/評価表示音.wav");
}

void audio_deinit()
{
	music::clear();
}