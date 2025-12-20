#include "Enemy.h"

Enemy::Enemy():coinReward(100)
{
	hp          = 100;
	atk         = 50;
	texSize     = { 180.0f,125.0f };
	texPos      = { 0.0f,0.0f };
	pos         = { 1000,500 };
	color       = { 1.0f,1.0f,1.0f,1.0f };
	scale       = { 1,1 };
	pivot       = { texSize.x * 0.5f,texSize.y * 0.5f };
	speed       = { 0,0 };
	offset      = { 0,0 };
	act         = 0;
	timer       = 0;
	anime       = 0;
	animeTimer  = 0;
	anime_state = 0;
	radius      = texSize.x * 0.5f;
	spr         = nullptr;
}

Enemy::Enemy(VECTOR2 Pos) :coinReward(100)
{
	hp          = 100;
	atk         = 50;
	texSize     = { 180.0f,125.0f };
	texPos      = { 0.0f,0.0f };
	pos         = { Pos.x,Pos.y};
	color       = { 1.0f,1.0f,1.0f,1.0f };
	scale       = { 1,1 };
	pivot       = { texSize.x * 0.5f,texSize.y * 0.5f };
	speed       = { 0,0 };
	offset      = { 0,0 };
	act         = 0;
	timer       = 0;
	anime       = 0;
	animeTimer  = 0;
	anime_state = 0;
	radius      = texSize.x * 0.5f;
	spr         = nullptr;
}

void Enemy::init()  
{
	hp          = 100;
	atk         = 50;
	texSize     = { 180.0f,125.0f };
	texPos      = { 0.0f,0.0f };
	pos         = { 1000,500 };
	color       = { 1.0f,1.0f,1.0f,1.0f };
	scale       = { 1,1 };
	pivot       = { texSize.x * 0.5f,texSize.y * 0.5f };
	speed       = { 0,0 };
	offset      = { 0,0 };
	act         = 0;
	timer       = 0;
	anime       = 0;
	animeTimer  = 0;
	anime_state = 0;
	radius      = texSize.x * 0.5f;
	if(!spr)
	spr.reset(sprite_load(L"./Data/Images/enemy.png"));
}
void Enemy::deinit()
{

}
void Enemy::update()
{

}
