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
	void cameraRender(CAMERA& camera);
	void betCoin(int gold,float atkMultiple,float goldMultiple);		//攻撃するときにかけるお金 引数　掛け金　攻撃力倍率　帰ってくるお金倍率
	bool isDeath() { return isDeathOn; }
	void inputMove();
	void inputJump();
	void inputDodge();
	void state();
	void InputProjectile();

	//ビルド関連
	void addEffect(std::unique_ptr<Build> e) { builds.push_back(std::move(e)); }	//追加
	void clearEffect() { builds.clear(); }											//削除

	int GetMaxJump();
	void ResetJumpCount() { jumpCount = GetMaxJump(); }
	void setHeavyCost();
	void setHeavyVeryCost();
	void setAttackFrame();
	void setGravity();
	void setDEF();

	bool lightAttack = false;	//軽攻撃フラグ
	bool heavyAttack = true;	//重攻撃フラグ

	float getLightRatio()const { return lightBetRatio; }
	float getHeavyRatio()const { return heavyBetRatio; }
	void addLightRatio(float ratio) { lightBetRatio += ratio; }
	void addHeavyRatio(float ratio) { heavyBetRatio += ratio; }

	void degHeavyBulletSpeed(VECTOR2 speed) { heavySpeed -= speed; }
	void addHeavyBulletScale(VECTOR2 scale) { heavyScale += scale; }
	void addHeavyBulletRadius(float radius) { heavyRadius += radius; }

	void degAttackFrame(int frame) { attack_frame -= frame; }

	//追撃弾
	float getPursuitLife()const { return lightLifeLimit; }
	float getPursuitRadius()const { return lightRadius; }
	VECTOR2 getPursuitSpeed()const { return lightSpeed; }
	VECTOR2 getPursuitScale()const { return lightScale; }
	VECTOR2 getPursuitSize()const { return lightTexSize; }

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
		LANDING_INIT,
		LANDING,
		ATTACK1_INIT,
		ATTACK1,
		ATTACK2_INIT,
		ATTACK2,
		HEAVY_ATTACK1_INIT,
		HEAVY_ATTACK1,
		HEAVY_ATTACK2_INIT,
		HEAVY_ATTACK2,
		DODGE_INIT,
		DODGE,
		DEATH_INIT,
		DEATH
	};

private:
	int gold       = Coin::GetCoinNum(); //お金
	int returnGold = 0;			//攻撃を当てた時に帰ってくるお金
	float lightBetRatio = 0.01f;//軽攻撃消費コイン割合
	float heavyBetRatio = 0.1f;	//重攻撃消費コイン割合
	const VECTOR2 MAX_SPEED;	//最高速度
	bool attack2Reserve = false;// 次弾攻撃予約
	bool isDeathOn      = false;

	const float  moveLimitLeft =20; //移動できる範囲左
	const float  moveLimitRight=SCREEN_W*2+200; //移動できる範囲左
	
	int baseMaxJump = 2;		//最大のジャンプ回数
	int jumpCount = 2;			//残りのジャンプ回数
	int attack_frame = 5;		//攻撃時のフレーム数
	int animeCount;

	//球関連
	VECTOR2 lightSpeed = { 15,15 };
	VECTOR2 lightScale = { 3,3 };
	float lightLifeLimit = 0.7f;
	VECTOR2 lightTexSize = { 6,6 };
	float lightRadius = 3.0f;

	VECTOR2 heavySpeed = { 10,10 };
	VECTOR2 heavyScale = { 8.0,8.0 };
	float heavyLifeLimit = 0.5f;
	VECTOR2 heavyTexSize = { 6,6 };
	float heavyRadius = 3.0f;
	VECTOR2 drawPos;
	bool drawPosFlag;
	const VECTOR2 drawPosOffet = { -100,-90 };


	std::shared_ptr<Sprite> playerBullet;

	
	//ビルド関係
	std::vector<std::unique_ptr<Build>> builds;

};

