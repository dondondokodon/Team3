#include "Player.h"
#include "../GameLib/game_lib.h"
#include "common.h"
#include "ProjectileStraight.h"
#include "Ghost.h"
#include "EffektManager.h"
#include"ImageManager.h"
#include "HitBox.h"
#include "UI_Manager.h"

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
	radius      = texSize.x * 0.2f * scale.x;
	atk         = 0;
	gold        = 0;
	returnGold  = 0;
	isGround    = false;
	heavyAttack = false;
	jumpCount   = 0;
	direction   = { 1,0 };
	invincibleTimer = 1.0f;

	//ヒットボックス いったんやめる
	//Player_HitBox::Instance().setTarget(this);
}

void Player::init()
{
	pos     = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
	scale   = { 1,1 };
	texPos  = { 0,0 };
	texSize = { 320,320 };
	pivot   = { texSize.x * 0.5f,texSize.y * 0.5f };
	color   = { 1,1,1,1 };
	speed   = { 0,0 };
	offset  = { 0,50 * scale.y };
	angle   = 0;
	
	spr             = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Player);
	act             = 0;
	timer           = 0;
	anime           = 0;
	animeTimer      = 0;
	anime_state     = 0;
	radius          = texSize.x * 0.2f * scale.x;
	atk             = 0;
	gold            = 0;
	returnGold      = 0;
	attack2Reserve  = false;
	isGround        = false;
	heavyAttack     = false;
	baseMaxJump     = 2;
	jumpCount       = 0;
	direction       = { 1,0 };
	invincibleTimer = 1.0f;
	attack_frame    = 5;
	animeCount      = 0;

	playerBullet   = ImageManager::Instance().getSprite(ImageManager::SpriteNum::PlayerBullet);
	lightBetRatio  = 0.01f;
	heavyBetRatio  = 0.1f;
	lightSpeed     = { 15,15 };
	lightScale     = { 3,3 };
	lightLifeLimit = 0.7f;
	lightTexSize   = { 6,6 };
	lightRadius    = 3.0f;
	drawPos        = { 0,0 };
	drawPosFlag    = false;
	heavySpeed     = { 10,10 };
	heavyScale     = { 8.0,8.0 };
	heavyLifeLimit = 0.5f;
	heavyTexSize   = { 6,6 };
	heavyRadius    = 3.0f;

	setFallEnergy(VECTOR2{ 0.0f,1.3f });
	setDef(0);

	//texSize = { 320,320 };

	//3段ジャンプ
	if (Build::extraJump)
		addEffect(std::make_unique<ExtraJump>());

	//重攻撃コイン消費アップ
	if (Build::extraCost)
		addEffect(std::make_unique<CostUp>());

	//重攻撃コイン消費超アップ
	if (Build::extraVeryCost)
		addEffect(std::make_unique<VeryCostUp>());

	//攻撃モーション短縮
	if (Build::extraMotionRapid)
		addEffect(std::make_unique<MotionRapid>());

	//重力低下
	if (Build::extraMoonGravity)
		addEffect(std::make_unique<moonGravity>());

	setHeavyCost();
	setHeavyVeryCost();
	setAttackFrame();
	setGravity();
	setDEF();
}

void Player::deinit()
{
	//ビルドを消す
	clearEffect();

	//PlayerTargetをヌルにする いったんやめる
	//Player_HitBox::Instance().setTarget(nullptr);
}

