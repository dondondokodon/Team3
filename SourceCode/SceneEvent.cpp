#include "SceneEvent.h"
#include"ImageManager.h"


void SceneEvent::init()
{
	state = 0;
}

void SceneEvent::update()
{
	switch (state)
	{
	case 0:
		setBlendMode(Blender::BS_ALPHA);

		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::EventBack);
		event = std::make_unique<Events>();
		state++;

	case 1:
		event->init();
		state++;

	case 2:

		if(event->update())	nextScene = SCENE_MAP;

		debug::setString("event");
		break;
	}
}

void SceneEvent::render()
{
	GameLib::clear(0, 0.5, 0.5);
	//”wŒi
	sprite_render(spr.get(), 0, 0, 1, 1, 0, 0, 1280, 720, 0, 0, 0, 1, 1, 1, 1);

	event->render();
}


void SceneEvent::deinit()
{

}
