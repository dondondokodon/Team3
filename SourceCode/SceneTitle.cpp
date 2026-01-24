#include"SceneTitle.h"
#include "../GameLib/game_lib.h"
#include "ImageManager.h"
using namespace input;

void SceneTitle::init()
{
	state = 0;
	spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::titleBack);
	tramp[0].setSprite(ImageManager::Instance().getSprite(ImageManager::SpriteNum::titleSprites));
	for (int i = 0; i < 5; i++)
	{
		tramp[i].setTexSize(VECTOR2{ 743 ,509 });
		//tramp[i].setTexPos(VECTOR2{  743 * i, 0 });
		tramp[i].setPivot(VECTOR2{ tramp[i].getTexSize().x * 0.5f,tramp[i].getTexSize().y * 0.5f });
		tramp[i].setPosition(VECTOR2{ SCREEN_W * 0.5f, SCREEN_H * 0.55f });
	}
}

void SceneTitle::update()
{
	switch (state)
	{
	case 0:
		state++;

	case 1:
		GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);
		state++;

	case 2:
		//デバッグ用
		if (TRG(0) & PAD_START)
			ISCENE::nextScene = SCENE_MAP;
		

		break;

	}
}

void SceneTitle::render()
{
	GameLib::clear(0, 0, 1);
	
	sprite_render(spr.get(), 0, 0, 1, 1, 0, 0, 1280, 720, 0, 0, 0, 1, 1, 1, 1);

	for(int i = 0; i < 5; i++)
		tramp[i].render();
	
	//text_out(1, "0123456789", 500, 500, 1, 1, 1 ,0,0);
}


void SceneTitle::deinit()
{

}

void SceneTitle::deleteSprite()
{
	//delete player
}

void titleSprite::init()
{

}