#include "ImageManager.h"

void ImageManager::load()
{
	spr[Player].reset(GameLib::sprite_load(L"./Data/Images/ziki_motto_tadasii_sprite.png"));
	spr[Enemy].reset(GameLib::sprite_load(L"./Data/Images/teki_motto_tadasii_sprite.png"));
	spr[PlayerBullet].reset(GameLib::sprite_load(L"./Data/Images/1213_coin6x6.png"));
	spr[EnemyBullet].reset(GameLib::sprite_load(L"./Data/Images/bullet.png"));

	spr[Map].reset(GameLib::sprite_load(L"./Data/Images/map.png"));
	spr[boss].reset(GameLib::sprite_load(L"./Data/Images/eirian.png"));
	spr[bossTail].reset(GameLib::sprite_load(L"./Data/Images/tail.png"));
	spr[Shop].reset(GameLib::sprite_load(L"./Data/Images/shop.png"));
	spr[Battle].reset(GameLib::sprite_load(L"./Data/Images/battle.png"));
	spr[MiddleBoss].reset(GameLib::sprite_load(L"./Data/Images/middleBoss.png"));
	spr[LastBoss].reset(GameLib::sprite_load(L"./Data/Images/lastBoss.png"));
	spr[Event].reset(GameLib::sprite_load(L"./Data/Images/event.png"));
	spr[InShop].reset(GameLib::sprite_load(L"./Data/Images/shop_room.png"));
	spr[veryCostUp].reset(GameLib::sprite_load(L"./Data/Images/build0.png"));
	spr[extraJump].reset(GameLib::sprite_load(L"./Data/Images/build1.png"));
	spr[motionRapid].reset(GameLib::sprite_load(L"./Data/Images/build2.png"));

	spr[billBack].reset(GameLib::sprite_load(L"./Data/Images/back.png"));
	spr[billBackBack].reset(GameLib::sprite_load(L"./Data/Images/back-back.png"));
	spr[billMiddle].reset(GameLib::sprite_load(L"./Data/Images/back-middle.png"));
	spr[billFront].reset(GameLib::sprite_load(L"./Data/Images/back-front.png"));
	spr[billGround].reset(GameLib::sprite_load(L"./Data/Images/ground.png"));

	spr[casinoBack].reset(GameLib::sprite_load(L"./Data/Images/casinoBack.png"));
	spr[casinoMiddle].reset(GameLib::sprite_load(L"./Data/Images/casinoMiddle.png"));
	spr[casinoFront].reset(GameLib::sprite_load(L"./Data/Images/casinoFront.png"));

	spr[coin].reset(GameLib::sprite_load(L"./Data/Images/coinUi.png"));
}

std::shared_ptr<GameLib::Sprite> ImageManager::getSprite(int num)
{
	//”ÍˆÍŠOƒ`ƒFƒbƒN
	if (num >= Max)	return nullptr;
	return spr[num];
}