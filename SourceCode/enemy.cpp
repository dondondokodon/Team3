#include "Enemy.h"
#include "EnemyManager.h"

Enemy::Enemy():coinReward(100),maxSpeedX(3)
{
	hp          = 100;
	atk         = 50;
	texSize     = { 320.0f,320.0f };
	texPos      = { 0.0f,0.0f };
	pos         = { 1000,500 };
	color       = { 1.0f,1.0f,1.0f,1.0f };
	scale       = { 1.0f,1.0f };
	pivot       = { texSize.x * 0.5f,texSize.y * 0.5f };
	speed       = { 0,0 };
	offset      = { 0,0 };
	act         = IDLE_INIT;
	timer       = 0;
	anime       = 0;
	animeTimer  = 0;
	anime_state = 0;
	radius      = texSize.y * 0.5f;
	spr         = nullptr;
}

Enemy::Enemy(VECTOR2 Pos) :coinReward(100), maxSpeedX(3)
{
	hp          = 100;
	atk         = 50;
	texSize     = { 320.0f,320.0f };
	texPos      = { 0.0f,0.0f };
	pos         = { Pos.x,Pos.y};
	color       = { 1.0f,1.0f,1.0f,1.0f };
	scale       = { 0.5f,0.5f };
	pivot       = { texSize.x * 0.5f,texSize.y * 0.5f };
	speed       = { 0,0 };
	offset      = { 0,0 };
	act         = IDLE_INIT;
	timer       = 0;
	anime       = 0;
	animeTimer  = 0;
	anime_state = 0;
	radius      = texSize.y * 0.5f;
	spr         = nullptr;
}

void Enemy::init()  
{
	hp          = 100;
	atk         = 50;
	texSize     = { 320.0f,320.0f };
	texPos      = { 0.0f,0.0f };
	//pos         = { 1000,500 };		引数付きコンストラクタで設定する場合があるのでinitでは書かない
	color       = { 1.0f,1.0f,1.0f,1.0f };
	scale       = { 0.7f,0.7f };
	pivot       = { texSize.x * 0.5f,texSize.y * 0.5f };
	moveInCamera = false;
	speed       = { 0,0 };
	offset      = { 0,0 };
	act         = IDLE_INIT;
	timer       = 0;
	anime       = 0;
	animeTimer  = 0;
	anime_state = 0;
	radius      = texSize.y * 0.3f*scale.x;
	if(!spr)
	spr.reset(sprite_load(L"./Data/Images/teki_motto_tadasii_sprite.png"));
}

void Enemy::deinit()
{

}

void Enemy::update(CAMERA& camera)
{
	//状態遷移
	state();

	moveHorizontalInCamera(camera);

	//位置に速度足す
	pos += speed;

	friction(this);


	//死んだら破棄
	if (isDeath())
	{
		Destroy();
		//coinReward = 100;
	}

}

void Enemy::state()
{
	switch (act)
	{
	case IDLE_INIT:
		anime_state = 0;
		act = IDLE;

	case IDLE:
		if (animeUpdate(0, 14, 6, true))	act = ATTACK1_INIT;
		if (fabsf(speed.x) > 0.0f)			act = WALK_INIT;
		break;

	case WALK_INIT:
		anime_state = 0;
		act = WALK;

	case WALK:
		if(animeUpdate(1, 10, 6, false))	act = IDLE_INIT;
		break;

	case ATTACK1_INIT:
		anime_state = 0;
		act = ATTACK1;

	case ATTACK1:
		if (animeUpdate(2, 10, 6, false))	act = IDLE_INIT;
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

	//const float MAX_S = 3.0f;

	//画面外に出たら中に入るモードに行く
	if (pos.x < camLeft || pos.x > camRight)
	{
		moveInCamera = true;
	}

	// --- 回収モード ---
	if (moveInCamera)
	{
		float targetX;		//目標地点

		if (pos.x < safeLeft)
			targetX = safeLeft;
		else if (pos.x > safeRight)
			targetX = safeRight;
		else
		{
			// 安全ラインに入ったら終了
			moveInCamera = false;
			return;
		}

		//目標地点との距離に応じて引き寄せ速度を変える
		float dx = targetX - pos.x;
		speed.x += dx * 0.02f; //dxに引き寄せ力をかける
	}

	// 速度制限
	if (speed.x > maxSpeedX) speed.x = maxSpeedX;
	if (speed.x < -maxSpeedX) speed.x = -maxSpeedX;
}
