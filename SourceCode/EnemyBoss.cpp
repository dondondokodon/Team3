#include "EnemyBoss.h"
#include "ImageManager.h"
#include "HitBox.h"
#include "ProjectileManager.h"
#include "Tail.h"

EnemyBoss::EnemyBoss() :coinReward(10000), maxSpeedX(10)
{
	hp              = 2000;
	atk             = 100;
	texSize         = { 1000.0f,700.0f };
	texPos          = { 0.0f,0.0f };
	color           = { 1.0f,1.0f,1.0f,1.0f };
	scale           = { 1.0f,1.0f };
	pivot           = { texSize.x * 0.5f,texSize.y * 0.5f };
	speed           = { 0,0 };
	offset          = { 0,0 };
	act             = IDLE_INIT;
	timer           = 0;
	anime           = 0;
	animeTimer      = 0;
	anime_state     = 0;
	radius          = texSize.y * 0.5f;
	spr             = nullptr;
	invincibleTimer = 1.0f;
	direction       = { 1,0 };
	attackType = -1;
	mellePos = { 0,0 };
	melleRadius = 0;
	isTargetRemoveOn = false;
	animeCount = 0;

	sprTail = nullptr;
}

EnemyBoss::EnemyBoss(VECTOR2 Pos) :coinReward(10000),maxSpeedX(10)
{
	hp              = 2000;
	atk             = 100;
	texSize         = { 1000.0f,700.0f };
	texPos          = { 0.0f,0.0f };
	pos             = { 1000,700 };
	color           = { 1.0f,1.0f,1.0f,1.0f };
	pivot           = { texSize.x * 0.5f,texSize.y * 0.5f };
	speed           = { 0,0 };
	offset          = { 0,0 };
	pos             = Pos;
	act             = IDLE_INIT;
	timer           = 0;
	anime           = 0;
	animeTimer      = 0;
	anime_state     = 0;
	radius          = texSize.y * 0.5f;
	spr             = nullptr;
	invincibleTimer = 1.0f;
	direction       = { 1,0 };
	attackType = -1;
	mellePos = { 0,0 };
	melleRadius = 0;
	isTargetRemoveOn = false;
	animeCount = 0;
	sprTail = nullptr;
}

void EnemyBoss::init()
{
	if (!spr)
		spr          = ImageManager::Instance().getSprite(ImageManager::SpriteNum::boss);

	if (!sprTail)
		sprTail = ImageManager::Instance().getSprite(ImageManager::SpriteNum::bossTail);

	hp               = 2000;
	atk              = 100;
	texSize          = { 1000.0f,700.0f };
	texPos           = { 0.0f,0.0f };
	color            = { 1.0f,1.0f,1.0f,1.0f };
	scale            = { 1.0f,1.0f };
	pivot            = { texSize.x * 0.5f,texSize.y * 0.5f };
	speed            = { 0,0 };
	offset           = { 0,0 };
	act              = IDLE_INIT;
	timer            = 0;
	anime            = 0;
	animeTimer       = 0;
	anime_state      = 0;
	radius           = texSize.y * 0.5f;
	invincibleTimer  = 1.0f;
	direction        = { 1,0 };
	pos              = { 500,500 };
	attackType       = -1;
	mellePos         = { 0,0 };
	melleRadius      = 0;
	isTargetRemoveOn = false;
	animeCount       = 0;
	act = ATTACK2_INIT;
}

void EnemyBoss::deinit()
{
	isTargetRemoveOn = true;
}

void EnemyBoss::update(CAMERA& camera, VECTOR2 targetPos)
{
	//攻撃出てない様にする
	isAttackOn       = false;
	attackType       = none;
	isTargetRemoveOn = false;

	//状態遷移
	state();

	//無敵時間更新
	invincibleTimerUpdate();

	//画面外に出た場合移動 攻撃時は移動しない
	moveHorizontalInCamera(camera);

	// 速度制限
	if (speed.x > maxSpeedX) speed.x = maxSpeedX;
	if (speed.x < -maxSpeedX) speed.x = -maxSpeedX;

	//摩擦
	friction(this);

	//位置に速度足す
	pos += speed;

	//スケール反転
	ScaleReverse(targetPos);

	//死んだら破棄
	if (isDeath())
	{
		Destroy();
	}
	debug::setString("Pos,state:%f:%f:%d", pos.x, pos.y,act);
}

