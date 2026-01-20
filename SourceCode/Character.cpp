#include "Character.h"
//いらんかも
//今日は私の体験した怖い話を書いていこうと思います
//私が体験した怖い話はそう、去年の年末１２月３１日のある出来事から始まった。。。
//年越しに地元の寺に行こうと友達Aが言い出した。
//陽気な少年Uも賛成してた
//思ってたよりも３０分ほど早めについてしまった私たちは暇をつぶそうと当たりをうろちょろしていたらBが言い出しました
// B「この３人で集まったんやったら心すぽいかん？」
// 僕たち３人は心霊スポットに行きたいと普段から話している３人組でした。
//機会がなくてついいつも逃してしまうが行きたいと私はよく話していました

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