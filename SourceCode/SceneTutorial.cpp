#include "SceneTutorial.h"
#include "ImageManager.h"
#include "audio.h"

void SceneTutorial::update()
{
	if (!loopCount)
	{
		if (buttonCount > 4)
		{
			texPos.x = 0.0f;
			buttonCount = 0;
			loopCount++;
		}
	}
	else
		if (buttonCount > 3)
		{
			nextScene = SCENE_TITLE;
		}
	if (TRG(0) & PAD_START)
	{
		music::play(tranpFly);
		buttonCount++;
	}
	texPos = { 1280.0f * buttonCount,720.0f * loopCount };
}

void SceneTutorial::render()
{
	sprite_render(spr.get(), 0.0f, 0.0f,
		1.0f, 1.0f,
		texPos.x, texPos.y,
		1280.0f, 720.f,
		0.0f, 0.0f,
		0.0f,
		1.0f, 1.0f, 1.0f, 1.0f);
}

void SceneTutorial::init()
{
	spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::tutorial);	
	texPos = { 0.0f,0.0f };
	buttonCount = 0;
	loopCount = 0;
}

void SceneTutorial::deinit()
{

}

void SceneTutorial::deleteSprite()
{

}