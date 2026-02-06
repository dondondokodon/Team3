#include "Player.h"
#include "../GameLib/game_lib.h"
#include "common.h"
#include "ProjectileStraight.h"
#include "Ghost.h"
#include "EffektManager.h"
#include"ImageManager.h"
#include "HitBox.h"
#include "textUI_Manager.h"
#include "audio.h"
#include "PlayerEffect.h"
#include "imgui.h"

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
	pos     = { SCREEN_W * 0.2f,SCREEN_H * 0.1f };
	//pos     = { SCREEN_W * 0.5f,0.0f };
	scale   = { 1,1 };
	texPos  = { 0,0 };
	texSize = { 320,320 };
	pivot   = { texSize.x * 0.5f,texSize.y * 0.5f };
	color   = { 1,1,1,1 };
	speed   = { 0,0 };
	offset  = { 0,50 * scale.y };
	angle   = 0;
	
	spr             = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Player);
	act             = FALL_INIT;
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
	isDeathOn       = false;
	dodgeReserve    = false;
	baseMaxJump     = 2;
	jumpCount       = 0;
	direction       = { 1,0 };
	invincibleTimer = 1.0f;
	attack_frame    = 5;
	animeCount      = 0;

	playerBullet         = ImageManager::Instance().getSprite(ImageManager::SpriteNum::PlayerBullet);
	lightBetRatio        = 0.01f;
	heavyBetRatio        = 0.10f;
	lightSpeed           = { 15,15 };
	lightScale           = { 3,3 };
	lightLifeLimit       = 0.7f;
	lightTexSize         = { 6,6 };
	lightRadius          = 3.0f;
	drawPos              = { 0,0 };
	drawPosFlag          = false;
	heavySpeed           = { 10,10 };
	heavyScale           = { 8.0,8.0 };
	heavyLifeLimit       = 0.5f;
	heavyTexSize         = { 6,6 };
	heavyRadius          = 3.0f;
	beforeLayer          = nullptr;
	oldFallEnemgyY       = 0.0f;
	fallEnergy           = { 0.0f,1.3f };

	targetHitWall.x      = -1000.0f;
	targetHitWall.top    = 0.0f;
	targetHitWall.bottom = 0.0f;
	targetHitWall.dirX   = 0.0f;

	setFallEnergy(VECTOR2{ 0.0f,1.3f });
	setDef(0);

	maxSpeed = 7;
	Coin::lightRatio = 2.5f;
	Coin::heavyRatio = 1.5f;

	//texSize = { 320,320 };

	//	//攻撃コイン消費アップ効果
	//if (PlayerEffect::attackCoinUp)
	//{
	//	//lightBetRatio *= 2;
	//	//heavyBetRatio *= 2;
	//	PlayerEffect::attackCoinUp = false;

	//}

	Build::extraJump = true;
	Build::extraCost = true;
	Build::extraVeryCost = true;
	Build::extraMotionRapid = true;
	//Build::extraMoonGravity = true;
	//Build::defenseDown = true;
	Build::extraReward = true;
	Build::extraSpeed = true;
	Build::extraBullet = true;
	Build::lightChange = true;

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


	//イベントでの防御ダウン
	if (Build::defenseDown)
		addEffect(std::make_unique<ReceivedUp>());

	//返ってくるコインの枚数アップ
	if (Build::extraReward)
		addEffect(std::make_unique<ExtraReward>());
	
	//移動速度アップ
	if (Build::extraSpeed)
		addEffect(std::make_unique<RapidSpeed>());
	
	//K攻撃変化
	if (Build::lightChange)
		addEffect(std::make_unique<ChangeLightAtk>());
	

	setCost();
	setHeavyVeryCost();
	setAttackFrame();
	setGravity();
	setDEF();
	setRewardRatio();
	setLightAtk();

	MAX_SPEED.x = maxSpeed;


}

void Player::deinit()
{
	//ビルドを消す
	clearEffect();
	isDeathOn = false;
	//PlayerTargetをヌルにする いったんやめる
	//Player_HitBox::Instance().setTarget(nullptr);
}

