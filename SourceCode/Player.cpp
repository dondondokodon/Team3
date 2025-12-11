#include "Player.h"
#include<memory>
#include "../GameLib/game_lib.h"

Player::Player()
{
	pos = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
	scale = { 1,1 };
	texPos = { 0,0 };
	texSize = { 256,256 };
	pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
	color = { 1,1,1,1 };
	speed = { 0,0 };
	offset = { 0,0 };
	angle = 0;
	spr = nullptr;
	act = 0;
	timer = 0;
	anime = 0;
	animeTimer = 0;
	anime_state = 0;
	radius = texSize.x * 0.5f;
	atk = 0;
	gold = 0;
	returnGold = 0;
}

void Player::init()
{
	pos = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
	scale = { 5,5 };
	texPos = { 0,0 };
	texSize = { 256,256 };
	pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
	color = { 1,1,1,1 };
	speed = { 0,0 };
	offset = { 0,0 };
	angle = 0;
	if(!spr)
	spr = std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load(L"./Data/Images/0_sp.png"));
	act = 0;
	timer = 0;
	anime = 0;
	animeTimer = 0;
	anime_state = 0;
	radius = texSize.x * 0.5f;
	atk = 0;
	gold = 0;
	returnGold = 0;
}

void Player::deinit()
{

}

void Player::update()
{
	static int num = 0;
	if (num % 2 == 0)
	{
		if (animeUpdate(0, 6, 8, false))
		{
			anime_state = 0;
			num++;
		}
	}
	else
	{
		if (animeUpdate(1, 5 , 8, false))
		{
			anime_state = 0;
			num++;
		}
	}
}

void Player::betCoin(int Gold,float atkMultiple, float goldMultiple)
{
	atk = Gold * atkMultiple;
	returnGold = Gold * goldMultiple;
	if (returnGold)		returnGold = 1;	//ãAÇ¡ÇƒÇ≠ÇÈêîÇ™0ÇÃéûç≈í·ï€èÿÇ≈1Ç…Ç∑ÇÈ
}