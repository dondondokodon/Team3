#include "Enemy.h"
#include "common.h"
#include "CAMERA.h"
#include<cstdlib>
#include"ImageManager.h"
#include "audio.h"

Enemy::Enemy():coinReward(100),maxSpeedX(3)
{
	hp              = 100;
	atk             = 20;
	texSize         = { 320.0f,320.0f };
	texPos          = { 0.0f,0.0f };
	pos             = { 1000,500 };
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
	isAttackOn      = false;
	isHitOn         = false;
	gravityOn       = false;
	isTargetRemoveOn = false;
	invincibleTimer = 1.0f;
	direction       = { 1,0 };
	hitPos          = { 0,0 };
	attackType = -1;
	mellePos = { 0,0 };
	melleRadius = 0;
}

Enemy::Enemy(VECTOR2 Pos) :coinReward(100), maxSpeedX(3)
{
	hp              = 100;
	atk             = 20;
	texSize         = { 320.0f,320.0f };
	texPos          = { 0.0f,0.0f };
	pos             = { Pos.x,Pos.y};
	color           = { 1.0f,1.0f,1.0f,1.0f };
	scale           = { 0.5f,0.5f };
	pivot           = { texSize.x * 0.5f,texSize.y * 0.5f };
	speed           = { 0,0 };
	offset          = { 0,0 };
	act             = IDLE_INIT;
	timer           = 0;
	anime           = 0;
	animeTimer      = 0;
	anime_state     = 0;
	radius          = texSize.y * 0.5f;
	isAttackOn      = false;
	spr             = nullptr;
	isHitOn         = false;
	invincibleTimer = 1.0f;
	gravityOn       = false;
	isTargetRemoveOn = false;
	direction       = {1,0};
	hitPos          = { 0,0 };
	attackType = -1;
	mellePos = { 0,0 };
	melleRadius = 0;
}

void Enemy::init()  
{
	hp				= 50;
	atk				= 30;
	texSize			= { 320.0f,320.0f };
	texPos			= { 0.0f,0.0f };
	//pos			= { 1000,500 };		引数付きコンストラクタで設定する場合があるのでinitでは書かない
	color			= { 1.0f,1.0f,1.0f,1.0f };
	scale			= { 0.7f,0.7f };
	pivot			= { texSize.x * 0.5f,texSize.y * 0.5f };
	moveInCamera	= false;
	speed			= { 0,0 };
	offset			= { 0,0 };
	act				= IDLE_INIT;
	timer			= 0;
	anime			= 0;
	animeTimer		= 0;
	anime_state		= 0;
	radius			= texSize.y * 0.3f*scale.x;
	isAttackOn		= false;
	gravityOn		= false;
	isTargetRemoveOn = false;
	if (!spr)
		spr         = ImageManager::Instance().getSprite(ImageManager::SpriteNum::Enemy);
	invincibleTimer = 1.0f;
	direction       = { -1,0 };
	hitPos          = { 0,0 };
	attackType = -1;
	mellePos = { 0,0 };
	melleRadius = 0;
	exitRnd = 40;
	isDeathOn = false;
}

void Enemy::deinit()
{
	isTargetRemoveOn = true;
}

void Enemy::update(CAMERA& camera, VECTOR2 targetPos)
{
	attackType       = none;
	isAttackOn       = false;
	isTargetRemoveOn = false;

	//ヒット時の挙動
	if (isHitOn)
	{
		hitPos    = pos;
		speed.x   = 3 * -direction.x;
		speed.y   = -20;
		isHitOn   = false;
		gravityOn = true;
		//被弾の画像みたいに見えるところにセット
		texPos    = { texSize.x * 9,0 };
	}

	//重力
	if (gravityOn)
	{
		gravity(this, fallEnergy);
		timer++;
		if (hitPos.y<pos.y)
		{
			speed.y	  = -speed.y * 0.5f;
		}
		if (timer > 60)
		{
			gravityOn = false;
			timer     = 0;
			speed     = {0,0};
			hitPos    = { 0,0 };
			act       = IDLE_INIT;
			if (hp <= 0)	isDeathOn = true;
		}
	}

	else
	{
		//状態遷移
		state();

		//無敵時間更新
		invincibleTimerUpdate();

		//画面外に出た場合移動 攻撃時は移動しない
		if (act != ATTACK1 && act != ATTACK1_INIT)
			moveHorizontalInCamera(camera);

		// 速度制限
		if (ATTACK1!=act)
		{
			if (speed.x > maxSpeedX) speed.x = maxSpeedX;
			if (speed.x < -maxSpeedX) speed.x = -maxSpeedX;
		}

		//摩擦
		if (act != ATTACK1)
			friction(this);
	}

	//位置に速度足す
	pos += speed;

	//スケール反転
	ScaleReverse(targetPos);

	//死んだら破棄
	if (isDeath())
	{
		Destroy();
		//coinReward = 100;
	}
	debug::setString("EnemyDire:%f", direction.x);
}

