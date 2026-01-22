#include "UI_Manager.h"

DegMoneyText::DegMoneyText(VECTOR2 pos)
{
	spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::lostCoinText);//後で差し替え
	this->pos = pos;//spawnで作った座標を入れる
	scale = { 1,1 };
	texPos = { 0,0 };
	texSize = { 200,50 };//仮置き
	pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
	color = { 1,1,1,1 };
	speed = { 0,0 };
	offset = { };
	angle = 0;
	direction = { -1,0 };//減らす分は左側
	kind = textUI::kinds::deg;
}


AddMoneyText::AddMoneyText(VECTOR2 pos)
{
	spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::lostCoinText);//後で差し替え
	this->pos = pos;
	scale = { 1,1 };
	texPos = { 0,0 };
	texSize = { 200,50 };//仮置き
	pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
	color = { 1,1,1,1 };
	speed = { 0,0 };
	offset = { };
	angle = 0;
	direction = { 1,0 };//増やす分は右側
	kind = textUI::kinds::add;

}

void textUI_Manager::spawnDegText(Character& target)
{
	if (target.getDir() == VECTOR2{ 1,0 })	//右向きなら
	{
		VECTOR2 spawnPos = {};
		spawnPos = target.getPos() + VECTOR2{ -70, -70 };
		texts.emplace_back(std::make_unique<DegMoneyText>(spawnPos));
	}
	else if (target.getDir() == VECTOR2{ -1,0 })	//左向きなら
	{
		VECTOR2 spawnPos = {};
		spawnPos = target.getPos() + VECTOR2{ 70, -70 };
		texts.emplace_back(std::make_unique<DegMoneyText>(spawnPos));
	}

}

void textUI_Manager::spawnAddText(Character& target)
{
	if (target.getDir() == VECTOR2{ 1,0 })	//右向きなら
	{
		VECTOR2 spawnPos = {};
		spawnPos = target.getPos() + VECTOR2{ 70, -70 };
		texts.emplace_back(std::make_unique<AddMoneyText>(spawnPos));
	}
	else if (target.getDir() == VECTOR2{ -1,0 })	//左向きなら
	{
		VECTOR2 spawnPos = {};
		spawnPos = target.getPos() + VECTOR2{ -70, -70 };
		texts.emplace_back(std::make_unique<AddMoneyText>(spawnPos));
	}

}

void textUI_Manager::update()
{
	float up = -1.0f;
	float down = 1.0f;
	float alpha = -0.05f;
	int TextCount = textCount();
	for (int i = 0; i < TextCount; i++)
	{
		textUI* text = getText(i);

		if (text->getKind() == textUI::kinds::add)
			text->setPosition(text->getPos() + VECTOR2{0, up});

		if (text->getKind() == textUI::kinds::deg)
			text->setPosition(text->getPos() + VECTOR2{0, down});

		VECTOR4 c = text->getColor();
		c.w += alpha;
		text->setColor(c);

	}
}

void textUI_Manager::render(CAMERA& camera)
{
	int TextCount = textCount();
	for (int i = 0; i < TextCount; i++)
	{
		textUI* text = getText(i);

		text->cameraRender(camera);
	}

}

void textUI_Manager::Clear()
{
	texts.clear();
}