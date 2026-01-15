#include "EnemyBoss.h"
#include "ImageManager.h"
#include "HitBox.h"
#include "ProjectileManager.h"

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
}

void EnemyBoss::init()
{
	if (!spr)
		spr          = ImageManager::Instance().getSprite(ImageManager::SpriteNum::boss);
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
	act = ATTACK1_INIT;
}

void EnemyBoss::deinit()
{
	isTargetRemoveOn = true;
}

void EnemyBoss::update(CAMERA& camera, VECTOR2 targetPos)
{
	//UŒ‚o‚Ä‚È‚¢—l‚É‚·‚é
	isAttackOn = false;
	attackType = none;
	isTargetRemoveOn = false;

	//ó‘Ô‘JˆÚ
	state();

	//–³“GŽžŠÔXV
	invincibleTimerUpdate();

	//‰æ–ÊŠO‚Éo‚½ê‡ˆÚ“® UŒ‚Žž‚ÍˆÚ“®‚µ‚È‚¢
	moveHorizontalInCamera(camera);

	// ‘¬“x§ŒÀ
	if (speed.x > maxSpeedX) speed.x = maxSpeedX;
	if (speed.x < -maxSpeedX) speed.x = -maxSpeedX;

	//–€ŽC
	friction(this);

	//ˆÊ’u‚É‘¬“x‘«‚·
	pos += speed;

	//ƒXƒP[ƒ‹”½“]
	ScaleReverse(targetPos);

	//Ž€‚ñ‚¾‚ç”jŠü
	if (isDeath())
	{
		Destroy();
	}
	debug::setString("Pos,state:%f:%f:%d", pos.x, pos.y,act);
}

void EnemyBoss::state()
{
	//ƒ‚[ƒVƒ‡ƒ“‚È‚¢‚©‚çanimieUpdate‚Ì‚È‚©‚Æ‚©“K“–@’´‰¼
	switch (act)
	{
	case IDLE_INIT:
		anime_state = 0;
		animeCount = 0;
		act = IDLE;

	case IDLE:
		//2’iƒAƒjƒ[ƒVƒ‡ƒ“
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
				//act = ATTACK1_INIT;	//‰¼
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
		{	//‚Æ‚Ñ‚©‚©‚è‚P’i–Ú
		case 0:
			if (animeUpdate(0, 14, 6, true))
			{
				animeCount++;
				anime_state = 0;
			}
			break;
			//‚Æ‚Ñ‚©‚©‚è‚Q’i–Ú
		case 1:
			if (animeUpdate(1, 2, 6, true))
			{
				animeCount++;
				anime_state = 0;
			}
			break;
			//‚Æ‚Ñ‚©‚©‚è”­¶
		case 2:
			if (animeUpdate(2, 11, 6, true))
			{
				isTargetRemoveOn = true;
				act = FALL_INIT;
			}

			//UŒ‚”­¶
			if (animeTimer == 8 * 6)
			{
				isAttackOn = true;	//‹…”­ŽË
				attackType = melle;
			}
			break;
		}

		break;

	case FALL_INIT:
		anime_state = 0;
		act = FALL;

	case FALL:
		//Ú’n‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©‚ÌðŒ‚àŒã‚Å’Ç‰Á‚·‚é
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
		switch (animeCount)
		{	//‚µ‚Á‚Û‚P’i–Ú
		case 0:
			if (animeUpdate(5, 14, 6, true))
			{
				animeCount++;
				anime_state = 0;
			}
			break;
			//‚µ‚Á‚Û‚Q’i–Ú
		case 1:
			if (animeUpdate(6, 2, 6, true))
			{
				act = IDLE_INIT;
			}
			break;
		}
		

		break;

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