void Enemy::state()
{
	switch (act)
	{
	case IDLE_INIT:
		anime_state = 0;
		act = IDLE;

	case IDLE:
		if (animeUpdate(1, 9, 6, true))	act = ATTACK1_INIT;
		if (fabsf(speed.x) > 0.0f)			act = WALK_INIT;
		break;

	case WALK_INIT:
		anime_state = 0;
		act = WALK;

	case WALK:
		animeUpdate(2, 9, 6, true);
		if (fabsf(speed.x) <= 0.3f) act = IDLE_INIT;
		break;

	case ATTACK1_INIT:
		anime_state = 0;
		music::play(zakoFlyA);
		act = ATTACK1;

	case ATTACK1:
		if (animeUpdate(0, 14, 6, false))	act = IDLE_INIT;
		if (animeTimer == 8 * 6)
		{
			isAttackOn = true;
			attackType = bulet;
		}
		if (animeTimer > 9 * 6)
			speed.x = 5.0f * -direction.x;
		break;

	}
}
void Enemy::Destroy()
{
	//めっちゃ仮置き
	spr = nullptr;
	pos = {};
}

void Enemy::moveHorizontalInCamera(CAMERA& camera)
{
	//カメラの視界
	float camLeft = camera.getPos().x;
	float camRight = camLeft + SCREEN_W;

	//どれくらい内側まで移動させるか
	const float SAFE_OFFSET = 200.0f;
	

	float safeLeft = camLeft + SAFE_OFFSET;
	float safeRight = camRight - SAFE_OFFSET;


	//画面外に出たら中に入るモードに行く
	if (pos.x < camLeft || pos.x > camRight)
	{
		moveInCamera = true;
	}

	// --- 回収モード ---
	if (moveInCamera)
	{
		float targetX=pos.x;				//目標地点

		const float MIN_PULL_SPEED = 0.5f;	//最低速度

		float oldSpeedX = 0;


		if (pos.x < safeLeft)
			targetX = safeLeft;
		else if (pos.x > safeRight)
			targetX = safeRight;
		else 
		{
			//oldSpeedX = speed.x;
			if (rand() % exitRnd == 0)
			{
				// 安全ラインに入ったら終了
				moveInCamera = false;
				return;
			}
		}
		//if (oldSpeedX)
			//return;

		//目標地点との距離に応じて引き寄せ速度を変える
		float dx = targetX - pos.x;
		float pull = dx * 0.02f;

		// 最低速度保証
		if (fabsf(pull) < MIN_PULL_SPEED)
		{
			pull = (direction.x>0) ? MIN_PULL_SPEED : -MIN_PULL_SPEED;
			//pull = (dx > 0) ? MIN_PULL_SPEED : -MIN_PULL_SPEED;
		}

		speed.x += pull;
	}

	/*debug::setString(
		"pos=%.1f safeL=%.1f safeR=%.1f camL=%.1f camR=%.1f in=%d",
		pos.x, safeLeft, safeRight, camLeft, camRight, moveInCamera);*/
}

//敵のほうを見るようにする
void Enemy::ScaleReverse(VECTOR2 target)
{
	/*if (target.x < pos.x)
	{
		if (scale.x < 0)
		{
			direction.x = -1;
			scale.x = -scale.x;
		}
	}
	else if (scale.x > 0)
	{
		scale.x = -scale.x;
		direction.x = 1;
	}*/

	//真上に来た時に左右になりまくるのがいやなのでデッドゾーンを付けたver
	//if (fabsf(speed.x) > 0.5f)	return;		//スピードがあるときは変えない

	const float DEAD_ZONE = 20.0f; // この範囲では向きを変えない
	float dx = target.x - pos.x;

	if (dx < -DEAD_ZONE)
	{
		direction.x = -1;
		scale.x = fabsf(scale.x);
	}
	else if (dx > DEAD_ZONE)
	{
		direction.x = 1;
		scale.x = -fabsf(scale.x);
	}
}

//発射方向を決める
VECTOR2 Enemy::shotDir(VECTOR2 targetPos)
{
	return normalize({targetPos.x-pos.x,targetPos.y-pos.y});	//ターゲットの方向
}