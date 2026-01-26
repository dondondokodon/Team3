#include "SceneBuildSlect.h"
#include "../GameLib/game_lib.h"
#include <functional>
#include <random>
#include "audio.h"
using namespace input;
int j;				//どのカードを選んでいるか
std::unique_ptr<extraSprite> selectingMessage;
std::unique_ptr<extraSprite> price_board;

void SceneBuildSelect::init()
{
	j = 0;
	state = 0;
	spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::InShop);

	money.setSprite(ImageManager::Instance().getSprite(ImageManager::SpriteNum::coin));

	selectingMessage = std::make_unique<extraSprite>( 
		ImageManager::Instance().getSprite(ImageManager::SpriteNum::selectingGetPark),
		VECTOR2{SCREEN_W * 0.5f,50.0f},
		VECTOR2{1,1},
		VECTOR2{0,0},
		VECTOR2{684,93},
		VECTOR4{1,1,1,1},
		VECTOR2{0,0},VECTOR2{0,0},
		VECTOR2{0,0} );

	price_board = std::make_unique<extraSprite>(
		ImageManager::Instance().getSprite(ImageManager::SpriteNum::priceBoard),
		VECTOR2{ -800, -800 },
		VECTOR2{ 1,1 },
		VECTOR2{ 0,0 },
		VECTOR2{ 237,229 },
		VECTOR4{ 1,1,1,1 },
		VECTOR2{ 0,0 }, VECTOR2{ 0,0 },
		VECTOR2{ 0,0 });
	//selectingMessage->setSprite(ImageManager::Instance().getSprite(ImageManager::SpriteNum::selectingGetPark));

}

void SceneBuildSelect::update()
{
	switch (state)
	{
	case 0:
		state++;

	case 1:
		//srand(unsigned int(time(NULL)));
		//music::play(main, true);
		setBuild();
		state++;

	case 2:
		//デバッグ用
		//if (TRG(0) & PAD_START)
		//	ISCENE::nextScene = SCENE_GAME;

		cardPick();

		//debug::setString("Build");

		break;

	}
}

void SceneBuildSelect::render()
{
	GameLib::clear(0, 0.6, 1);
	if (!spr) return;
	sprite_render(spr.get(), 0, 0, 1, 1, 0, 0, 1280, 720, 0, 0, 0, 1, 1, 1, 1);

	selectingMessage->render();

	for (int i = 0; i <= GetCardCount() - 1; i++)
	{
		BuildCard* card = GetCard(i);
		card->render();
		//card->buffDebuffRender();
	}
	
	BuildCard::Instance().buffDebuffRender();

	price_board->render();
	text_out(7, price_board->ShowPrice, price_board->textPos.x, price_board->textPos.y, 2, 2, price_board->textColor.x, price_board->textColor.y,price_board->textColor.z, price_board->textColor.w);

	money.render();

}


void BuildCard::buffDebuffRender()
{
	for (auto& effectText : effects)
	{
		effectText->render();
	}

}

