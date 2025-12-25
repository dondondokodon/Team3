#include "Coin.h"

//コインの初期値
int Coin::CoinNum = 1500;

//関数内計算用
int Coin::moveCoin = Coin::CoinNum;

int Coin::GetRatioCoin(float ratio)
{
	moveCoin = CoinNum;	//ここでコピー
	moveCoin *= ratio;
	return moveCoin;
}