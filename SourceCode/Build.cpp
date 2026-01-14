#include "Build.h"

//フラグ
bool Build::extraJump = false;
bool Build::extraCost = false;
bool Build::extraVeryCost = false;
bool Build::extraMotionRapid = false;
bool Build::extraMoonGravity = false;


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

//重力を6分の1に
VECTOR2 moonGravity::degGravity() const
{
	return { 0.0f,0.6f };	//1.3 * 0.6
}

//防御力を下げる
float moonGravity::degDefense() const
{
	return -30.0f;	//30%down
}
