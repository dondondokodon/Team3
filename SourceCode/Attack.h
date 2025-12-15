#pragma once


class Attack
{
private:
	Attack(){}
	~Attack(){}

public:
	//ダメージ計算
	int calcDamage(int baseDamage, int coin) { return baseDamage * coin; }
};