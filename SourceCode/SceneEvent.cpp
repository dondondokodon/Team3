#include "SceneEvent.h"


void SceneEvent::init()
{
	state = 0;

}

void SceneEvent::update()
{
	switch (state)
	{
	case 0:
		state++;

	case 1:
		state++;

	case 2:

		if (TRG(0) & PAD_START)
		{
			nextScene = SCENE_MAP;
		}

		debug::setString("event");
		break;
	}
}

void SceneEvent::render()
{
	GameLib::clear(0, 0.5, 0.5);

}


void SceneEvent::deinit()
{

}
