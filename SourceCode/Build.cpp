#include "Build.h"

//フラグ
bool Build::extraJump = false;
bool Build::extraCost = false;


//ジャンプ追加
int ExtraJump::AddMaxJump() const
{
	return 1; 	//２＋１
}

//重攻撃時コストup
float CostUp::AddCost() const
{
	return 0.2f;	//0.1+0.2
}

//重攻撃時コスト超up
float VeryCostUp::AddCost() const
{
	return 0.4f;	//0.1+0.4
}

//弾速減
VECTOR2 VeryCostUp::DegProjectileSpeed() const
{
	return { 8,8 };	//10-8
}

//スケール増
VECTOR2 VeryCostUp::AddProjectileSize() const
{
	return { 2,2 };	
}

//当たり判定拡大
float VeryCostUp::AddProjectileRadius() const
{
	return 20;	//仮置き
}