void EnemyBoss::state()
{
	//モーションないからanimieUpdateのなかとか適当　超仮
	switch (act)
	{
	case IDLE_INIT:
		anime_state = 0;
		animeCount = 0;
		act = IDLE;

	case IDLE:
		//2段アニメーション
		if (!animeCount)
		{
			if (animeUpdate(7, 14, 6, true))
			{
				animeCount++;
				anime_state = 0;
			}
		}	
		else
			if (animeUpdate(8, 1, 6, true))
			{
				animeCount = 0;
				anime_state = 0;
				//act = ATTACK1_INIT;	//仮
			}

		if (fabsf(speed.x) > 0.0f)			act = WALK_INIT;
		break;

	case WALK_INIT:
		anime_state = 0;
		act = WALK;

	case WALK:
		animeUpdate(9,11,6, true);
		if (fabsf(speed.x) <= 0.3f) act = IDLE_INIT;
		break;

	case ATTACK1_INIT:
		anime_state = 0;
		animeCount = 0;
		mellePos = { pos.x + (200 * direction.x),pos.y - 100 };
		act = ATTACK1;
		
	case ATTACK1:
		switch (animeCount)
		{	//とびかかり１段目
		case 0:
			if (animeUpdate(0, 14, 6, true))
			{
				animeCount++;
				anime_state = 0;
			}
			break;
			//とびかかり２段目
		case 1:
			if (animeUpdate(1, 2, 6, true))
			{
				animeCount++;
				anime_state = 0;
			}
			break;
			//とびかかり発生
		case 2:
			if (animeUpdate(2, 11, 6, true))
			{
				isTargetRemoveOn = true;
				act = FALL_INIT;
			}

			//攻撃発生
			if (animeTimer == 8 * 6)
			{
				isAttackOn = true;	//球発射
				attackType = melle;
			}
			break;
		}

		break;

	case FALL_INIT:
		anime_state = 0;
		act = FALL;

	case FALL:
		//接地しているかどうかの条件も後で追加する
		if (animeUpdate(3, 4, 6, false))
		{
			act = LANDING_INIT;
		}

		break;

	case LANDING_INIT:
		anime_state = 0;
		act = LANDING;

	case LANDING:
		if (animeUpdate(4, 4, 6, false))
		{
			act = IDLE_INIT;
		}

		break;

	case ATTACK2_INIT:
		anime_state = 0;
		animeCount = 0;
		act = ATTACK2;

	case ATTACK2:
	{
		switch (animeCount)
		{	//しっぽ１段目
		case 0:
		{
			if (animeUpdate(5, 14, 6, true))
			{
				animeCount++;
				anime_state = 0;
			}

			const int TAIL_SEG = 10;
			const float SEG_LEN = 50.0f;
			for (int i = 0;i < TAIL_SEG;i++)
			{
				if (animeTimer == 6 * 7)
				{
					TailHitCircle* c=new TailHitCircle(
						&ProjectileManager::Instance(),
						10,						//damage
						Projectile::kinds::enemy,
						0.3f,					//lifeLimit
						sprTail,				//使う画像
						{ 30,30 },				//TEX_SIZE
						{ -1.5f,1.5f },					//Scale
						{ 0,0 },					//Speed
						25*1.5f,					//radius
						this,					//owner
						{ (i + 1) * SEG_LEN,-100 },			//offset
						16.0f
					);
				}
			}

			break;
		}
			//しっぽ２段目
		case 1:
			if (animeUpdate(6, 2, 6, true))
			{
				act = IDLE_INIT;
				act = ATTACK2_INIT;
			}
			break;
		}

		break;
	}
	case ATTACK3_INIT:
		anime_state = 0;
		act = ATTACK2;

	case ATTACK3:

		break;

	case ATTACK4_INIT:
		anime_state = 0;
		act = ATTACK2;

	case ATTACK4:

		break;
	}
}