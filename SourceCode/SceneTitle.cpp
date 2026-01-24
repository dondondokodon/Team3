#include"SceneTitle.h"
#include "../GameLib/game_lib.h"
#include "ImageManager.h"
#include "audio.h"
using namespace input;

int tap;

void SceneTitle::init()
{
	state = 0;
	spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::titleBack);
	titleSprites.emplace_back(std::make_unique<titleText>(VECTOR2{ 610, 340 }, VECTOR2{1,1}));
	selectButton.emplace_back(std::make_unique<play>(VECTOR2{ SCREEN_W * 0.5f, SCREEN_H * 0.7f }, VECTOR2{ 0,1 }));
	if (!tap)
	{
		trampCard.emplace_back(std::make_unique<trampSprite>(VECTOR2{ SCREEN_W * 0.45f,SCREEN_H * 0.65f }, trampSprite::trampNumber::S5, 5));
		trampCard.emplace_back(std::make_unique<trampSprite>(VECTOR2{ SCREEN_W * 0.45f,SCREEN_H * 0.35f }, trampSprite::trampNumber::H6, 4));
		trampCard.emplace_back(std::make_unique<trampSprite>(VECTOR2{ SCREEN_W * 0.85f,SCREEN_H * 0.55f }, trampSprite::trampNumber::H8, 3));
		trampCard.emplace_back(std::make_unique<trampSprite>(VECTOR2{ SCREEN_W * 0.55f,SCREEN_H * 0.55f }, trampSprite::trampNumber::S7, 2));
		trampCard.emplace_back(std::make_unique<trampSprite>(VECTOR2{ SCREEN_W * 0.70f,SCREEN_H * 0.55f }, trampSprite::trampNumber::H5, 1));
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
		music::play(main, true);

		for (auto& tramp : trampCard)
			tramp->setSprite(ImageManager::Instance().getSprite(ImageManager::SpriteNum::titleSprites));

		for (auto& text : titleSprites)
			text->setSprite(ImageManager::Instance().getSprite(ImageManager::SpriteNum::titleSprites));
		
		for (auto& button : selectButton)
			button->setSprite(ImageManager::Instance().getSprite(ImageManager::SpriteNum::titleSprites));

		state++;

	case 2:
		//fobO—p
//		if (TRG(0) & PAD_START && tap > 4)
		selecting();

		if (TRG(0) & PAD_START)
			tap++;


		for (auto& tramp : trampCard)
		{
			if (tap == tramp->flip)
				tramp->update();
		}

		for (auto& tramp : trampCard)
		{
			tramp->addPos(tramp->getSpeed());
			tramp->multipleSpeed(0.92f);
			if (fabs(tramp->getSpeed().x) < 0.2f)
				tramp->setSpeed(VECTOR2{ 0,0 });
		}


		break;

	}
}

void SceneTitle::render()
{
	GameLib::clear(0, 0, 1);
	
	sprite_render(spr.get(), 0, 0, 1, 1, 0, 0, 1280, 720, 0, 0, 0, 1, 1, 1, 1);

	for (auto& text : titleSprites)
		text->render();

	for (auto& button : selectButton)
		button->render();

	for(auto& tramp : trampCard)
		tramp->render();
	
}


void SceneTitle::deinit()
{
	music::stop();
	//trampCard.clear();
	//delete &WillPlay;
	//WillPlay = nullptr;
}

void SceneTitle::deleteSprite()
{
	//delete player
}


void SceneTitle::selecting()
{
	int ButtonCount = getButtonCount();
	int i = 0;
//	for (int i = 0; i < ButtonCount; i++)
	{
		if (GameLib::input::TRG(0) & GameLib::input::PAD_UP)	//W
		{
			i--;
			if (i < 0)
				i = ButtonCount - 1;

		}

		if (GameLib::input::TRG(0) & GameLib::input::PAD_DOWN)	//S
		{
			i++;
			if (i > ButtonCount - 1)
				i = 0;

		}

		titleSprite* nowButton = getButton(i);
		
		nowButton->setScale(VECTOR2{ 1.2,1.2 });

		if (TRG(0) & PAD_START && tap > 4)	nowButton->update();


	}
}

//void SceneTitle::pickButton()
//{
//	selecting();
//
//}

void trampSprite::update()
{
	VECTOR2 dir = {};
	float impulse = 0;
	if (TRG(0) & PAD_START)
	{
		switch (number)
		{
		case S5:
			dir = setDirection(VECTOR2{ 0,0 });
			impulse = 42.0f;
			break;

		case H5:
			dir = setDirection(VECTOR2{ 1280,700 });
			impulse = 45.0f;
			break;

		case H6:
			dir = setDirection(VECTOR2{ 0,300 });
			impulse = 38.0f;
			break;

		case S7:
			dir = setDirection(VECTOR2{ 1500,0 });
			impulse = 58.0f;
			break;

		case H8:
			dir = setDirection(VECTOR2{ 1180,0 });
			impulse = 25.0f;
			break;

		}
		trampImpulse(dir, impulse);
	}

}

void trampSprite::trampImpulse(VECTOR2 Direction, float Impulse)
{
	float impulse = Impulse;
	speed = Direction * impulse;
}

VECTOR2 trampSprite::setDirection(VECTOR2 Pos)
{
	VECTOR2 Vector = Pos - pos;
	float len = sqrtf(Vector.x * Vector.x + Vector.y * Vector.y);
	VECTOR2 normalize = VECTOR2{ Vector.x / len, Vector.y / len };
	return normalize;
}
