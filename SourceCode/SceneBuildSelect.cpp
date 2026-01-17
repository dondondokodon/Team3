#include "SceneBuildSlect.h"
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
		srand(unsigned int(time(NULL)));
		setBuild();
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
	//nowCard->update();
	if (TRG(0) & PAD_START)
	{
		auto bought = std::move(showWindow.at(j));

		//効果反映
		bought->update();

		//購入済み
		soldOut.push_back(std::move(bought));

		//showWindowからなくす
		showWindow.erase(showWindow.begin() + j);

		//選んだビルドがshowWindowの範囲を超えていたら
		if (j >= (int)showWindow.size())	j = 0;

		//次のシーンへ
		nextScene = SCENE_GAME;
	}

	for (int j = 0; j <= GetCardCount() - 1; j++)
	{
		BuildCard* card = GetCard(j);

//		card->setLocalPos(WorldToLocal(card->getWorldPos()));

		if (card != nowCard)
			card->setScale({ 1,1 });
	}
}

void SceneBuildSelect::setBuild()
{
	VECTOR2 left = { 240, 400 };
	VECTOR2 right = { 780, 400 };


	showWindow.emplace_back(std::make_unique<VeryCostUpBuild>(left));
	showWindow.emplace_back(std::make_unique<ExtraJumpBuild>(right));

}