void SceneBuildSelect::deinit()
{
	//買ったビルドをsoldOutに入れる
	//if (Build::extraVeryCost)
	//{
	//	soldOut.push_back(std::move(showWindow[i]));
	//}

	//music::stop();
	showWindow.clear();
	BuildCard::Instance().Clear();
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

	//ごり押し御免
	if (j + 1 != 2)
	{
		BuildCard::Instance().GetEffect(j)->setScale({ 1.1,1.1 });
		BuildCard::Instance().GetEffect(j + 1)->setScale({ 1.1,1.1 });
		BuildCard::Instance().GetEffect(j + 2)->setScale({ 1,1 });
		BuildCard::Instance().GetEffect(j + 3)->setScale({ 1,1 });
	}
	else//2
	{
		BuildCard::Instance().GetEffect(j + 1)->setScale({ 1.1,1.1 });
		BuildCard::Instance().GetEffect(j + 2)->setScale({ 1.1,1.1 });
		BuildCard::Instance().GetEffect(j)->setScale({ 1,1 });
		BuildCard::Instance().GetEffect(j - 1)->setScale({ 1,1 });
	}

	//価格を表示
	if (nowCard->getRank() == BuildCard::rank::strong)
	{
		price_board->setPosition(VECTOR2{ 540, 600 });
	}
	else
	{
		price_board->setPosition(VECTOR2{ 1130, 600 });
	}

	price_board->ShowPrice = std::to_string(nowCard->getPrice());
	price_board->textPos = VECTOR2{ price_board->getPos().x - 70,price_board->getPos().y - 15 };
	price_board->textColor = VECTOR4{ 1,0.8,0,1};


	//お金がないと買えない
	if (TRG(0) & PAD_START && Coin::GetCoinNum() > nowCard->getPrice())
	{
		music::play(buy);

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
		nextScene = SCENE_MAP;
	}
	else
	{
		//何かしらの演出入れたい
	}

	//メニュー
	if (TRG(0) & PAD_SELECT)
	{
		nextScene = SCENE_MAP;
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
	//購入済みかどうかを確認する関数(ラムダ式 ->boolはこの関数はbool型ですよーって意味)
	auto isSoldOut = [&](int kind) ->bool
		{
			for (auto& c : soldOut)
			{
				if (c && c->build == kind) return true;
			}
			return false;
		};

	//std::function 少し処理が遅い 毎フレーム呼ばれるような処理には不向き
	//できること　先に作り方だけを登録しておいて後で何を作るかを決める
	using Factory = std::function<std::unique_ptr<BuildCard>(VECTOR2)>;

	//強いビルド
	std::vector<std::pair<int, Factory>> strongPool =
	{
		{BuildCard::kinds::VERYCOST,   [](VECTOR2 p) {return std::make_unique < VeryCostUpBuild>(p); }},
		{BuildCard::kinds::EXTRABULLET,[](VECTOR2 p) {return std::make_unique < ExtraBulletBuild>(p); }},

	};
	//弱いビルド
	std::vector<std::pair<int, Factory>> weakPool =
	{
		//{BuildCard::kinds::EXTRAJUMP,  [](VECTOR2 p) {return std::make_unique < ExtraJumpBuild>(p); }},
		{BuildCard::kinds::MOTIONRAPID,[](VECTOR2 p) {return std::make_unique < MotionRapidBuild>(p); }},
		{BuildCard::kinds::MOONGRAVITY,[](VECTOR2 p) {return std::make_unique < MoonGravityBuild>(p); }},

	};

	//soldOutに入っていないビルド群を作る
	//ここで使われているfirst/secondはpairの1つ目の要素と２つ目の要素
	std::vector<Factory> strongCandidates;
	for (auto& it : strongPool) if (!isSoldOut(it.first)) strongCandidates.push_back(it.second);

	std::vector<Factory> weakCandidates;
	for (auto& it : weakPool) if (!isSoldOut(it.first)) weakCandidates.push_back(it.second);

	//さっき作ったビルド群が空だった場合 
	if (strongCandidates.empty())
		for (auto& it : strongPool) strongCandidates.push_back(it.second);

	if (weakCandidates.empty())
		for (auto& it : weakPool) weakCandidates.push_back(it.second);


	//乱数設定
	static std::mt19937 rng{ std::random_device{}() };

	//範囲の設定
	std::uniform_int_distribution<int> ds(0, (int)strongCandidates.size() - 1);
	std::uniform_int_distribution<int> dw(0, (int)weakCandidates.size() - 1);

	//出現位置
	//VECTOR2 left = { 340, 400 };
	//VECTOR2 right = { 940, 400 };
	VECTOR2 left = { 240, 400 };
	VECTOR2 right = { 840, 400 };

	//左に強いビルド・右に弱いビルド
	showWindow.clear();
	showWindow.emplace_back(strongCandidates[ds(rng)](left));
	showWindow.emplace_back(weakCandidates[dw(rng)](right));
}
