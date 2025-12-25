#pragma once
#include "Character.h"
#include "Coin.h"
#include <vector>
#include <memory>
#include "Build.h"
#include "ProjectileManager.h"

class Player :
    public Character
{
public:
	Player();
	void init();
	void deinit();
	void update();
	void betCoin(int gold,float atkMultiple,float goldMultiple);		//攻撃するときにかけるお金 引数　掛け金　攻撃力倍率　帰ってくるお金倍率
	bool isDeath() { return (gold <= 0 && returnGold <= 0); }
	void inputMove();
	void inputJump();
	void state();
	void InputProjectile();

	//ビルド関連
	void addEffect(std::unique_ptr<Build> e) { builds.push_back(std::move(e)); }	//追加
	void clearEffect() { builds.clear(); }											//削除

	int GetMaxJump();
	void ResetJumpCount() { jumpCount = GetMaxJump(); }

	bool lightAttack = false;	//軽攻撃フラグ
private:
	int gold       = Coin::GetCoinNum(); //お金
	int returnGold = 0; //攻撃を当てた時に帰ってくるお金
	const VECTOR2 MAX_SPEED;	//最高速度
	bool isGround = false;
	int baseMaxJump = 2;	//最大のジャンプ回数
	int jumpCount = 2;		//残りのジャンプ回数
	//ProjectileManager projMgr;

	
	enum ACT
	{
		IDLE_INIT,
		IDLE,
		WALK_INIT,
		WALK,
		JUMP_INIT,
		JUMP,
		FALL_INIT,
		FALL,
		ATTACK1_INIT,
		ATTACK1,
		ATTACK2_INIT,
		ATTACK2,
	};
	//ビルド関係
	std::vector<std::unique_ptr<Build>> builds;

};

