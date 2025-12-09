#include "stage.h"

//コンストラクタ
Stage01::Stage01()
{
	//背景//
	pos = {0,0 };
	scale = { 1,1 };
	texPos = { 0,0 };
	texSize = { 1920,1080 };
	pivot = { 0,0 };
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
}

//デストラクタ
Stage01::~Stage01()
{

}

void Stage01::init()
{
	//背景//
	pos = { 0,0 };
	scale = { 1,1 };
	texPos = { 0,0 };
	texSize = { 1920,1080 };
	pivot = { 0,0 };
	color = { 1,1,1,1 };
	speed = { 0,0 };
	offset = { 0,0 };
	angle = 0;
	spr = std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load(L"./Data/Images/back.png"));
	act = 0;
	timer = 0;
	anime = 0;
	animeTimer = 0;
	anime_state = 0;
	radius = texSize.x * 0.5f;

}


void Stage01::update()
{

}

void Stage01::deinit()
{

}

