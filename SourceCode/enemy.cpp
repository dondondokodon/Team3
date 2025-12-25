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

void Enemy::init()  
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
	if(!spr)
	spr.reset(sprite_load(L"./Data/Images/teki_motto_tadasii_sprite.png"));
}

void Enemy::deinit()
{

}

void Enemy::update()
{
	//èÛë‘ëJà⁄
	state();

	//à íuÇ…ë¨ìxë´Ç∑
	pos += speed;

	//éÄÇÒÇæÇÁîjä¸
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
	{
		animeUpdate(0, 14, 6, true);
	}	

	}
}
void Enemy::Destroy()
{
	//ÇﬂÇ¡ÇøÇ·âºíuÇ´
	spr = nullptr;
	pos = {};
}
