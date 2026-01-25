#include "SceneEvent.h"
#include"ImageManager.h"

bool flag = false;

void SceneEvent::init()
{
	state = 0;
}

void SceneEvent::update()
{
	switch (state)
	{
	case 0:
		if (resetMap)
			flag = false;
		setBlendMode(Blender::BS_ALPHA);

		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::EventBack);

		int n;
		flag ? n=5 : n=4;
		switch (rand() % n)
		{
		case 0:
			event = std::make_unique<Events>();
			break;

		case 1:
			event = std::make_unique<Event2>();
			break;

		case 2:
			event = std::make_unique<Event3>();
			break;

		case 3:
			event = std::make_unique<Event4>();
			break;

		case 4:
			event = std::make_unique<Event5>();
			break;
		}
		
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