void Player::update()
{
	//描画位置補正 状態遷移より上に置かないとサイズとかが更新されてから描画されるので上に置く
	if (drawPosFlag)
	{
		drawPos = { 0,0 };
		drawPosFlag = false;

		texSize = { 320.0f,320.0f };
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Player);
	}

	//状態遷移
	state();

	//軽攻撃
	if (lightAttack)
	{
		int useCoin = Coin::GetRatioCoin(getLightRatio());
		ProjectileStraight* b = new ProjectileStraight(&ProjectileManager::Instance(), Projectile::Faction::player, Coin::calcDamage(2, useCoin), Projectile::kinds::light, lightLifeLimit, playerBullet, lightTexSize, lightScale, lightSpeed, lightRadius);
		Coin::DegCoinNum(useCoin);
		b->Launch(getDir(), getPos());
		textUI_Manager::Instance().spawnDegText(*this);

	}
	lightAttack = false;

	//重攻撃
	if (heavyAttack)
	{
		int useCoin = Coin::GetRatioCoin(getHeavyRatio());
		heavyScale = (getAct() == Player::HEAVY_ATTACK2) ? VECTOR2{ 17.0f,17.0f } : VECTOR2{ 8.0f,8.0f };
		ProjectileStraight* projectile = new ProjectileStraight(&ProjectileManager::Instance(), Projectile::Faction::player, Coin::calcDamage(10, useCoin), Projectile::kinds::heavy, heavyLifeLimit, playerBullet, heavyTexSize, heavyScale, heavySpeed, heavyRadius);
		Coin::DegCoinNum(useCoin);
		projectile->Launch(getDir(), getPos());
		textUI_Manager::Instance().spawnDegText(*this);

	}
	heavyAttack = false;

	//無敵時間更新
	invincibleTimerUpdate();

	//位置に速度足す
	pos += speed;

	//範囲制限
	if (moveLimitLeft > pos.x -	 radius)	pos.x = moveLimitLeft  + radius;
	if (moveLimitRight < pos.x +radius)	pos.x = moveLimitRight - radius;

	//重力と地面判定
	if(!isGround)
	gravity(this, fallEnergy);
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
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Player_ATTACK_Effect);
		texSize = { 512.0f,512.0f };
		drawPos = { drawPosOffet.x * direction.x,drawPosOffet.y };
		act = ATTACK1;

	case ATTACK1:
	{
		InputProjectile();	//ここでattack2Reserveを更新してる
		//lightAttack = false;
		if (animeUpdate(0, 11, attack_frame, false))
		{
			drawPosFlag = true;
			act = IDLE_INIT;
		}
		if (animeTimer == 3* attack_frame)	lightAttack = true;	//４コマ目に射撃
		
		
		//連撃
		if (anime >= 11 && attack2Reserve)
		{
			{
				act = ATTACK2_INIT;
			}
		}
		break;
	}

	case ATTACK2_INIT:
		anime_state = 0;
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Player_ATTACK_Effect);
		texSize = { 512.0f,512.0f };
		drawPos = { drawPosOffet.x * direction.x,drawPosOffet.y };
		act = ATTACK2;

	case ATTACK2:
		if (animeUpdate(1, 11, attack_frame, false))
		{
			drawPosFlag = true;
			act = IDLE_INIT;
		}
		if (animeTimer == 3 * attack_frame)			lightAttack = true;	//４コマ目に射撃
		break;

	case HEAVY_ATTACK1_INIT:
		anime_state = 0;
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Player_ATTACK_Effect);
		texSize = { 512.0f,512.0f };
		drawPos = { drawPosOffet.x * direction.x,drawPosOffet.y };
		animeCount = 0;
		act = HEAVY_ATTACK1;

	case HEAVY_ATTACK1:
		switch (animeCount)
		{
		case 0:
			if (animeUpdate(2, 14, attack_frame, false))
			{
				anime_state = 0;
				animeCount++;
			}
			break;

		case 1:
			if (animeUpdate(3, 14, attack_frame, false))
			{
				anime_state = 0;
				animeCount++;
			}
			if (animeTimer == 5 * attack_frame + 1)			heavyAttack = true; //20コマ目に射撃
			if (animeTimer == 5 * attack_frame + 1)			speed.x = 20 * -direction.x;
			break;
		case 2:
			if (animeUpdate(4, 10, attack_frame, false))
			{
				drawPosFlag = true;
				act = IDLE_INIT;
			}
			break;
		}

		
		break;

	case HEAVY_ATTACK2_INIT:
		anime_state = 0;
		animeCount = 0;
		drawPos = { drawPosOffet.x*direction.x,drawPosOffet.y };
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Player_ATTACK_Effect);
		texSize = { 512.0f,512.0f };
		act = HEAVY_ATTACK2;

	case HEAVY_ATTACK2:
		switch (animeCount)
		{
		case 0:
			if (animeUpdate(5, 14, attack_frame, false))
			{
				anime_state = 0;
				animeCount++;
			}
			break;

		case 1:
			if (animeUpdate(6, 14, attack_frame, false))
			{
				anime_state = 0;
				animeCount++;
			}
			if (animeTimer == 5 * attack_frame + 1)			heavyAttack = true; //20コマ目に射撃
			if (animeTimer == 5 * attack_frame + 1)			speed.x = 20 * -direction.x;
			break;
		case 2:
			if (animeUpdate(7, 10, attack_frame, false))
			{
				drawPosFlag = true;
				act = IDLE_INIT;
			}
			break;
		}
		break;

	case DODGE_INIT:
		anime_state = 0;
		act = DODGE;

	case DODGE:
		if (animeUpdate(7, 10, 5, false))
		{
			act = IDLE_INIT;
		}

		//4こまめから８こまめいないまでの時に後ろ方向に速度を入れる
		if (animeTimer >= 3 * 5 + 1 && animeTimer < 7 * 5 + 1)
		{
			invincibleTimer = 1.5f;	//無敵時間
			speed.x = 10.0f * -direction.x;

			if(animeTimer%3==0)		//残像エフェクト
			EffektManager::Instance().Register(new Ghost(*this));
		}
		break;
	}
}

