#include "SceneBuildSlect.h"
#include "Build.h"
#include "../GameLib/game_lib.h"
using namespace input;
int j;				//どのカードを選んでいるか

void SceneBuildSelect::init()
{
	j = 0;
	state = 0;
	spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::InShop);

}

void SceneBuildSelect::update()
{
	switch (state)
	{
	case 0:
		state++;

	case 1:
		showWindow.emplace_back(std::make_unique<VeryCostUpBuild>(VECTOR2{ 240,360 }));
		showWindow.emplace_back(std::make_unique<ExtraJumpBuild>(VECTOR2{ 640,360 }));
		showWindow.emplace_back(std::make_unique<MotionRapidBuild>(VECTOR2{ 1040,360 }));
		state++;

	case 2:
		//デバッグ用
		//if (TRG(0) & PAD_START)
		//	ISCENE::nextScene = SCENE_GAME;

		cardPick();

		debug::setString("Build");

		break;

	}
}

void SceneBuildSelect::render()
{
	GameLib::clear(0, 0.6, 1);
	if (!spr) return;
	sprite_render(spr.get(), 0, 0, 1, 1, 0, 0, 1280, 720, 0, 0, 0, 1, 1, 1, 1);

	for (int i = 0; i <= GetCardCount() - 1; i++)
	{
		BuildCard* card = GetCard(i);
		card->render();
	}

}


void SceneBuildSelect::deinit()
{
	//買ったビルドをsoldOutに入れる
	//if (Build::extraVeryCost)
	//{
	//	soldOut.push_back(std::move(showWindow[i]));
	//}


	showWindow.clear();
}

void SceneBuildSelect::deleteSprite()
{
	//delete player
}


void VeryCostUpBuild::update()
{
	if (TRG(0) & PAD_START)
	{
		Build::extraVeryCost = true;
		ISCENE::nextScene = SCENE_GAME;
	}

}

void ExtraJumpBuild::update()
{
	if (TRG(0) & PAD_START)
	{
		Build::extraJump = true;
		ISCENE::nextScene = SCENE_GAME;
	}

}

void MotionRapidBuild::update()
{
	if (TRG(0) & PAD_START)
	{
		//Build::extraMotionRapid = true;
		//Build::extraMoonGravity = true;
		Build::extraBullet = true;
		ISCENE::nextScene = SCENE_GAME;
	}

}

void SceneBuildSelect::inputCardSelect()
{

	if (GameLib::input::TRG(0) & GameLib::input::PAD_LEFT)	//A
	{
		j--;
		if (j < 0)
			j = GetCardCount() - 1;

	}

	if (GameLib::input::TRG(0) & GameLib::input::PAD_RIGHT)	//D
	{
		j++;
		if (j > GetCardCount() - 1)
			j = 0;

	}



}

void SceneBuildSelect::cardPick()
{
	inputCardSelect();

	BuildCard* nowCard = GetCard(j);

	nowCard->setScale({ 1.1,1.1 });
	nowCard->update();

	for (int j = 0; j <= GetCardCount() - 1; j++)
	{
		BuildCard* card = GetCard(j);

//		card->setLocalPos(WorldToLocal(card->getWorldPos()));

		if (card != nowCard)
			card->setScale({ 1,1 });
	}
}
