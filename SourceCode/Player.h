#pragma once
#include "Character.h"
#include "Coin.h"

class Player :
    public Character
{
public:
	Player();
	void init();
	void deinit();
	void update();
	void betCoin(int gold,float atkMultiple,float goldMultiple);		//UŒ‚‚·‚é‚Æ‚«‚É‚©‚¯‚é‚¨‹à ˆø”@Š|‚¯‹à@UŒ‚—Í”{—¦@‹A‚Á‚Ä‚­‚é‚¨‹à”{—¦
	bool isAlive() { return (gold <= 0 && returnGold <= 0); }
	void inputMove();
	void inputJump();
	void state();
private:
	int gold       = Coin::GetCoinNum(); //‚¨‹à
	int returnGold = 0; //UŒ‚‚ğ“–‚Ä‚½‚É‹A‚Á‚Ä‚­‚é‚¨‹à
	const VECTOR2 MAX_SPEED;	//Å‚‘¬“x
	bool isGround = false;
	int jumpCount = 2;
};

