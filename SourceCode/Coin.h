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
	static int LightAttackReward() { return RewardCoin(lightRatio); }
	static int HeavyAttackReward() { return RewardCoin(heavyRatio); }
	static float lightRatio;
	static float heavyRatio;

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

	void update() override;
	void render()override
	{
		OBJ2D::render();

		// 桁数を求める
		int num = Coin::GetCoinNum();
		int temp = num;
		int digit = 1;
		while (temp >= 10)
		{
			temp /= 10;
			digit *= 10;
		}

		// 大きい桁から取り出す
		int i = 0;
		while (digit > 0)
		{
			int d = num / digit;   // 先頭の桁

			char str = (d + '0');
			std::string strin(1, str);
			text_out(7, strin, pos.x + i * 30 + 40, pos.y - 20, scale.x, scale.y, 1.0f, 1.0f, 0.0f, 1.0f);
			num %= digit;          // 先頭桁を削除
			digit /= 10;
			i++;
		}
	}
};