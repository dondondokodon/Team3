#pragma once
#include "OBJ2D.h"
class Character :
    public OBJ2D
{
public:
	virtual ~Character() {}
	virtual void init()    = 0;
	virtual void deinit()  = 0;
	virtual void update(){}	//エネミーで違うUpdate使うからフック
	virtual bool isDeath() = 0;
	void ScaleReverse()		//速度に応じてスケール反転
	{
		if (!speed.x)		return;	//スピードがなければ即リターン

		//画像が左向きの時　右向きの時はscaleの符号を反転
		if (speed.x > 0)
		{
			if (scale.x > 0)		scale.x = -scale.x;
		}
		else
		{
			if (scale.x < 0)		scale.x = -scale.x;
		}
	}
	int getATK() { return atk; }
	float getInvincibleTimer() { return invincibleTimer; }
	float getMelleRadius() { return radius; }
	VECTOR2 getMellePos() { return mellePos; }
	void setInvincibleTimer(int num) { invincibleTimer = num; }
	void invincibleTimerUpdate() { if (invincibleTimer > 0.0f)	invincibleTimer -= 0.1f; }

	void setDef(float def) { this->def = def * 0.01f; }	//100分率に変換
	void addDef(float def) { this->def += def * 0.01f; }
	void degDef(float def) { this->def -= def * 0.01f; }
	float getDef()const { return def; }
	int calcProtectingDamage(int damage);

	void setFallEnergy(VECTOR2 energy) { fallEnergy = energy; }
	VECTOR2 calcFallEnergy(VECTOR2 energy);
protected:
	int atk              = 0;	//攻撃力
	float invincibleTimer=1.0f;	//無敵時間 0以上無敵状態
	float def			 = 0;	//防御力	敵も自機も初期値は０
	VECTOR2 fallEnergy = { 0.0f,1.3f };	//重力をいじりたくなった

	VECTOR2 mellePos = { 0,0 };	//近接攻撃用
	float   melleRadius = 0;
	bool isGround = false;		//地面判定
};

