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

	//中身
	virtual int AddMaxJump() const { return 0; }
	virtual float AddCost() const { return 0.0f; }
	virtual float AddVeryCost() const { return 0.0f; }
	virtual VECTOR2 DegProjectileSpeed() const { return { 0.0f,0.0f }; }
	virtual VECTOR2 AddProjectileScale() const { return { 0.0f,0.0f }; }
	virtual float AddProjectileRadius() const { return  0.0f; }
	virtual float DegProjectileLife()const { return 0.0f; }
	virtual int degMotionFrameSpeed()const { return 0.0f; }
	virtual VECTOR2 degGravity() const { return { 0.0f,0.0f }; }
	virtual float degDefense() const { return 0.0f; }


};


//ジャンプ追加
class ExtraJump : public Build
{
public:
	~ExtraJump() {}
	int AddMaxJump() const;
};

//重攻撃時コイン消費量up
class CostUp :public Build
{
public:
	~CostUp(){}
	float AddCost() const;
};

//重攻撃時コイン消費量up+弾速低下+サイズup
class VeryCostUp :public Build
{
public:
	~VeryCostUp(){}
	float AddVeryCost() const;
	VECTOR2 DegProjectileSpeed() const;
	VECTOR2 AddProjectileScale() const;
	float AddProjectileRadius() const;
	//float DegProjectileLife()const;
};

//攻撃測上昇+サイズDown
class MotionRapid :public Build
{
public:
	~MotionRapid(){}
	int degMotionFrameSpeed()const;
	
};

//重力低下+被ダメ増加
class moonGravity : public Build
{
public:
	~moonGravity(){}
	VECTOR2 degGravity() const;
	float degDefense() const;
};