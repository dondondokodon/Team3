#include "Coin.h"

//コインの初期値
int Coin::CoinNum = 1500;

//
int Coin::moveCoin = Coin::CoinNum;

int Coin::GetRatioCoin(float ratio)
{
	moveCoin = CoinNum;	//ここでコピー
	moveCoin *= ratio;
	return moveCoin;
}