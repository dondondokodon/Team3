#include "SceneResult.h"
#include "SceneMap.h"
#include "audio.h"
#include "Coin.h"

std::string coincoin;
extern bool resetMap;
extern int moveTile;
extern int timeClear;
extern bool death;
int second;
int minutes;
std::string time_second;
std::string time_minutes;

void SceneResult::init()
{
	state = 0;
	sprite.init();
	resetMap = true;

	minutes = timeClear / 60;
	second = (timeClear > 59) ? timeClear % 60 : timeClear;
}

void SceneResult::update()
{
	switch (state)
	{
	case 0:
		state++;

	case 1:
		music::stop();
		music::play(result,true);
		coincoin = std::to_string(Coin::GetGotCoin());
		time_second = std::to_string(second);
		time_minutes = std::to_string(minutes);
		state++;

	case 2:
		//デバッグ用
		if (TRG(0) & PAD_START)
			ISCENE::nextScene = SCENE_TITLE;
		//SceneMap::Instance().Clear();
		sprite.update();
		debug::setString("result");

		break;

	}

}

void SceneResult::render()
{
	GameLib::clear(0, 0.5, 0.5);
	sprite.render();
	
	if (moveTile == 6 && !death)
	{
		if (minutes < 10)
		{
			if (second < 10)
				text_out(7, "0" + time_minutes + ":0" + time_second, 523, 268, 2, 2, 1, 1, 1);
			else
				text_out(7, "0" + time_minutes + ":" + time_second, 523, 268, 2, 2, 1, 1, 1);
		}
		else if (second < 10)
		{
			text_out(7, time_minutes + ":0" + time_second, 523, 268, 2, 2, 1, 1, 1);
		}
		else
			text_out(7, time_minutes + ":" + time_second, 523, 268, 2, 2, 1, 1, 1);

	}
	else
		text_out(7,"--:--", 523, 268, 2, 2, 1, 1, 1);

	text_out(7, coincoin, 523, 378, 2, 2, 1, 0.8, 0);
}

void SceneResult::deinit()
{
	Coin::SetCoinNum(1500);
	music::stop();

}



//////////////////////////////////////////////////////////////////////////
///////////////////////////spriteの中身////////////////////////////////////
void resultScene::init()
{
	back.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::resultBack);
	back.pos = {};
	back.scale = { 1,1 };
	back.texPos = { 0,0 };
	back.texSize = { 1280, 720 };
	back.pivot = { 0,0 };
	back.color = { 1,1,1,1 };
	back.speed = { 0,0 };
	back.offset = { 0,0 };
	back.angle = 0;
	back.act = 0;
	back.timer = 0;
	back.anime = 0;
	back.animeTimer = 0;
	back.anime_state = 0;
	back.radius = 0;

	rank.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::scoreSprite);
	rank.pos = {SCREEN_W * 0.6f, SCREEN_H * 0.55f};
	rank.scale = { 1,1 };
	rank.texPos = { 0,0 };
	rank.texSize = { 256, 256 };
	rank.pivot = { 0,0 };
	rank.color = { 1,1,1,1 };
	rank.speed = { 0,0 };
	rank.offset = { 0,0 };
	rank.angle = 0;
	rank.act = 0;
	rank.timer = 0;
	rank.anime = 0;
	rank.animeTimer = 0;
	rank.anime_state = 0;
	rank.radius = 0;

	resultMassage.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::scoreSprite);
	resultMassage.pos = {SCREEN_W * 0.5f, SCREEN_H * 0.3f};
	resultMassage.scale = { 1,1 };
	resultMassage.texPos = { 0,256*2 };
	resultMassage.texSize = { 768, 256 };
	resultMassage.pivot = { resultMassage.texSize.x * 0.5f,resultMassage.texSize.y * 0.5f };
	resultMassage.color = { 1,1,1,1 };
	resultMassage.speed = { 0,0 };
	resultMassage.offset = { 0,0 };
	resultMassage.angle = 0;
	resultMassage.act = 0;
	resultMassage.timer = 0;
	resultMassage.anime = 0;
	resultMassage.animeTimer = 0;
	resultMassage.anime_state = 0;
	resultMassage.radius = 0;

}

void resultScene::update()
{
	//仮置き
	if (calcScore() < 500)
		rank.texPos = VECTOR2{ 0,0 };
	else if (calcScore() < 1500)
		rank.texPos = VECTOR2{ 256,0 };
	else if (calcScore() < 3000)
		rank.texPos = VECTOR2{ 256 * 2,0 };
	else
		rank.texPos = VECTOR2{ 256 * 3,0 };

	if (death)
	{
		resultMassage.texPos = VECTOR2{ 0 ,256 * 3 };
		resultMassage.pos = VECTOR2{ SCREEN_W * 0.55f, SCREEN_H * 0.3f };
	}
	
}

void resultScene::deinit()
{

}

void resultScene::render()
{
	back.render();
	rank.render();
	resultMassage.render();
}

int resultScene::calcScore()
{
	return Coin::GetGotCoin() / timeClear;
}