void Player::update()
{
	//効果があったら
	//if (PlayerEffect::defDef)
	//{
	//	def = -0.3f;
	//	PlayerEffect::defDef = false;
	//}

	//描画位置補正 状態遷移より上に置かないとサイズとかが更新されてから描画されるので上に置く
	if (drawPosFlag)
	{
		drawPos = { 0,0 };
		drawPosFlag = false;

		texSize = { 320.0f,320.0f };
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Player);
	}

	//当たり判定壁
	beforeWall = hitWall;

	
	if (Coin::GetCoinNum() <= 0&&act!=DEATH)
		act = DEATH_INIT;

	//軽攻撃
	if (lightAttack)
	{
		int useCoin = Coin::GetRatioCoin(getLightRatio());
		ProjectileStraight* b = new ProjectileStraight(&ProjectileManager::Instance(), Projectile::Faction::player, Coin::calcDamage(2, useCoin), Projectile::kinds::light, lightLifeLimit, playerBullet, lightTexSize, lightScale, lightSpeed, lightRadius);
		Coin::DegCoinNum(useCoin);
		b->Launch(getDir(), getPos());
		textUI_Manager::Instance().spawnDegText(*this, -useCoin);

	}
	lightAttack = false;

	//重攻撃
	if (heavyAttack)
	{
		int useCoin = Coin::GetRatioCoin(getHeavyRatio());
		heavyScale = (getAct() == Player::HEAVY_ATTACK2) ? VECTOR2{ 17.0f,17.0f } : VECTOR2{ 8.0f,8.0f };
		ProjectileStraight* projectile = new ProjectileStraight(&ProjectileManager::Instance(), Projectile::Faction::player, Coin::calcDamage(2.5f, useCoin), Projectile::kinds::heavy, heavyLifeLimit, playerBullet, heavyTexSize, heavyScale, heavySpeed, heavyRadius);
		Coin::DegCoinNum(useCoin);
		projectile->Launch(getDir(), getPos());
		textUI_Manager::Instance().spawnDegText(*this, -useCoin);

	}
	heavyAttack = false;

	//無敵時間更新
	invincibleTimerUpdate();

	//位置に速度足す
	pos += speed;

	//当たり判定壁更新
	HitWallUpdate();

	//CheckHitWall(targetHitWall);

	//範囲制限
	if (moveLimitLeft > pos.x -	 radius)	pos.x = moveLimitLeft  + radius;
	if (moveLimitRight < pos.x +radius)	pos.x = moveLimitRight - radius;


	//重力
	if(!isGround)
	gravity(this, fallEnergy);
	debug::setString("GRAVITY_Y:%f", fallEnergy.y);

	//地面判定
	if (pos.y > GROUND_Y - pivot.y)
	{
		pos.y = GROUND_Y - pivot.y;
		speed.y = 0;
		isGround = true;
		//jumpCount = 2;
		ResetJumpCount();
	}

	//地面接地
	if (isGround)
	{
		//ジャンプ回数リセット
		ResetJumpCount();
	}

	//状態遷移
	state();

	//摩擦
	friction(this);

	//Gui
	DrawGui();

	setBlendMode(Blender::BS_ALPHA);
	//debug::setString("SPEEDX:%f", speed.x);
	//debug::setString("SPEEDY:%f", speed.y);
	//debug::setString("positionX:%f", pos.x);
	//debug::setString("positionY:%f", pos.y);
	//debug::setString("jumpCount:%d", jumpCount);
	//debug::setString("act:%d", act);
	//debug::setString("isGround:%d", isGround);
	//debug::setString("buildCount:%d", builds.size());
	//debug::setString("heavyCost:%d", getHeavyRatio());

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
		inputDodge();

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
		inputDodge();

		//アイドル
		//if (GROUND_Y - pivot.y <= pos.y)
		if(isGround)
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
		anime_state    = 0;
		attack2Reserve = false;
		dodgeReserve   = false;
		oldFallEnemgyY = fallEnergy.y;
		fallEnergy.y   =fallEnergy.y*0.5f; //重攻撃中は落下しない
		speed.y        = 0.0f;
		spr            = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Player_ATTACK_Effect);
		texSize        = { 512.0f,512.0f };
		drawPos        = { drawPosOffet.x * direction.x,drawPosOffet.y };
		act            = ATTACK1;

	case ATTACK1:
	{
		InputProjectile();	//ここでattack2Reserveを更新してる
		inputDodge();
		//lightAttack = false;
		if (animeUpdate(0, 11, attack_frame, false))
		{
			fallEnergy.y = oldFallEnemgyY; //元に戻す
			drawPosFlag = true;
			act = IDLE_INIT;
		}
		if (animeTimer == 3* attack_frame)	lightAttack = true;	//４コマ目に射撃
		
		
		//連撃
		if (anime >= 7)
		{
			if(attack2Reserve)
			{
				act = ATTACK2_INIT;
			}
			if(dodgeReserve)
			{
				fallEnergy.y = oldFallEnemgyY; //元に戻す
				drawPosFlag = true;
				act = DODGE_INIT;
			}
		}


		break;
	}

	case ATTACK2_INIT:
		anime_state = 0;
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Player_ATTACK_Effect);
		texSize = { 512.0f,512.0f };
		drawPos = { drawPosOffet.x * direction.x,drawPosOffet.y };
		dodgeReserve = false;
		act = ATTACK2;

	case ATTACK2:
		inputDodge();
		if (animeUpdate(1, 11, attack_frame, false))
		{
			fallEnergy.y = oldFallEnemgyY; //元に戻す
			drawPosFlag = true;
			act = IDLE_INIT;
		}
		if (animeTimer == 3 * attack_frame)			lightAttack = true;	//４コマ目に射撃
		
		if (anime >= 6&&dodgeReserve)
		{
			fallEnergy.y = oldFallEnemgyY; //元に戻す
			drawPosFlag = true;
			act = DODGE_INIT;
		}
		break;

	case HEAVY_ATTACK1_INIT:
		anime_state = 0;
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Player_ATTACK_Effect);
		texSize = { 512.0f,512.0f };
		drawPos = { drawPosOffet.x * direction.x,drawPosOffet.y };
		animeCount = 0;
		dodgeReserve = false;
		oldFallEnemgyY = fallEnergy.y;
		fallEnergy.y = 0.0f; //重攻撃中は落下しない
		speed.y = 0.0f;
		music::play(bigAttack);
		act = HEAVY_ATTACK1;

	case HEAVY_ATTACK1:
		inputDodge();
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
			
			if (anime >= 10 )
			{
				fallEnergy.y = oldFallEnemgyY; //元に戻す
				if (dodgeReserve)
				{
					drawPosFlag = true;
					fallEnergy.y = oldFallEnemgyY; //元に戻す
					act = DODGE_INIT;
				}
			}
			break;
		case 2:
			if (animeUpdate(4, 1, attack_frame, false))
			{
				drawPosFlag = true;
				fallEnergy.y = oldFallEnemgyY; //元に戻す
				act = IDLE_INIT;
			}

			break;
		}

		
		break;

	case HEAVY_ATTACK2_INIT:
		anime_state = 0;
		animeCount = 0;
		dodgeReserve = false;
		drawPos = { drawPosOffet.x*direction.x,drawPosOffet.y };
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Player_ATTACK_Effect);
		texSize = { 512.0f,512.0f };
		music::play(bigAttack);
		oldFallEnemgyY = fallEnergy.y;
		fallEnergy.y = 0.0f; //重攻撃中は落下しない
		speed.y = 0.0f;
		act = HEAVY_ATTACK2;

	case HEAVY_ATTACK2:
		inputDodge();
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
			
			if (anime >= 10 )
			{
				fallEnergy.y = oldFallEnemgyY; //元に戻す
				if (dodgeReserve)
				{
					drawPosFlag = true;
					fallEnergy.y = oldFallEnemgyY; //元に戻す
					act = DODGE_INIT;
				}
			}

			break;
		case 2:
			if (animeUpdate(7, 1, attack_frame, false))
			{
				drawPosFlag = true;
				act = IDLE_INIT;
			}
		     break;
		}
		break;

	case DODGE_INIT:
	{
		anime_state = 0;
		int num = Coin::GetCoinNum() * 0.01f;
		Coin::DegCoinNum(num); //回避でコイン消費
		textUI_Manager::Instance().spawnDegText(*this, -num);
		music::play(P_doge);
		act = DODGE;
	}
	case DODGE:
		if (animeUpdate(7, 10, 5, false))
		{
			act = IDLE_INIT;
		}

		//4こまめから８こまめいないまでの時に後ろ方向に速度を入れる
		if (animeTimer >= 1 * 5 + 1 && animeTimer < 8 * 5 + 1)
		{
			invincibleTimer = 1.5f;	//無敵時間
			speed.x = 5.0f * -direction.x;

			if(animeTimer%3==0)		//残像エフェクト
			EffektManager::Instance().Register(new Ghost(*this));
		}
		break;

	case DEATH_INIT:
		anime_state = 0;
		drawPos = { 0,0 };
		drawPosFlag = false;
		texSize = { 320.0f,320.0f };
		speed = { 0.0f,0.0f };
		fallEnergy = { 0.0f,1.3f };	//重力戻す
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Player);
		act = DEATH;

	case DEATH:
		if (animeUpdate(8, 20, 6, false))
		{
			isDeathOn = true;
		}
		break;
	}
}

