#include "CAMERA.h"
#include "common.h"
#include "Character.h"

CAMERA::CAMERA() :pos({0,0}),height(SCREEN_H),width(SCREEN_W)
{

}

void CAMERA::init()
{
	pos    = { 0,0 };
	height = SCREEN_H;
	width  = SCREEN_W;
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
	
	//プレイヤーの画面内Y座標
	float playerScreenY = target.getPos().y - pos.y;
	//上に押した
	if (playerScreenY < DEADZONE_TOP)
	{
		pos.y = target.getPos().y - DEADZONE_TOP;
	}
	else if (playerScreenY > DEADZONE_BOTTOM)
	{
		pos.y = target.getPos().y - DEADZONE_BOTTOM;
	}

	// ステージ端制限
	if (pos.x < 0)
		pos.x = 0;
	if (pos.x > stageLimitX - width)
		pos.x = stageLimitX - width;

	if (pos.y < -800)
		pos.y = -800;
	if (pos.y > stageLimitY - height)
		pos.y = stageLimitY - height;
	debug::setString(
		"camY=%.1f stageLimitY=%.1f height=%.1f",
		pos.y, stageLimitY, height
	);

}