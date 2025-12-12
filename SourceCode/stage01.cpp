#include "stage.h"


void Stage01::init()
{
	//îwåiÅiÉOÉâÉfÅ[ÉVÉáÉìÅj
	back.spr = std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load(L"./Data/Images/back.png"));
	back.pos = { 0,0 };
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

	//âìÅXîwåi
	back_back.spr = std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load(L"./Data/Images/back-back.png"));
	back_back.pos = { 0,0 };
	back_back.scale = { 1,1 };
	back_back.texPos = { 0,0 };
	back_back.texSize = { 2560, 720 };
	back_back.pivot = { 0,0 };
	back_back.color = { 1,1,1,1 };
	back_back.speed = { 0,0 };
	back_back.offset = { 0,0 };
	back_back.angle = 0;
	back_back.act = 0;
	back_back.timer = 0;
	back_back.anime = 0;
	back_back.animeTimer = 0;
	back_back.anime_state = 0;
	back_back.radius = 0;

	//íÜîwåi
	middle.spr = std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load(L"./Data/Images/back-middle.png"));
	middle.pos = { 0,0 };
	middle.scale = { 1,1 };
	middle.texPos = { 0,0 };
	middle.texSize = { 2560, 720 };
	middle.pivot = { 0,0 };
	middle.color = { 1,1,1,1 };
	middle.speed = { 0,0 };
	middle.offset = { 0,0 };
	middle.angle = 0;
	middle.act = 0;
	middle.timer = 0;
	middle.anime = 0;
	middle.animeTimer = 0;
	middle.anime_state = 0;
	middle.radius = 0;

	//ãﬂîwåi
	front.spr = std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load(L"./Data/Images/back-front.png"));
	front.pos = { 0,0 };
	front.scale = { 1,1 };
	front.texPos = { 0,0 };
	front.texSize = { 2560, 720 };
	front.pivot = { 0,0 };
	front.color = { 1,1,1,1 };
	front.speed = { 0,0 };
	front.offset = { 0,0 };
	front.angle = 0;
	front.act = 0;
	front.timer = 0;
	front.anime = 0;
	front.animeTimer = 0;
	front.anime_state = 0;
	front.radius = 0;


	//ínñ 
	ground.spr = std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load(L"./Data/Images/ground.png"));
	ground.pos = { 0,0 };
	ground.scale = { 1,1 };
	ground.texPos = { 0,0 };
	ground.texSize = { 1280, 720 };
	ground.pivot = { 0,0 };
	ground.color = { 1,1,1,1 };
	ground.speed = { 0,0 };
	ground.offset = { 0,0 };
	ground.angle = 0;
	ground.act = 0;
	ground.timer = 0;
	ground.anime = 0;
	ground.animeTimer = 0;
	ground.anime_state = 0;
	ground.radius = 0;

}


void Stage01::update()
{
	back_back.pos.x += -0.1f;
	middle.pos.x += -0.5f;
	front.pos.x += -0.7f;
}

void Stage01::deinit()
{

}

void Stage01::render()
{
	setBlendMode(Blender::BS_ALPHA);	
	back.render();
	back_back.render();
	middle.render();
	front.render();
	ground.render();
}