void Player::CheckHitWall(const HitWall& wall)
{
	//横方向の壁との衝突
	//debug::setString("wall.x:%f dirX:%f top:%f bottom:%f",
	//	wall.x, wall.dirX, wall.top, wall.bottom);

	////高さがあっているか
	////if (beforeWall.top<wall.bottom || beforeWall.bottom>wall.top)
	//if (beforeWall.bottom < wall.top || beforeWall.top > wall.bottom)
	//	return;

	//float dPrev = (beforeWall.x - wall.x) * wall.dirX;
	//float dNow = (hitWall.x - wall.x) * wall.dirX;
	//debug::setString("dPrev:%f dNow:%f", dPrev, dNow);
	//debug::setString("pos.x:%f hitWall.x:%f wall.x:%f",
	//	pos.x, hitWall.x, wall.x);



	//if (dPrev > 0 && dNow <= 0)
	//{
	//	//pos.x -= dNow * wall.dirX;
	//	//pos.x -= 20;
	//	/*float halfW = pivot.x * scale.x;
	//	pos.x = wall.x + halfW * wall.dirX;*/

	//	float halfW = pivot.x * fabsf(scale.x);

	//	// 壁の手前に押し戻す
	//	pos.x = wall.x - halfW * wall.dirX;

	//	speed.x = 0;
	//}

	// 床（下方向）との衝突
	if (beforeWall.bottom <= wall.top && hitWall.bottom >= wall.top && speed.y > 0) {
		// 床の上にピッタリ合わせる
		pos.y = wall.top - (hitWall.bottom - pos.y);
		speed.y = 0;
		isGround = true;
		// 必要なら着地時の処理（例：ResetJumpCount()など）
	}

	// 天井（上方向）との衝突
	if (beforeWall.top >= wall.bottom && hitWall.top <= wall.bottom && speed.y < 0) {
		// 天井の下にピッタリ合わせる
		pos.y = wall.bottom + (pos.y - hitWall.top);
		speed.y = 0;
	}
}

