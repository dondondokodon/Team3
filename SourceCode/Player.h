#pragma once
#include "Character.h"
#include "Coin.h"
#include <vector>
#include <memory>
#include "Build.h"
#include "ProjectileManager.h"

class StageLayer;

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
	void CheckHitWall(const HitWall& wall);

	//ビルド関連
	void addEffect(std::unique_ptr<Build> e) { builds.push_back(std::move(e)); }	//追加
	void clearEffect() { builds.clear(); }											//削除

	int GetMaxJump();
	void ResetJumpCount() { jumpCount = GetMaxJump(); }
	void setCost();
	void setHeavyVeryCost();
	void setAttackFrame();
	void setGravity();
	void setDEF();
	void setRewardRatio();
	void setLightAtk();

	void setHitWall(HitWall set) { targetHitWall = set; }
	void setSpeed(VECTOR2 set) { speed = set; }
	void setIsGround(bool set) { isGround = set; }
	void setPos(VECTOR2 set) { pos = set; }
	void setBeforeLayer(StageLayer* layer) { beforeLayer = layer; }
	StageLayer* getBeforeLayer()const { return beforeLayer; }

	bool lightAttack = false;	//軽攻撃フラグ
	bool heavyAttack = true;	//重攻撃フラグ

	float getLightRatio()const { return lightBetRatio; }
	float getHeavyRatio()const { return heavyBetRatio; }
	VECTOR2 getBeforePos()const { return beforePos; }
	void addLightRatio(float ratio) { lightBetRatio += ratio; }
	void addHeavyRatio(float ratio) { heavyBetRatio += ratio; }

	void degHeavyBulletSpeed(VECTOR2 speed) { heavySpeed -= speed; }
	void addHeavyBulletScale(VECTOR2 scale) { heavyScale += scale; }
	void addHeavyBulletRadius(float radius) { heavyRadius += radius; }

	void degAttackFrame(int frame) { attack_frame -= frame; }
	void setSpeedX(float Speed) { maxSpeed += Speed; }

	VECTOR2 setLightAtkSpeed(VECTOR2 Speed) { return lightSpeed += Speed; }
	VECTOR2 setLightAtkSize(VECTOR2 size) { return lightScale += size; }
	float setLightLife(float limit) { return lightLifeLimit += limit; }

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
	float heavyBetRatio = 0.10f;	//重攻撃消費コイン割合
	VECTOR2 MAX_SPEED;	//最高速度
	float maxSpeed = 7;		//ビルドでいじる用
	bool attack2Reserve = false;// 次弾攻撃予約
	bool dodgeReserve   = false;// 回避予約
	bool isDeathOn      = false;

	const float  moveLimitLeft =20; //移動できる範囲左
	const float  moveLimitRight=SCREEN_W*2+200; //移動できる範囲左
	
	int baseMaxJump = 2;		//最大のジャンプ回数
	int jumpCount = 2;			//残りのジャンプ回数
	int attack_frame = 5;		//攻撃時のフレーム数
	int animeCount;
	float oldFallEnemgyY = 0.0f;	//落下時の重力加速度y成分
	HitWall beforeWall;		//１フレーム前の
	VECTOR2 beforePos;		//１フレーム前の位置

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
	HitWall targetHitWall;
	StageLayer* beforeLayer=nullptr;


	std::shared_ptr<Sprite> playerBullet;

	
	//ビルド関係
	std::vector<std::unique_ptr<Build>> builds;

};