void Player::cameraRender(CAMERA& camera)
{
	VECTOR2 dPos = pos;
	dPos+= drawPos;
	
	sprite_render(
		spr.get(),
		dPos.x - camera.getPos().x,
		dPos.y - camera.getPos().y,
		scale.x, scale.y,
		texPos.x, texPos.y,
		texSize.x, texSize.y,
		pivot.x, pivot.y,
		angle,
		color.x, color.y, color.z, color.w
	);
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
		if (Build::extraVeryCost)
			act = HEAVY_ATTACK2_INIT;
		else
			act = HEAVY_ATTACK1_INIT;
	}

	//Jで重攻撃（重いバージョン　仮）
	if (TRG(0) & PAD_TRG6)
	{
		if (Build::extraVeryCost)
			act = HEAVY_ATTACK2_INIT;
		else
			act = HEAVY_ATTACK1_INIT;
	}
}

///////////////////////////////////////////////////////////////
/*-------------------------ビルド関連--------------------------*/
int Player::GetMaxJump()
{
	int bounce = 0;
	for (auto& e : builds) bounce += e->AddMaxJump();
	return baseMaxJump + bounce;
}

void Player::setHeavyCost()
{
	float addCost = 0.0f;
	for (auto& e : builds)	addCost += e->AddCost();
	addHeavyRatio(addCost);
}

void Player::setHeavyVeryCost()
{
	float addCost = 0.0f;
	VECTOR2 speed = { 0.0f,0.0f };
	VECTOR2 scale = { 0.0f,0.0f };
	float radius = 0.0f;
	for (auto& e : builds)
	{
		addCost += e->AddVeryCost();
		speed += e->DegProjectileSpeed();
		scale += e->AddProjectileScale();
		radius += e->AddProjectileRadius();
	}
	addHeavyRatio(addCost);
	degHeavyBulletSpeed(speed);
	addHeavyBulletScale(scale);
	addHeavyBulletRadius(radius);
}

void Player::setAttackFrame()
{
	int frame = 0;
	for (auto& e : builds)	frame += e->degMotionFrameSpeed();
	degAttackFrame(frame);

}

void Player::setGravity()
{
	VECTOR2 energy = {};
	for (auto& e : builds)	energy += e->degGravity();
	if (energy.y > 0)
		setFallEnergy(calcFallEnergy(energy));
	else
		setFallEnergy(VECTOR2{ 0.0f, 1.3f });
}

void Player::setDEF()
{
	float def = 0;
	for (auto& e : builds)	def += e->degDefense();
	setDef(def);


}
