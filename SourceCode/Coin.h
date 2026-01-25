#pragma once
#include "OBJ2D.h"
#include "audio.h"

//コイン（HPも兼ねているMPみたいなイメージ）
class Coin
{
private:
	static int CoinNum;	//現在の合計枚数
	static int moveCoin;//動く枚数
	static int gotCoin;	//総獲得コイン数

public:
	static int GetCoinNum() { return CoinNum; }				//ゲッター
	static void SetCoinNum(int coin) { CoinNum = coin; }	//セッター（多分使わない）

	static void AddCoinNum(int add) { CoinNum += add;  music::play(coinGet);}		//加算
	static void DegCoinNum(int deg) { CoinNum -= deg; }		//減算

	static int GetRatioCoin(float ratio);	//割合で取りだす
											//攻撃で使用した場合、しっかり減算してね

	static int RewardCoin(float ratio) { return moveCoin * ratio; }	//返ってくるコイン
	static int LightAttackReward() { return RewardCoin(2.5f); }
	static int HeavyAttackReward() { return RewardCoin(1.5f); }

	//ダメージ計算
	static int calcDamage(int baseDamage, int coin) { return baseDamage * coin; }

	static void AddGotCoin(int add) { gotCoin += add; }	//獲得した枚数を入れる
	static int GetGotCoin() { return gotCoin; }			//獲得した枚数のゲッター
	static void ResetGotCoin() { gotCoin = 0; }			//獲得したコインを０に戻す

};

class CoinUi : public OBJ2D
{
public:
	CoinUi();
	~CoinUi() {}

	void update(){}
};