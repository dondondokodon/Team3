#include "Player.h"
#include "../GameLib/game_lib.h"
#include "common.h"
#include "ProjectileStraight.h"


Player::Player():MAX_SPEED({15,25})
{
	pos = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
	scale = { 1,1 };
	texPos = { 0,0 };
	texSize = { 320,320 };
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
	direction = { 1,1 };

}

void Player::init()
{
	pos = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
	scale = { 1,1 };
	texPos = { 0,0 };
	texSize = { 320,320 };
	pivot = { texSize.x * 0.5f,texSize.y};
	color = { 1,1,1,1 };
	speed = { 0,0 };
	offset = { 0,0 };
	angle = 0;
	if(!spr)
	spr = std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load(L"./Data/Images/tadasii_sprite.png"));
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
	direction = { 1,1 };

	//3段ジャンプ
	if (Build::extraJump)
		addEffect(std::make_unique<ExtraJump>());
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
	if (pos.y > GROUND_Y)
	{
		pos.y = GROUND_Y;
		speed.y = 0;
		isGround = true;
		//jumpCount = 2;
		ResetJumpCount();
	}

	//摩擦
	friction(this);

	//GameLib::primitive::circle(pos.x,pos.y, 20, 1, 1);


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
	{		
		animeUpdate(2, 5, 6, true);
		
		inputMove();
		inputJump();

		//歩き
		if (fabsf(speed.x) > 2)
			act = WALK_INIT;

		//攻撃
		InputProjectile();
		break;
	}
	case WALK_INIT:
		anime_state = 0;
		act = WALK;

	case WALK:
		//animeUpdate();
		inputMove();
		inputJump();

		//アイドル
		if (fabsf(speed.x) < 2)
			act = IDLE_INIT;

		//攻撃
		InputProjectile();
		break;

	case JUMP_INIT:
		anime_state = 0;
		act = JUMP;

	case JUMP:
		//animeUpdate();
		inputMove();
		inputJump();
		//落下
		if (speed.y > 0)
			act = FALL_INIT;

		//攻撃
		InputProjectile();
		break;

	case FALL_INIT:
		anime_state = 0;
		act = FALL;

	case FALL:
		//animeUpdate();
		inputMove();
		inputJump();

		//アイドル
		if (GROUND_Y <= pos.y)
			act = IDLE;

		//攻撃
		InputProjectile();
		break;
	case ATTACK1_INIT:
		anime_state = 0;
		lightAttack = true;
		act = ATTACK1;

	case ATTACK1:
	{
		//lightAttack = false;
		static int i = 0;
		if (i == 0)
		{
			if (animeUpdate(0, 8, 6, false))
			{
				anime_state = 0;
				i++;
			}
		}
		else
		{
			if (animeUpdate(1, 7, 6, false))
			{
				i = 0;
				act = IDLE_INIT;
			}
		}		
		break;
	}

	}
}

void Player::inputMove()
{
	//scale.x *= direction.x;
	//キー入力で加速
	if (STATE(0) & PAD_LEFT)
	{
		speed.x -= 2;
		scale.x = -1;
		direction.x = -1;
	}
	if (STATE(0) & PAD_RIGHT)
	{
		speed.x += 2;
		scale.x = 1;
		direction.x = 1;
	}

	//速度でスケールやるver
	/*if (fabsf(speed.x) > 0.5f)
	{
		scale.x = (speed.x > 0) ? 1.0f : -1.0f;
	}*/

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
		speed.y = -MAX_SPEED.y;
		jumpCount--;
		isGround = false;
		act = JUMP_INIT;
	}
}

void Player::betCoin(int Gold,float atkMultiple, float goldMultiple)
{
	atk = Gold * atkMultiple;
	returnGold = Gold * goldMultiple;
	if (!returnGold)		returnGold = 1;	//帰ってくる数が0の時最低保証で1にする
}


void Player::InputProjectile()
{
	if (TRG(0) & PAD_TRG4)
	{
		act = ATTACK1_INIT;
		//b->init();

	}
}

///////////////////////////////////////////////////////////////
/*-------------------------ビルド関連--------------------------*/
int Player::GetMaxJump()
{
	int bouns = 0;
	for (auto& e : builds) bouns += e->AddMaxJump();
	return baseMaxJump + bouns;
}
