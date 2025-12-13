#include"SceneGame.h"
#include"../GameLib/game_lib.h"

void SceneGame::init()
{
	state = 0;
	frame = 0;
	timer = 0;
}

void SceneGame::update()
{
	switch (state)
	{
	case 0:
		state++;

	case 1:
		setBlendMode(Blender::BS_ALPHA);
		state++;

	case 2:

		//éûä‘åvéZÅiïbÅj
		frame++;
		if (frame % 60 == 0)
			timer++;

		debug::setString("time:%d", timer);
		break;
	}
}

void SceneGame::render()
{
	GameLib::clear(1, 0, 1);


}


void SceneGame::deinit()
{

}

void SceneGame::deleteSprite()
{

}