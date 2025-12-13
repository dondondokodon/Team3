#pragma once

//コイン（HPも兼ねているMPみたいなイメージ）
class Coin
{
private:
	static int CoinNum;	///現在の合計枚数

public:
	static int GetCoinNum() { return CoinNum; }				//ゲッター
	static void SetCoinNum(int coin) { CoinNum = coin; }	//セッター（多分使わない）

	static void AddCoinNum(int add) { CoinNum += add; }		//加算
	static void DegCoinNum(int deg) { CoinNum += deg; }		//減算
	 
	static int GetRatioCoin(float ratio) { return CoinNum *= ratio; }	//割合で取りだす


};

