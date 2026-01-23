#include "EnemySlip.h"
#include "Tail.h"
#include "audio.h"

EnemySlip::EnemySlip()
{
	hp               = 100;
	atk              = 20;
	texSize          = { 320.0f,320.0f };
	texPos           = { 0.0f,0.0f };
	pos              = { 1000,500 };
	color            = { 1.0f,1.0f,1.0f,1.0f };
	scale            = { 1.0f,1.0f };
	pivot            = { texSize.x * 0.5f,texSize.y * 0.5f };
	speed            = { 0,0 };
	offset           = { 0,0 };
	act              = WALK_INIT;
	timer            = 0;
	anime            = 0;
	animeTimer       = 0;
	anime_state      = 0;
	radius           = texSize.y * 0.5f;
	spr              = nullptr;
	isAttackOn       = false;
	isHitOn          = false;
	isTargetRemoveOn = false;
	invincibleTimer  = 1.0f;
	direction        = { 1,0 };
	hitPos           = { 0,0 };
	gravityOn = false;
}

EnemySlip::EnemySlip(VECTOR2 pos)
{
	hp               = 100;
	atk              = 20;
	texSize          = { 320.0f,320.0f };
	texPos           = { 0.0f,0.0f };
	this->pos        = pos;
	color            = { 1.0f,1.0f,1.0f,1.0f };
	scale            = { 1.0f,1.0f };
	pivot            = { texSize.x * 0.5f,texSize.y * 0.5f };
	speed            = { 0,0 };
	offset           = { 0,0 };
	act              = WALK_INIT;
	timer            = 0;
	anime            = 0;
	animeTimer       = 0;
	anime_state      = 0;
	radius           = texSize.y * 0.5f;
	spr              = nullptr;
	isAttackOn       = false;
	isHitOn          = false;
	isTargetRemoveOn = false;
	invincibleTimer  = 1.0f;
	direction        = { 1,0 };
	hitPos           = { 0,0 };
	gravityOn        = false;
}


void EnemySlip::init()
{
	hp                 = 100;
	atk                = 100;
	texSize            = { 320.0f,320.0f };
	texPos             = { 0.0f,0.0f };
	//pos              = { 1000,500 };
	color              = { 1.0f,1.0f,1.0f,1.0f };
	scale              = { 0.7f,0.7f };
	pivot              = { texSize.x * 0.5f,texSize.y * 0.5f };
	speed              = { 0,0 };
	offset             = { 0,0 };
	act                = WALK_INIT;
	timer              = 0;
	anime              = 0;
	animeTimer         = 0;
	anime_state        = 0;
	radius             = texSize.y * 0.3f*scale.x;
	spr                = ImageManager::Instance().getSprite(ImageManager::SpriteNum::EnemySlip);
	isAttackOn         = false;
	isHitOn            = false;
	isTargetRemoveOn   = false;
	invincibleTimer    = 1.0f;
	direction          = { 1,0 };
	hitPos             = { 0,0 };
	gravityOn          = true;
	exitRnd            = 30;
	fallEnergy         = { 0,1.3f };
	attackType         = -1;
	mellePos           = { 0,0 };
	melleRadius        = 0;
	exitRnd            = 40;
	isDeathOn          = false;
	isHitMotionOn      = false;
	attackTimer = 0;
}

void EnemySlip::update(CAMERA& camera, VECTOR2 targetPos)
{
	this->targetPos = targetPos;

	if (hp <= 0)	isDeathOn = true;

	attackType = none;
	isAttackOn = false;
	isTargetRemoveOn = false;

	//ƒqƒbƒgŽž‚Ì‹““®
	if (isHitOn)
	{
		hitPos = pos;
		speed.x = 3 * -direction.x;
		speed.y = -20;
		isHitOn = false;
		isHitMotionOn = true;
		gravityOn = true;
		//”í’e‚Ì‰æ‘œ‚Ý‚½‚¢‚ÉŒ©‚¦‚é‚Æ‚±‚ë‚ÉƒZƒbƒg
		texPos = { texSize.x * 9,0 };
	}

	if(isHitMotionOn)
	{
		//gravity(this, fallEnergy);
		timer++;
		if (hitPos.y < pos.y)
		{
			speed.y = -speed.y * 0.5f;
		}
		if (timer > 60)
		{
			isHitMotionOn = false;
			timer = 0;
			speed = { 0,0 };
			hitPos = { 0,0 };
			act = WALK_INIT;
		}
	}
	if (speed.y < 0)		isGround = false;
	//d—Í
	if (!isGround)
		gravity(this, fallEnergy);
	
	pos += speed;

	if (!isHitMotionOn)
	{
		//ƒXƒP[ƒ‹”½“]
		if(act!=ATTACK&&act!=SLIP)
		ScaleReverse(targetPos);

		//ó‘Ô‘JˆÚ
		state();

		//’n–Ê”»’è
		if (pos.y > GROUND_Y - pivot.y * scale.y)
		{
			pos.y = GROUND_Y - pivot.y * scale.y;
			speed.y = 0;
			isGround = true;
		}

		//–³“GŽžŠÔXV
		invincibleTimerUpdate();

		// ‘¬“x§ŒÀ
		if (ATTACK != act)
		{
			if (speed.x > maxSpeedX) speed.x = maxSpeedX;
			if (speed.x < -maxSpeedX) speed.x = -maxSpeedX;
		}

		//–€ŽC
		if (act != ATTACK)
			friction(this);
	}

	

	//Ž€‚ñ‚¾‚ç”jŠü
	if (isDeath())
	{
		Destroy();
	}
}

void EnemySlip::deinit()
{

}

void EnemySlip::state()
{
	switch (act)
	{
	case WALK_INIT:
	{
		anime_state = 0;
		
		if (!moveInCamera)
		{
			addSpeed = direction.x * 3.0f;
		}
	
		act = WALK;

	}
	case WALK:
		animeUpdate(0, 9, 6, true);
		if(!moveInCamera)
		speed.x = addSpeed;

		if (fabsf(targetPos.x - pos.x) < 500.0f)
		{
			act = ATTACK_INIT;
		}
		break;

	case ATTACK_INIT:
		anime_state = 0;
		attackTimer = 0;
		speed.x     = 0.0f;
		music::play(zako2_A);
		act         = ATTACK;

	case ATTACK:
		if (animeUpdate(1, 8, 6, false))
		{
			if(!attackTimer)
				new TailBigActionHitBox(&ProjectileManager::Instance(),
					atk,
					Projectile::kinds::enemy,
					999,
					nullptr,
					{ 50.0f,50.0f },
					{ 1.0f,1.0f },
					{ 0.0f,0.0f },
					25.0f,
					this,
					{ 0.0f,0.0f },
					40.0f,
					this,
					std::make_shared<AttackContext>()
				);
			attackTimer++;
		}
		if (animeTimer == 6 * 6)
			speed.x = 12 * direction.x;

		if (attackTimer > 30)
		{
			isTargetRemoveOn = true;
			act = SLIP_INIT;
		}
			
		break;

	case SLIP_INIT:
		anime_state = 0;
		act = SLIP;

	case SLIP:
		if (animeUpdate(2, 18, 6, false))
		{
			act = WALK_INIT;
		}

		if (animeTimer == 6 * 5)
			speed.x = 0.0f;
		break;
	}
}