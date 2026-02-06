#include "Coin.h"
#include "ImageManager.h"
#include <string>

//コインの初期値
long int Coin::CoinNum = 500;
long int Coin::gotCoin = 0;
//
long int Coin::moveCoin = Coin::CoinNum;
float Coin::lightRatio = 2.5f;
float Coin::heavyRatio = 1.5f;


long int Coin::GetRatioCoin(float ratio)
{
	moveCoin = CoinNum;	//ここでコピー
	moveCoin *= ratio;
	return moveCoin;
}

CoinUi::CoinUi()
{
	pos = { SCREEN_W * 0.04f,SCREEN_H * 0.07f };
	scale = { 1.5,1.5 };
	texPos = { 0,0 };
	texSize = { 50,50 };
	pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
	color = { 1,1,1,1 };
	speed = { 0,0 };
	offset = { 0,0 };
	angle = 0;
	act = 0;
	timer = 0;
	anime = 0;
	animeTimer = 0;
	anime_state = 0;
	radius = texSize.x * 0.2f * scale.x;;
}

void CoinUi::update()
{
}