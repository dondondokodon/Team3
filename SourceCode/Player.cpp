#include "Player.h"
#include "../GameLib/game_lib.h"
#include "common.h"
#include "ProjectileStraight.h"
#include "Ghost.h"
#include "EffektManager.h"


Player::Player():MAX_SPEED({7,25})
{
	pos         = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
	scale       = { 1,1 };
	texPos      = { 0,0 };
	texSize     = { 320,320 };
	pivot       = { texSize.x * 0.5f,texSize.y * 0.5f };
	color       = { 1,1,1,1 };
	speed       = { 0,0 };
	offset      = { 0,0 };
	angle       = 0;
	spr         = nullptr;
	act         = 0;
	timer       = 0;
	anime       = 0;
	animeTimer  = 0;
	anime_state = 0;
	radius      = texSize.x * 0.2f * scale.x;;
	atk         = 0;
	gold        = 0;
	returnGold  = 0;
	isGround    = false;
	heavyAttack = false;
	jumpCount   = 0;
	direction   = { 1,0 };
	invincibleTimer = 1.0f;
}

void Player::init()
{
	pos			   = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
	scale		   = { 1,1 };
	texPos		   = { 0,0 };
	texSize		   = { 320,320 };
	pivot		   = { texSize.x * 0.5f,texSize.y * 0.5f};
	color		   = { 1,1,1,1 };
	speed		   = { 0,0 };
	offset		   = { 0,50*scale.y };
	angle		   = 0;
	if(!spr)
	spr            = std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load(L"./Data/Images/ziki_motto_tadasii_sprite.png"));
	act            = 0;
	timer          = 0;
	anime          = 0;
	animeTimer     = 0;
	anime_state    = 0;
	radius         = texSize.x * 0.2f*scale.x;
	atk            = 0;
	gold           = 0;
	returnGold     = 0;
	attack2Reserve = false;
	isGround       = false;
	heavyAttack    = false;
	baseMaxJump	   = 2;
	jumpCount      = 0;
	direction      = { 1,0 };
	invincibleTimer = 1.0f;

	playerBullet = std::shared_ptr<GameLib::Sprite>(sprite_load(L"./Data/Images/1213_coin6x6.png"));


	//3段ジャンプ
	if (Build::extraJump)
		addEffect(std::make_unique<ExtraJump>());

	//重攻撃コイン消費アップ
	if (Build::extraCost)
		addEffect(std::make_unique<CostUp>());

	setHeavyCost();

}

void Player::deinit()
{
	//ビルドを消す
	clearEffect();
}

