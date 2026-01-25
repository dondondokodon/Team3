#pragma once
#include<memory>
#include "../GameLib/game_lib.h"

class ImageManager
{
	ImageManager(){}
	~ImageManager(){}
public:
	enum SpriteNum
	{
		Player,
		Player_ATTACK_Effect,
		Enemy,
		EnemySlip,
		PlayerBullet,
		EnemyBullet,

		hitEffectE,
		hitEffectP,

		Map,
		Shop,
		Battle,
		MiddleBoss,
		LastBoss,
		Event,
		InShop,

		STRONG,
		WEAK,
		buff,
		debuff,
		priceBoard,
		selectingGetPark,

		billBack,
		billBackBack,
		billMiddle,
		billFront,
		billGround,

		casinoBack,
		casinoBackBack,
		casinoMiddle,
		casinoFront,
		casinoLnthanum,

		footing,

		resultBack,
		scoreSprite,

		boss,
		bossTail,
		bossUltTail,
		bossTailPull,
		bossJump,

		coin,
		lostCoinText,
		titleBack,
		titleSprites,

		Event1,
		Event2,
		Event3,
		Event4,
		Event5,
		EventBack,

		Max
	};

	static ImageManager& Instance()
	{
		static ImageManager instance;
		return instance;
	}

	void load();
	std::shared_ptr<GameLib::Sprite> getSprite(int num);

private:
	std::shared_ptr<GameLib::Sprite> spr[SpriteNum::Max];
};

