#include "EnemyBoss.h"
#include "ImageManager.h"

EnemyBoss::EnemyBoss() :coinReward(10000), maxSpeedX(10)
{
	hp              = 2000;
	atk             = 100;
	texSize         = { 1000.0f,500.0f };
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
}

EnemyBoss::EnemyBoss(VECTOR2 Pos) :coinReward(10000),maxSpeedX(10)
{
	hp              = 2000;
	atk             = 100;
	texSize         = { 1000.0f,500.0f };
	texPos          = { 0.0f,0.0f };
	pos             = { 1000,500 };
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
}

void EnemyBoss::init()
{
	if (!spr)
		spr         = ImageManager::Instance().getSprite(ImageManager::SpriteNum::boss);
	hp              = 2000;
	atk             = 100;
	texSize         = { 1000.0f,500.0f };
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
	invincibleTimer = 1.0f;
	direction       = { 1,0 };
	pos             = { 500,500 };
}

void EnemyBoss::deinit()
{

}

void EnemyBoss::update(CAMERA& camera, VECTOR2 targetPos)
{
	//攻撃出てない様にする
	isAttackOn = false;

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
	debug::setString("Pos:%f:%f", pos.x, pos.y);
}

void EnemyBoss::state()
{
	//モーションないからanimieUpdateのなかとか適当　超仮
	switch (act)
	{
	case IDLE_INIT:
		anime_state = 0;
		act = IDLE;

	case IDLE:
		if (animeUpdate(0,0,1, true))	act = ATTACK1_INIT;
		if (fabsf(speed.x) > 0.0f)			act = WALK_INIT;
		break;

	case WALK_INIT:
		anime_state = 0;
		act = WALK;

	case WALK:
		animeUpdate(0,0,1, true);
		if (fabsf(speed.x) <= 0.3f) act = IDLE_INIT;
		break;

	case ATTACK1_INIT:
		anime_state = 0;
		act = ATTACK1;

	case ATTACK1:
		if (animeUpdate(0, 0,1, false))	act = IDLE_INIT;
		if (animeTimer == 8 * 6)	isAttackOn = true;	//球発射

		if (animeTimer > 9 * 6)
			speed.x = 5.0f * -direction.x;				//ノックバック
		break;

	case ATTACK2_INIT:
		anime_state = 0;
		act = ATTACK2;

	case ATTACK2:

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