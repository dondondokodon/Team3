#include "Enemy.h"
#include "EnemyManager.h"

Enemy::Enemy():coinReward(100)
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

Enemy::Enemy(VECTOR2 Pos) :coinReward(100)
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

void Enemy::update()
{
	//状態遷移
	state();

	//位置に速度足す
	pos += speed;

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
		if (fabsf(speed.x) > 0.0f)				act = WALK_INIT;
		if (animeUpdate(0, 14, 6, true))	act = ATTACK1_INIT;
		break;

	case WALK_INIT:
		anime_state = 0;
		act = WALK;

	case WALK:
		if(animeUpdate(1, 10, 6, false)) act = IDLE_INIT;
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
