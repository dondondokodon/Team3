#include "CAMERA.h"
#include "common.h"
#include "Character.h"

CAMERA::CAMERA() :pos({0,0}),height(SCREEN_H),width(SCREEN_W)
{

}

void CAMERA::update(Character& target)
{
	// プレイヤーの画面内X座標
	float playerScreenX = target.getPos().x - pos.x;

	// 右へ押した
	if (playerScreenX > DEADZONE_RIGHT)
	{
		pos.x = target.getPos().x - DEADZONE_RIGHT;
	}

	// 左へ押した
	if (playerScreenX < DEADZONE_LEFT)
	{
		pos.x = target.getPos().x - DEADZONE_LEFT;
	}

	// ステージ端制限
	if (pos.x < 0)
		pos.x = 0;
	if (pos.x > stageLimitX - width)
		pos.x = stageLimitX - width;
	
}