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

	//中身
	virtual int AddMaxJump() const { return 0; }
	virtual float AddCost() const { return 0.0f; }
	virtual VECTOR2 DegProjectileSpeed() const { return { 0.0f,0.0f }; }
	virtual VECTOR2 AddProjectileSize() const { return { 0.0f,0.0f }; }
	virtual float AddProjectileRadius() const { return 0.0f; }

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
	float AddCost() const;
	VECTOR2 DegProjectileSpeed() const;
	VECTOR2 AddProjectileSize() const;
	float AddProjectileRadius() const;
};