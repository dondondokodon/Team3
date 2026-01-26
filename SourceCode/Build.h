#pragma once

#include "../GameLib/game_lib.h"

class Player;


//追加効果(ビルド)の基底クラス
class Build
{
public:
	virtual ~Build() {}

	virtual void Update(Player& p) {}

	//ビルドフラグ
	static bool extraJump;
	static bool extraCost;
	static bool extraVeryCost;
	static bool extraMotionRapid;
	static bool extraMoonGravity;
	static bool extraBullet;
	static bool defenseDown;
	static bool extraReward;
	static bool extraSpeed;
	static bool lightChange;

	//中身 リファクタリングポイント
	virtual int AddMaxJump() const { return 0; }
	virtual float AddHeavyCost() const { return 0.0f; }
	virtual float AddLightCost() const { return 0.0f; }
	virtual float AddVeryCost() const { return 0.0f; }
	virtual VECTOR2 HeavyProjectileSpeed() const { return { 0.0f,0.0f }; }
	virtual VECTOR2 HeavyProjectileScale() const { return { 0.0f,0.0f }; }
	virtual float HeavyProjectileRadius() const { return  0.0f; }
	virtual VECTOR2 LightProjectileSpeed() const { return { 0.0f,0.0f }; }
	virtual VECTOR2 LightProjectileScale() const { return { 0.0f,0.0f }; }
	//virtual float LightProjectileRadius() const { return  0.0f; }
	virtual float HeavyProjectileLife()const { return 0.0f; }
	virtual float LightProjectileLife()const { return 0.0f; }
	virtual int degMotionFrameSpeed()const { return 0.0f; }
	virtual int addMotionFrameSpeed()const { return 0.0f; }
	virtual VECTOR2 degGravity() const { return { 0.0f,0.0f }; }
	virtual float degDefense() const { return 0.0f; }
	virtual float AddReward()const { return 0.0f; }
	virtual float degLightCost()const { return 0.0f; }
	virtual float degHeavyCost()const { return 0.0f; }
	virtual float DegMoveSpeed()const { return 0.0f; }
	virtual float AddMoveSpeed()const { return 0.0f; }



};


//ジャンプ追加
class ExtraJump : public Build
{
public:
	~ExtraJump() {}
	int AddMaxJump() const;
};

//攻撃時コイン消費量up
class CostUp :public Build
{
public:
	~CostUp(){}
	float AddHeavyCost() const;
	float AddLightCost() const;

};

//被ダメージアップ
class ReceivedUp : public Build
{
public:
	~ReceivedUp(){}
	float degDefense()const;
};


//重攻撃時コイン消費量up+弾速低下+サイズup
class VeryCostUp :public Build
{
public:
	~VeryCostUp(){}
	float AddVeryCost() const;
	VECTOR2 HeavyProjectileSpeed() const;
	VECTOR2 HeavyProjectileScale() const;
	float HeavyProjectileRadius() const;
	//float DegProjectileLife()const;
};

//攻撃速度上昇+攻撃力減少
class MotionRapid :public Build
{
public:
	~MotionRapid(){}
	int degMotionFrameSpeed()const;
	float degLightCost()const;
	float degHeavyCost()const;
	
};

//重力低下+被ダメ増加
class moonGravity : public Build
{
public:
	~moonGravity(){}
	VECTOR2 degGravity() const;
	float degDefense() const;
};

//コインの獲得枚数Up
class ExtraReward : public Build
{
public:
	~ExtraReward() {}
	float AddReward()const;
	float DegMoveSpeed()const;
};

//移動速度アップ＋被ダメ少アップ
class RapidSpeed : public Build
{
public:
	~RapidSpeed(){}
	float AddMoveSpeed()const;
	float degDefense() const;

};

//軽攻撃変化＋寿命大幅down
class ChangeLightAtk : public Build
{
public:
	~ChangeLightAtk(){}
	VECTOR2 LightProjectileSpeed() const;
	VECTOR2 LightProjectileScale() const;
	float LightProjectileLife()const;

};