#include "Player.h"
#include<memory>
#include "../GameLib/game_lib.h"
#include "common.h"

Player::Player():MAX_SPEED({20,30})
{
	pos = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
	scale = { 1,1 };
	texPos = { 0,0 };
	texSize = { 256,256 };
	pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
	color = { 1,1,1,1 };
	speed = { 0,0 };
	offset = { 0,0 };
	angle = 0;
	spr = nullptr;
	act = 0;
	timer = 0;
	anime = 0;
	animeTimer = 0;
	anime_state = 0;
	radius = texSize.x * 0.5f;
	atk = 0;
	gold = 0;
	returnGold = 0;
}

void Player::init()
{
	pos = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
	scale = { 1,1 };
	texPos = { 0,0 };
	texSize = { 256,256 };
	pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
	color = { 1,1,1,1 };
	speed = { 0,0 };
	offset = { 0,0 };
	angle = 0;
	if(!spr)
	spr = std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load(L"./Data/Images/0_sp.png"));
	act = 0;
	timer = 0;
	anime = 0;
	animeTimer = 0;
	anime_state = 0;
	radius = texSize.x * 0.5f;
	atk = 0;
	gold = 0;
	returnGold = 0;
}

void Player::deinit()
{

}

void Player::update()
{
	//重力と地面判定
	gravity(this);
	if (pos.y > 800)
	{
		pos.y = 800;
		speed.y = 0;
		isGround = true;
		jumpCount = 2;
	}

	/*static int num = 0;
	if (num % 2 == 0)
	{
		if (animeUpdate(0, 6, 8, false))
		{
			anime_state = 0;
			num++;
		}
	}
	else
	{
		if (animeUpdate(1, 5, 8, false))
		{
			anime_state = 0;
			num++;
		}
	}*/

	state();
}

void Player::state()
{
	switch (act)
	{

	}
}

void Player::inputMove()
{
	//キー入力で加速
	if (STATE(0) & PAD_LEFT)
	{
		speed.x -= 1;
	}
	if (STATE(0) & PAD_RIGHT)
	{
		speed.x += 1;
	}

	//最高速度に収める
	if (speed.x > MAX_SPEED.x)
		speed.x = MAX_SPEED.x;
	else if (speed.x < -MAX_SPEED.x)
		speed.x = -MAX_SPEED.x;

}
void Player::inputJump()
{
	//キー入力でジャンプ
	if (STATE(0) & PAD_TRG1)
	{
		speed -= MAX_SPEED;
	}
}

void Player::betCoin(int Gold,float atkMultiple, float goldMultiple)
{
	atk = Gold * atkMultiple;
	returnGold = Gold * goldMultiple;
	if (returnGold)		returnGold = 1;	//帰ってくる数が0の時最低保証で1にする
}