#include "ImageManager.h"

void ImageManager::load()
{
	spr[Player].reset(GameLib::sprite_load(L"./Data/Images/ziki_motto_tadasii_sprite.png"));
	spr[Enemy].reset(GameLib::sprite_load(L"./Data/Images/teki_motto_tadasii_sprite.png"));
	spr[PlayerBullet].reset(GameLib::sprite_load(L"./Data/Images/1213_coin6x6.png"));
	spr[EnemyBullet].reset(GameLib::sprite_load(L"./Data/Images/bullet.png"));
	spr[Map].reset(GameLib::sprite_load(L"./Data/Images/map.png"));
	spr[back].reset(GameLib::sprite_load(L"./Data/Images/back.png"));
	spr[backBack].reset(GameLib::sprite_load(L"./Data/Images/back-back.png"));
	spr[middle].reset(GameLib::sprite_load(L"./Data/Images/back-middle.png"));
	spr[front].reset(GameLib::sprite_load(L"./Data/Images/back-front.png"));
	spr[ground].reset(GameLib::sprite_load(L"./Data/Images/ground.png"));
	spr[boss].reset(GameLib::sprite_load(L"./Data/Images/boss.png"));
}

std::shared_ptr<GameLib::Sprite> ImageManager::getSprite(int num)
{
	//範囲外チェック
	if (num >= Max)	return nullptr;
	return spr[num];
}