void Player::update()
{
	//状態遷移
	state();

	//無敵時間更新
	invincibleTimerUpdate();

	//位置に速度足す
	pos += speed;

	//重力と地面判定
	if(!isGround)
	gravity(this);
	if (pos.y > GROUND_Y - pivot.y)
	{
		pos.y = GROUND_Y - pivot.y;
		speed.y = 0;
		isGround = true;
		//jumpCount = 2;
		ResetJumpCount();
	}

	//摩擦
	friction(this);

	//軽攻撃
	if (lightAttack)
	{
		int useCoin = Coin::GetRatioCoin(getLightRatio());
		ProjectileStraight* b = new ProjectileStraight(&ProjectileManager::Instance(), Projectile::Faction::player, Coin::calcDamage(2, useCoin), Projectile::kinds::light, 0.7f, playerBullet, VECTOR2{ 6,6 }, VECTOR2{ 3,3 }, VECTOR2{ 15,15 });
		Coin::DegCoinNum(useCoin);
		b->Launch(getDir(), getPos());
	}
	lightAttack = false;

	//重攻撃
	if (heavyAttack)
	{
		int useCoin = Coin::GetRatioCoin(getHeavyRatio());
		VECTOR2 bulletScale = (getAct() == Player::HEAVY_ATTACK2) ? VECTOR2{ 17.0f,17.0f } : VECTOR2{ 8.0f,8.0f };
		ProjectileStraight* projectile = new ProjectileStraight(&ProjectileManager::Instance(), Projectile::Faction::player, Coin::calcDamage(10, useCoin), Projectile::kinds::heavy, 0.5f, playerBullet, VECTOR2{ 6,6 }, bulletScale, VECTOR2{ 10,10 });
		Coin::DegCoinNum(useCoin);
		projectile->Launch(getDir(), getPos());
	}
	heavyAttack = false;


	setBlendMode(Blender::BS_ALPHA);
	debug::setString("SPEEDX:%f", speed.x);
	debug::setString("SPEEDY:%f", speed.y);
	debug::setString("positionX:%f", pos.x);
	debug::setString("positionY:%f", pos.y);
	debug::setString("jumpCount:%d", jumpCount);
	debug::setString("act:%d", act);
	debug::setString("isGround:%d", isGround);
	debug::setString("buildCount:%d", builds.size());
	debug::setString("heavyCost:%d", getHeavyRatio());

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
		animeUpdate(1, 5, 6, true);
		
		inputMove();
		inputJump();
		inputDodge();

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
	{
		animeUpdate(2, 10, 6, true);

		inputMove();
		inputJump();
		inputDodge();

		//アイドル
		if (fabsf(speed.x) < 2)
			act = IDLE_INIT;

		//攻撃
		InputProjectile();
		break;
	}
	case JUMP_INIT:
		anime_state = 0;
		act = JUMP;

	case JUMP:
		

		inputMove();
		inputJump();

		if (animeUpdate(3, 8, 3, false))
		{
			//落下
			if (speed.y > 0)
				act = FALL_INIT;
		}


		//攻撃
		InputProjectile();
		break;

	case FALL_INIT:
		anime_state = 0;
		act = FALL;

	case FALL:
		animeUpdate(4,11,6,false);
		inputMove();
		inputJump();

		//アイドル
		if (GROUND_Y - pivot.y <= pos.y)
			act = LANDING_INIT;

		//攻撃
		InputProjectile();
		break;

	case LANDING_INIT:
		anime_state = 0;
		act = LANDING;

	case LANDING:
		animeUpdate(5, 10, 6, false);	//モーションゆっくりやから意図的に２こ
		if(animeUpdate(5, 10, 6, false))	act=IDLE_INIT;

		break;

	case ATTACK1_INIT:
		anime_state = 0;
		attack2Reserve = false;
		act = ATTACK1;

	case ATTACK1:
	{
		InputProjectile();	//ここでattack2Reserveを更新してる
		//lightAttack = false;
		if (animeUpdate(0, 16, 5, false))		act = IDLE_INIT;
		if (animeTimer == 3*5)	lightAttack = true;	//４コマ目に射撃
		
		
		//連撃
		if (anime >= 11 && attack2Reserve)		act = ATTACK2_INIT;
		
		
		break;
	}

	case ATTACK2_INIT:
		anime_state = 0;
		act = ATTACK2;

	case ATTACK2:
		if (animeUpdate(6, 13, 5, false))	act = IDLE_INIT;
		if (animeTimer == 3 * 5)			lightAttack = true;	//４コマ目に射撃
		break;

	case HEAVY_ATTACK1_INIT:
		anime_state = 0;
		act = HEAVY_ATTACK1;

	case HEAVY_ATTACK1:
		if (animeUpdate(7, 40, 5, false))	act = IDLE_INIT;
		if (animeTimer == 20* 5+1)			heavyAttack = true; //20コマ目に射撃
		if (animeTimer == 20 * 5 + 1)	speed.x = 20 * -direction.x;
		break;

	case HEAVY_ATTACK2_INIT:
		anime_state = 0;
		act = HEAVY_ATTACK2;

	case HEAVY_ATTACK2:
		if (animeUpdate(8, 40, 5, false))	act = IDLE_INIT;
		if (animeTimer == 20 * 5 + 1)		heavyAttack = true; //20コマ目に射撃
		if (animeTimer == 20 * 5 + 1)	speed.x = 20 * -direction.x;
		break;

	case DODGE_INIT:
		anime_state = 0;
		act = DODGE;

	case DODGE:
		if (animeUpdate(9, 10, 5, false))
		{
			act = IDLE_INIT;
		}

		//4こまめから８こまめいないまでの時に後ろ方向に速度を入れる
		if (animeTimer >= 3 * 5 + 1 && animeTimer < 7 * 5 + 1)
		{
			invincibleTimer = 1.5f;		//無敵時間
			speed.x = 10.0f * -direction.x;

			if(animeTimer%3==0)		//残像エフェクト
			EffektManager::Instance().Register(new Ghost(*this));
		}
		break;
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

void Player::inputDodge()
{
	//キー入力で回避
	if (TRG(0) & PAD_TRG7)
	{
		act = DODGE_INIT;
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
	//Kで軽攻撃
	if (TRG(0) & PAD_TRG4)
	{
		if (act == ATTACK1)	attack2Reserve = true;
		
		else
		act = ATTACK1_INIT;
		//b->init();
	}

	//Lで重攻撃
	if (TRG(0) & PAD_TRG5)
	{
		act = HEAVY_ATTACK1_INIT;
	}

	//Jで重攻撃（重いバージョン　仮）
	if (TRG(0) & PAD_TRG6)
	{
		act = HEAVY_ATTACK2_INIT;
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

void Player::setHeavyCost()
{
	float addCost = 0.0f;
	for (auto& e : builds)	addCost += e->AddCost();
	addHeavyRatio(addCost);
}

