#include "stage.h"
#include"ImageManager.h"


void Stage02::init()
{
	//îwåiÅiÉOÉâÉfÅ[ÉVÉáÉìÅj
	back.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::casinoBack);
	back.pos = { 0,0 };
	back.scale = { 1,1 };
	back.texPos = { 0,0 };
	back.texSize = { 3840, 720 };
	back.pivot = { 0,0 };
	back.color = { 1,1,1,1 };
	back.speed = { 0.6,0.3 };
	back.offset = { 0,0 };
	back.angle = 0;
	back.act = 0;
	back.timer = 0;
	back.anime = 0;
	back.animeTimer = 0;
	back.anime_state = 0;
	back.radius = 0;

	////âìÅXîwåi
	//back_back.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::billBackBack);
	//back_back.pos = { 0,0 };
	//back_back.scale = { 1,1 };
	//back_back.texPos = { 0,0 };
	//back_back.texSize = { 2560, 720 };
	//back_back.pivot = { 0,0 };
	//back_back.color = { 1,1,1,1 };
	//back_back.speed = { 0,0 };
	//back_back.offset = { 0,0 };
	//back_back.angle = 0;
	//back_back.act = 0;
	//back_back.timer = 0;
	//back_back.anime = 0;
	//back_back.animeTimer = 0;
	//back_back.anime_state = 0;
	//back_back.radius = 0;

	//íÜîwåi
	middle.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::casinoMiddle);
	middle.pos = { 0,0 };
	middle.scale = { 1,1 };
	middle.texPos = { 0,0 };
	middle.texSize = { 3840, 720 };
	middle.pivot = { 0,0 };
	middle.color = { 1,1,1,1 };
	middle.speed = { 0.8,0.4 };
	middle.offset = { 0,0 };
	middle.angle = 0;
	middle.act = 0;
	middle.timer = 0;
	middle.anime = 0;
	middle.animeTimer = 0;
	middle.anime_state = 0;
	middle.radius = 0;


	//ñæÇ©ÇË
	Light1.init(VECTOR2{ 485, 200 });
	Light2.init(VECTOR2{ 1215, 200 });
	Light3.init(VECTOR2{ 2015, 200 });

	//ãﬂîwåi
	front.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::casinoFront);
	front.pos = { 0,0 };
	front.scale = { 1,1 };
	front.texPos = { 0,0 };
	front.texSize = { 3840, 720 };
	front.pivot = { 0,0 };
	front.color = { 1,1,1,1 };
	front.speed = { 1,0.5 };
	front.offset = { 0,0 };
	front.angle = 0;
	front.act = 0;
	front.timer = 0;
	front.anime = 0;
	front.animeTimer = 0;
	front.anime_state = 0;
	front.radius = 0;


	////ínñ 
	//ground.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::billGround);
	//ground.pos = { 0,0 };
	//ground.scale = { 1,1 };
	//ground.texPos = { 0,0 };
	//ground.texSize = { 1280, 720 };
	//ground.pivot = { 0,0 };
	//ground.color = { 1,1,1,1 };
	//ground.speed = { 0,0 };
	//ground.offset = { 0,0 };
	//ground.angle = 0;
	//ground.act = 0;
	//ground.timer = 0;
	//ground.anime = 0;
	//ground.animeTimer = 0;
	//ground.anime_state = 0;
	//ground.radius = 0;

	//ë´èÍ
	footings.clear();	//àÍâûÉNÉäÉA

	for (int i = 0;i < 3;i++)
	{
		StageLayer f;
		f.spr         = ImageManager::Instance().getSprite(ImageManager::SpriteNum::footing);
		f.pos         = { 300+ i * 1000.0f,500.0f };
		f.scale       = { 1,1 };
		f.texPos      = { 0,0 };
		f.texSize     = { 240, 50 };
		f.pivot       = { f.texSize.x * 0.5f,f.texSize.y * 0.5f };
		f.color       = { 1,1,1,1 };
		f.speed       = { 1,1 };
		f.offset      = { 0,0 };
		f.angle       = 0;
		f.act         = 0;
		f.timer       = 0;
		f.anime       = 0;
		f.animeTimer  = 0;
		f.anime_state = 0;
		f.radius      = 0;
		footings.push_back(f);
	}
}

void light::update()
{

}
void light::init(VECTOR2 pos)
{
	for (int i = 0; i < 4; i++)
	{
		lamp[i].spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::casinoLnthanum);
		lamp[i].pos = pos;
		lamp[i].scale = { 1,1 };
		lamp[i].texPos = { 0,0 };
		lamp[i].texSize = { 689,481 };
		lamp[i].pivot = { lamp[i].texSize.x * 0.5f,lamp[i].texSize.y * 0.5f };
		lamp[i].color = { 1,1,1,0.3 };
		lamp[i].speed = { 0.6,0.3 };
		lamp[i].offset = { 0,0 };
		lamp[i].angle = 0;
	}

	lamp[1].pos.x = lamp[0].pos.x + 10;
	lamp[2].pos = lamp[0].pos + VECTOR2{-10,20};
	lamp[3].pos = lamp[0].pos + VECTOR2{ 20,20 };

	lamp[2].color.w = lamp[3].color.w = lamp[0].color.w - 0.15f;
	lamp[1].color.w = lamp[3].color.w;
}

void light::render(CAMERA& camera)
{
	for (int i = 0; i < 4; i ++)
	{
		sprite_render(lamp[i].spr.get(), lamp[i].pos.x - camera.getPos().x * lamp[i].speed.x, lamp[i].pos.y - camera.getPos().y * lamp[i].speed.y, lamp[i].scale.x, lamp[i].scale.y, lamp[i].texPos.x, lamp[i].texPos.y, lamp[i].texSize.x, lamp[i].texSize.y, lamp[i].pivot.x, lamp[i].pivot.y, lamp[i].angle, lamp[i].color.x, lamp[i].color.y, lamp[i].color.z, lamp[i].color.w);
	}
}

void Stage02::update()
{
	//back_back.pos.x += -0.1f;
	//middle.pos.x += -0.5f;
	//front.pos.x += -0.7f;
}

void Stage02::deinit()
{
	footings.clear();
}

void Stage02::render()
{
	GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);
	back.render();
	//back_back.render();
	middle.render();
	front.render();
	//ground.render();
}

void Stage02::cameraRender(CAMERA camera)
{
	GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);
	back.cameraRender(camera);
	//back_back.cameraRender(camera);
	GameLib::setBlendMode(GameLib::Blender::BS_ADD);
	Light1.render(camera);
	Light2.render(camera);
	Light3.render(camera);
	GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);
	middle.cameraRender(camera);
	front.cameraRender(camera);
	GameLib::setBlendMode(GameLib::Blender::BS_ADD);
	primitive::rect(0, 0, 1280, 720, 0, 0, 0, 0, 0, 0, 0.7);
	GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);
	for (auto& footing : footings)
		footing.cameraRender(camera);
	//ground.cameraRender(camera);
}