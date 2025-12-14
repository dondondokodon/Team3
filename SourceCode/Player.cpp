#include "Player.h"
#include<memory>
#include "../GameLib/game_lib.h"
#include "common.h"



Player::Player():MAX_SPEED({15,25})
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
	isGround = false;
	jumpCount = 0;

}

void Player::init()
{
	pos = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
	scale = { 1,1 };
	texPos = { 0,0 };
	texSize = { 256,256 };
	pivot = { texSize.x * 0.5f,texSize.y};
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
	isGround = false;
	jumpCount = 0;

}

void Player::deinit()
{

}

void Player::update()
{
	//状態遷移
	state();

	//位置に速度足す
	pos += speed;

	//重力と地面判定
	if(!isGround)
	gravity(this);
	if (pos.y > 700)
	{
		pos.y = 700;
		speed.y = 0;
		isGround = true;
		jumpCount = 2;
	}

	//摩擦
	friction(this);
	setBlendMode(Blender::BS_ALPHA);
	debug::setString("SPEEDX:%f", speed.x);
	debug::setString("SPEEDY:%f", speed.y);
	debug::setString("jumpCount:%d", jumpCount);
	debug::setString("act:%d", act);
	debug::setString("isGround:%d", isGround);
	

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
		if (animeUpdate(1, 5 , 8, false))
		{
			anime_state = 0;
			num++;
		}
	}*/
}

void Player::state()
{
	switch (act)
	{
	case IDLE_INIT:
		anime_state = 0;
		act = IDLE;

	case IDLE:
		//animeUpdate();
		inputMove();
		inputJump();

		if (speed.y < 0)
			act = JUMP_INIT;
		else if (fabsf(speed.x) > 2)
			act = WALK_INIT;
		break;
	case WALK_INIT:
		anime_state = 0;
		act = WALK;

	case WALK:
		//animeUpdate();
		inputMove();
		inputJump();

		if (speed.y < 0)
			act = JUMP_INIT;
		else if (fabsf(speed.x) < 2)
			act = IDLE_INIT;
		break;

	case JUMP_INIT:
		anime_state = 0;
		act = JUMP;

	case JUMP:
		//animeUpdate();
		inputMove();
		inputJump();

		//いったんここまで
	}
}

void Player::inputMove()
{
	//キー入力で加速
	if (STATE(0) & PAD_LEFT)
	{
		speed.x -= 2;
	}
	if (STATE(0) & PAD_RIGHT)
	{
		speed.x += 2;
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
	if (TRG(0) & PAD_TRG1&&jumpCount>0)
	{
		speed.y -= MAX_SPEED.y;
		jumpCount--;
		isGround = false;
	}
}

void Player::betCoin(int Gold,float atkMultiple, float goldMultiple)
{
	atk = Gold * atkMultiple;
	returnGold = Gold * goldMultiple;
	if (!returnGold)		returnGold = 1;	//帰ってくる数が0の時最低保証で1にする
}