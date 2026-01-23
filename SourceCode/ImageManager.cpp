#include "ImageManager.h"

void ImageManager::load()
{
	spr[Player].reset(GameLib::sprite_load(L"./Data/Images/jiki_motto_tadasii_sprite.png"));
	spr[Player_ATTACK_Effect].reset(GameLib::sprite_load(L"./Data/Images/atk_1234_efct.png"));
	spr[Enemy].reset(GameLib::sprite_load(L"./Data/Images/teki_motto_tadasii_sprite.png"));
	spr[PlayerBullet].reset(GameLib::sprite_load(L"./Data/Images/1213_coin6x6.png"));
	spr[EnemyBullet].reset(GameLib::sprite_load(L"./Data/Images/bullet.png"));

	spr[Map].reset(GameLib::sprite_load(L"./Data/Images/map.png"));
	spr[boss].reset(GameLib::sprite_load(L"./Data/Images/erianNew.png"));
	spr[bossJump].reset(GameLib::sprite_load(L"./Data/Images/jump.png"));
	spr[bossTail].reset(GameLib::sprite_load(L"./Data/Images/sippo.png"));
	spr[bossUltTail].reset(GameLib::sprite_load(L"./Data/Images/tail.png"));
	spr[bossTailPull].reset(GameLib::sprite_load(L"./Data/Images/tail_hiki_mini.png"));
	spr[Shop].reset(GameLib::sprite_load(L"./Data/Images/shop.png"));
	spr[Battle].reset(GameLib::sprite_load(L"./Data/Images/battle.png"));
	spr[MiddleBoss].reset(GameLib::sprite_load(L"./Data/Images/middleBoss.png"));
	spr[LastBoss].reset(GameLib::sprite_load(L"./Data/Images/lastBoss.png"));
	spr[Event].reset(GameLib::sprite_load(L"./Data/Images/event.png"));
	spr[InShop].reset(GameLib::sprite_load(L"./Data/Images/shop_room.png"));
	spr[STRONG].reset(GameLib::sprite_load(L"./Data/Images/build0.png"));
	spr[WEAK].reset(GameLib::sprite_load(L"./Data/Images/build2.png"));
	spr[buff].reset(GameLib::sprite_load(L"./Data/Images/buff.png"));
	spr[debuff].reset(GameLib::sprite_load(L"./Data/Images/debuff.png"));
	spr[priceBoard].reset(GameLib::sprite_load(L"./Data/Images/price.png"));
	spr[selectingGetPark].reset(GameLib::sprite_load(L"./Data/Images/selectingGetPark.png"));

	spr[billBack].reset(GameLib::sprite_load(L"./Data/Images/back.png"));
	spr[billBackBack].reset(GameLib::sprite_load(L"./Data/Images/back-back.png"));
	spr[billMiddle].reset(GameLib::sprite_load(L"./Data/Images/back-middle.png"));
	spr[billFront].reset(GameLib::sprite_load(L"./Data/Images/back-front.png"));
	spr[billGround].reset(GameLib::sprite_load(L"./Data/Images/ground.png"));
	spr[footing].reset(GameLib::sprite_load(L"./Data/Images/footing.png"));

	spr[casinoBack].reset(GameLib::sprite_load(L"./Data/Images/casinoBack.png"));
	spr[casinoMiddle].reset(GameLib::sprite_load(L"./Data/Images/casinoMiddle.png"));
	spr[casinoFront].reset(GameLib::sprite_load(L"./Data/Images/casinoFront.png"));
	spr[casinoLnthanum].reset(GameLib::sprite_load(L"./Data/Images/lanthanum.png"));

	spr[resultBack].reset(GameLib::sprite_load(L"./Data/Images/result.png"));
	spr[scoreSprite].reset(GameLib::sprite_load(L"./Data/Images/scoreSprite.png"));

	spr[coin].reset(GameLib::sprite_load(L"./Data/Images/coinUi.png"));
	spr[lostCoinText].reset(GameLib::sprite_load(L"./Data/Images/lostCoinText.png"));
}

std::shared_ptr<GameLib::Sprite> ImageManager::getSprite(int num)
{
	//”ÍˁE�ŠOƒ`ƒFƒbƒN
	if (num >= Max)	return nullptr;
	return spr[num];
}