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
		back,
		backBack,
		middle,
		front,
		ground,
		boss,

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

