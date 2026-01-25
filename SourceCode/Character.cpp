#include "Character.h"

int Character::calcProtectingDamage(int damage)
{
	int calcDef = damage * def;
	int calcDamage = damage - calcDef;
	if (calcDamage)	return calcDamage;
	return 0;
}
VECTOR2 Character::calcFallEnergy(VECTOR2 energy)
{
	return { fallEnergy.x * energy.x, fallEnergy.y * energy.y };
}


void Character::init()
{
	OBJ2D::init();
	atk             = 0;	//攻撃力
	invincibleTimer = 1.0f;	//無敵時間 0以上無敵状態
	def             = 0;	//防御力	敵も自機も初期値は０
	fallEnergy      = { 0.0f,1.3f };	//重力をいじりたくなった
	mellePos        = { 0,0 };	//近接攻撃用
	acceleration    =0;	//スピードの上昇量
	melleRadius     = 0;
	isGround        = false;		//地面判定
}


void Character::HitWallUpdate()
{
	hitWall.dirX = direction.x;

	float halfW = pivot.x * fabsf(scale.x);
	float halfH = pivot.y * fabsf(scale.y);

	hitWall.x = pos.x + halfW * direction.x;
	hitWall.bottom = pos.y + halfH;
	hitWall.top = pos.y - halfH;


}