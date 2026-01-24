#include "stage.h"
#include"ImageManager.h"


void Stage01::init()
{
	//îwåiÅiÉOÉâÉfÅ[ÉVÉáÉìÅj
	back.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::billBack);
	back.pos = { 0,0 };
	back.scale = { 1,1 };
	back.texPos = { 0,0 };
	back.texSize = { 1280 * 2, 720 };
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
	back_back.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::billBackBack);
	back_back.pos = { 0,100 };
	back_back.scale = { 1,1 };
	back_back.texPos = { 0,0 };
	back_back.texSize = { 2560 * 2, 720 };
	back_back.pivot = { 0,0 };
	back_back.color = { 1,1,1,1 };
	back_back.speed = { 0.1,0.1 };
	back_back.offset = { 0,0 };
	back_back.angle = 0;
	back_back.act = 0;
	back_back.timer = 0;
	back_back.anime = 0;
	back_back.animeTimer = 0;
	back_back.anime_state = 0;
	back_back.radius = 0;

	//íÜîwåi
	middle.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::billMiddle);
	middle.pos = { 0,100 };
	middle.scale = { 1,1 };
	middle.texPos = { 0,0 };
	middle.texSize = { 2560 * 2, 720 };
	middle.pivot = { 0,0 };
	middle.color = { 1,1,1,1 };
	middle.speed = { 0.3,0.3 };
	middle.offset = { 0,0 };
	middle.angle = 0;
	middle.act = 0;
	middle.timer = 0;
	middle.anime = 0;
	middle.animeTimer = 0;
	middle.anime_state = 0;
	middle.radius = 0;

	//ãﬂîwåi
	front.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::billFront);
	front.pos = { 0,0 };
	front.scale = { 1,1 };
	front.texPos = { 0,0 };
	front.texSize = { 2560 * 2, 720 };
	front.pivot = { 0,0 };
	front.color = { 1,1,1,1 };
	front.speed = { 0.5,0.5 };
	front.offset = { 0,0 };
	front.angle = 0;
	front.act = 0;
	front.timer = 0;
	front.anime = 0;
	front.animeTimer = 0;
	front.anime_state = 0;
	front.radius = 0;


	//ínñ 
	ground.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::billGround);
	ground.pos = { 0,0 };
	ground.scale = { 1,1 };
	ground.texPos = { 0,0 };
	ground.texSize = { 1280 * 2+300, 720 };
	ground.pivot = { 0,0 };
	ground.color = { 1,1,1,1 };
	ground.speed = { 1,0.5 };
	ground.offset = { 0,0 };
	ground.angle = 0;
	ground.act = 0;
	ground.timer = 0;
	ground.anime = 0;
	ground.animeTimer = 0;
	ground.anime_state = 0;
	ground.radius = 0;

	//ë´èÍ
	footing.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::footing);
	footing.pos = { 500,500 };
	footing.scale = { 1,1 };
	footing.texPos = { 0,0 };
	footing.texSize = { 240, 50 };
	footing.pivot = { 0,0 };
	footing.color = { 1,1,1,1 };
	footing.speed = { 1,1 };
	footing.offset = { 0,0 };
	footing.angle = 0;
	footing.act = 0;
	footing.timer = 0;
	footing.anime = 0;
	footing.animeTimer = 0;
	footing.anime_state = 0;
	footing.radius = 0;

}


void Stage01::update()
{
	back.pos.x += -0.2f;
	//middle.pos.x += -0.5f;
	//front.pos.x += -0.7f;

	if (back.pos.x <= -1280)
		back.pos.x = 0;
}

void Stage01::deinit()
{

}

//ÉXÉeÅ[ÉWÇÃrenderÇPÇ‡ÇQÇ‡égÇ¡ÇƒÇ÷ÇÒ
void Stage01::render()
{
	GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);	
	//back.render();
	//back_back.render();
	//middle.render();
	//front.render();
	//ground.render();
}

void Stage01::cameraRender(CAMERA camera)
{
	GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);
	back.render();
	back_back.cameraRender(camera);
	middle.cameraRender(camera);
	front. cameraRender(camera);
	ground.cameraRender(camera);
	//primitive::rect(0, 0, 1280, 40, 0, 0, 0, 0, 0, 0,1);
	//primitive::rect(0, 680, 1280, 40, 0, 0, 0, 0, 0, 0,1);
	//footing.cameraRender(camera);	//Ç±Ç¢Ç¬Ç…ìñÇΩÇËîªíËÇÇ¬ÇØÇ»Ç¢Ç∆Ç¢ÇØÇ»Ç¢
}