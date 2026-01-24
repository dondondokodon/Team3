#include "textUI_Manager.h"

DegMoneyText::DegMoneyText(VECTOR2 pos, int coin)
{
	spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::lostCoinText);//後で差し替え
	this->pos = pos;//spawnで作った座標を入れる
	scale = { 3,3 };
	texPos = { 0,0 };
	texSize = { 200,50 };//仮置き
	pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
	color = { 1,1,1,1 };
	speed = { 0,0 };
	offset = { };
	angle = 0;
	direction = { -1,0 };//減らす分は左側
	kind = textUI::kinds::deg;
	moveCoin = coin;
}


AddMoneyText::AddMoneyText(VECTOR2 pos, int coin)
{
	spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::lostCoinText);//後で差し替え
	this->pos = pos;
	scale = { 3,3 };
	texPos = { 0,0 };
	texSize = { 200,50 };//仮置き
	pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
	color = { 1,1,1,1 };
	speed = { 0,0 };
	offset = { };
	angle = 0;
	direction = { 1,0 };//増やす分は右側
	kind = textUI::kinds::add;
	moveCoin = coin;
}

void textUI_Manager::spawnDegText(Character& target, int coin)
{
	if (target.getDir() == VECTOR2{ 1,0 })	//右向きなら
	{
		VECTOR2 spawnPos = {};
		spawnPos = target.getPos() + VECTOR2{ -120, -70 };
		texts.emplace_back(std::make_unique<DegMoneyText>(spawnPos, coin));
	}
	else if (target.getDir() == VECTOR2{ -1,0 })	//左向きなら
	{
		VECTOR2 spawnPos = {};
		spawnPos = target.getPos() + VECTOR2{ 70, -70 };
		texts.emplace_back(std::make_unique<DegMoneyText>(spawnPos, coin));
	}

}

void textUI_Manager::spawnAddText(Character& target, int coin)
{
	if (target.getDir() == VECTOR2{ 1,0 })	//右向きなら
	{
		VECTOR2 spawnPos = {};
		spawnPos = target.getPos() + VECTOR2{ 70, -70 };
		texts.emplace_back(std::make_unique<AddMoneyText>(spawnPos, coin));
	}
	else if (target.getDir() == VECTOR2{ -1,0 })	//左向きなら
	{
		VECTOR2 spawnPos = {};
		spawnPos = target.getPos() + VECTOR2{ -120, -70 };
		texts.emplace_back(std::make_unique<AddMoneyText>(spawnPos, coin));
	}

}

void textUI_Manager::update()
{
	float up = -1.0f;
	float down = 1.0f;
	float alpha = -0.03f;
	for (auto it = texts.begin(); it != texts.end();)
	{
		textUI* text = it->get();
		VECTOR4 c = text->getColor();
		c.w += alpha;
		//c.z += 0.1f;
		if (text->getKind() == textUI::kinds::add)
		{
			text->setPosition(text->getPos() + VECTOR2{ 0, up });
			c.z = 0;
		}

		if (text->getKind() == textUI::kinds::deg)
		{
			text->setPosition(text->getPos() + VECTOR2{ 0, down });
			c.y = c.z = 0;
		}


		text->setColor(c);

		if (c.w <= 0.0f)
			it = texts.erase(it);
		else
			it++;
	}
}
void textUI::textRender(CAMERA& camera, std::string coin)
{
	text_out(3, coin, pos.x - camera.getPos().x, pos.y - camera.getPos().y, scale.x, scale.y, color.x, color.y, color.z, color.w);
}

void textUI_Manager::render(CAMERA& camera)
{
	std::string textCoin;
	int TextCount = textCount();
	for (int i = 0; i < TextCount; i++)
	{
		textUI* text = getText(i);
		textCoin= std::to_string(text->getMoveCoin());

		if (text->getMoveCoin() < 0)
			text->textRender(camera, textCoin);
		else
			text->textRender(camera, "+" + textCoin);
	}

}

void textUI_Manager::Clear()
{
	texts.clear();
}