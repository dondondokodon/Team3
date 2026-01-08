#include "Build.h"

//フラグ
bool Build::extraJump = false;
bool Build::extraCost = false;
bool Build::extraVeryCost = false;
bool Build::extraMotionRapid = false;


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
float VeryCostUp::AddVeryCost() const
{
	return 0.4f;	//0.1+0.4
}

//弾速減
VECTOR2 VeryCostUp::DegProjectileSpeed() const
{
	return { 5,5 };	//10-8
}

//スケール増
VECTOR2 VeryCostUp::AddProjectileScale() const
{
	return { 18,18 };	
}

//当たり判定拡大
float VeryCostUp::AddProjectileRadius() const
{
	return  120;	//仮置き
}

//モーション短縮
int MotionRapid::degMotionFrameSpeed()const
{
	return 2;	//frame-2
}
