#include "Build.h"

//フラグ
bool Build::extraJump = false;
bool Build::extraCost = false;
bool Build::extraVeryCost = false;
bool Build::extraMotionRapid = false;
bool Build::extraMoonGravity = false;
bool Build::extraBullet = false;
bool Build::defenseDown = false;
bool Build::extraReward = false;

//ジャンプ追加
int ExtraJump::AddMaxJump() const
{
	return 1; 	//２＋１
}

//重攻撃時コストup
float CostUp::AddHeavyCost() const
{
	return 0.1f;	//0.1+0.1
}

float CostUp::AddLightCost() const
{
	return 0.005f;	//0.01+0.005
}

//重攻撃時コスト超up
float VeryCostUp::AddVeryCost() const
{
	return 0.2f;	//0.1+0.2
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
	return  50;	//仮置き
}

//モーション短縮
int MotionRapid::degMotionFrameSpeed()const
{
	return 2;	//frame-2

}
float MotionRapid::degLightCost()const
{
	return 0.0002f;
}
float MotionRapid::degHeavyCost()const
{
	return 0.02f;
}


//重力を6分の1に（イメージ）
VECTOR2 moonGravity::degGravity() const
{
	return { 0.0f,0.6f };	//1.3 * 0.6
}

//防御力を下げる
float moonGravity::degDefense() const
{
	return -10.0f;	//10%down
}

//イベント用のやつ
float ReceivedUp::degDefense() const
{
	return -10.0f;
}

//コインの返還枚数Up
float ExtraReward::AddReward() const
{
	return 0.5f; 
}

float ExtraReward::DegMoveSpeed()const
{
	return 1.5;
}