void Player::cameraRender(CAMERA& camera)
{
	VECTOR2 dPos = pos;
	dPos+= drawPos;
	
	sprite_render(
		spr.get(),
		dPos.x - camera.getDrawPos().x,
		dPos.y - camera.getDrawPos().y,
		scale.x, scale.y,
		texPos.x, texPos.y,
		texSize.x, texSize.y,
		pivot.x, pivot.y,
		angle,
		color.x, color.y, color.z, color.w
	);

	//壁判定
	//primitive::line(hitWall.x-camera.getPos().x, hitWall.top - camera.getPos().y, hitWall.x - camera.getPos().x, hitWall.bottom - camera.getPos().y);
	//primitive::line(beforeWall.x-camera.getPos().x, beforeWall.top - camera.getPos().y, beforeWall.x - camera.getPos().x, beforeWall.bottom - camera.getPos().y);
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
	if ((TRG(0) & PAD_TRG1||TRG(0)& PAD_UP )&& jumpCount>0)
	{
		isGround ? music::play(P_jumpGround) : music::play(P_jump, false);
		speed.y = -MAX_SPEED.y;
		jumpCount--;
		isGround = false;
		act = JUMP_INIT;
	}
}

void Player::inputDodge()
{
	//キー入力で回避
	if (TRG(0) & PAD_TRG5||TRG(0)&PAD_TRG7)
	{
		if (act == ATTACK1 || act == ATTACK2 || act == HEAVY_ATTACK1 || act == HEAVY_ATTACK2)
		{
			dodgeReserve = true;
			return;
		}

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

	//ATTACK1中に重攻撃でないようにした
	if (act == ATTACK1)	return;

	//Lで重攻撃
	if (TRG(0) & PAD_TRG6)
	{
		if (Build::extraVeryCost)
			act = HEAVY_ATTACK2_INIT;
		else
			act = HEAVY_ATTACK1_INIT;
	}

	//Jで重攻撃（重いバージョン　仮）
	/*if (TRG(0) & PAD_TRG6)
	{
		if (Build::extraVeryCost)
			act = HEAVY_ATTACK2_INIT;
		else
			act = HEAVY_ATTACK1_INIT;
	}*/
}

///////////////////////////////////////////////////////////////
/*-------------------------ビルド関連--------------------------*/
int Player::GetMaxJump()
{
	int bounce = 0;
	for (auto& e : builds) bounce += e->AddMaxJump();
	return baseMaxJump + bounce;
}

void Player::setCost()
{
	float addCost = 0.0f;
	float addLight = 0.0f;
	for (auto& e : builds) 
	{ 
		addCost += e->AddHeavyCost();
		addLight += e->AddLightCost();
		addLight -= e->degLightCost();
		addCost -= e->degHeavyCost();
	}
	addHeavyRatio(addCost);
	addLightRatio(addLight);
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
		speed += e->HeavyProjectileSpeed();
		scale += e->HeavyProjectileScale();
		radius += e->HeavyProjectileRadius();
	}
	addHeavyRatio(addCost);
	degHeavyBulletSpeed(speed);
	addHeavyBulletScale(scale);
	addHeavyBulletRadius(radius);
}

void Player::setAttackFrame()
{
	int frame = 0;
	for (auto& e : builds) 
	{
		frame += e->degMotionFrameSpeed(); 
		frame += -e->addMotionFrameSpeed();
	}
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

void Player::setRewardRatio()
{
	float addRatio = 0;
	float degSpeed = 0;
	for (auto& e : builds) 
	{
		addRatio += e->AddReward(); 
		degSpeed += e->DegMoveSpeed();
		degSpeed += e->AddMoveSpeed();
	}

	setSpeedX(-degSpeed);
	Coin::lightRatio += addRatio;
	Coin::heavyRatio += addRatio;
}

void Player::setLightAtk()
{
	VECTOR2 bulletSpeed = { 0,0 };
	VECTOR2 bulletSize = { 0,0 };
	float life = 0;
	for (auto& e : builds)
	{
		bulletSpeed += e->LightProjectileSpeed();
		bulletSize -= e->LightProjectileScale();
		life -= e->LightProjectileLife();
	}

	setLightAtkSpeed(bulletSpeed);
	setLightAtkSize(bulletSize);
	setLightLife(life);
}

//Gui描画
void Player::DrawGui()
{
	ImGui::InputFloat2("pos", &pos.x);
}
