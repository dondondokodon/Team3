#pragma once

//コイン（HPも兼ねているMPみたいなイメージ）
class Coin
{
private:
	static int CoinNum;	///現在の合計枚数

public:
	int GetCoinNum()const { return CoinNum; }		//ゲッター
	void SetCoinNum(int coin) { CoinNum = coin; }	//セッター（多分使わない）

	void AddCoinNum(int add) { CoinNum += add; }	//加算
	void DegCoinNum(int deg) { CoinNum += deg; }	//減算

	int GetRatioCoin(float ratio) { return CoinNum *= ratio; }	//割合で取りだす


};

