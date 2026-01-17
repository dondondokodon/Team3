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
		Enemy,
		PlayerBullet,
		EnemyBullet,

		Map,
		Shop,
		Battle,
		MiddleBoss,
		LastBoss,
		Event,
		InShop,

		veryCostUp,
		extraJump,
		motionRapid,

		billBack,
		billBackBack,
		billMiddle,
		billFront,
		billGround,

		casinoBack,
		casinoBackBack,
		casinoMiddle,
		casinoFront,
		casinoGround,

		boss,
		bossTail,
		bossJump,

		coin,

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

