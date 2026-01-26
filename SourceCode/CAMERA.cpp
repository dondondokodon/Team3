#include "CAMERA.h"
#include "common.h"
#include "Character.h"

VECTOR2 CAMERA::shakeVelocity = { 0.0f,0.0f };

CAMERA::CAMERA() :pos({0,0}),height(SCREEN_H),width(SCREEN_W)
{

}

void CAMERA::init()
{
	pos    = { 0,0 };
	height = SCREEN_H;
	width  = SCREEN_W;

	drawOffset    = { 0.0f,0.0f };
	shakeVelocity = { 0.0f,0.0f };
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
	//debug::setString(
	//	"camY=%.1f stageLimitY=%.1f height=%.1f",
	//	pos.y, stageLimitY, height
	//);

	//// ===== 揺れ処理 =====
	// その方向に移動するだけ
	//drawOffset.x += shakeVelocity.x;
	//drawOffset.y += shakeVelocity.y;

	//// 速度減衰（イージング）
	//shakeVelocity.x *= 0.9f;
	//shakeVelocity.y *= 0.9f;

	//// 元に戻す
	//drawOffset.x *= 0.9f;
	//drawOffset.y *= 0.9f;

	//// ほぼ0なら止める
	//if (fabs(drawOffset.x) < 0.01f) drawOffset.x = 0;
	//if (fabs(drawOffset.y) < 0.01f) drawOffset.y = 0;


	// バネ定数（戻ろうとする強さ）
	const float spring = 0.3f;
	// 減衰（空気抵抗）
	const float damping = 0.85f;

	// 原点に戻ろうとする力
	VECTOR2 force;
	force.x = -drawOffset.x * spring;
	force.y = -drawOffset.y * spring;

	// 速度に力を加える
	shakeVelocity.x += force.x;
	shakeVelocity.y += force.y;

	// 速度減衰
	shakeVelocity.x *= damping;
	shakeVelocity.y *= damping;

	// 位置更新
	drawOffset.x += shakeVelocity.x;
	drawOffset.y += shakeVelocity.y;

	// 微小なら止める
	if (fabs(drawOffset.x) < 0.01f) drawOffset.x = 0;
	if (fabs(drawOffset.y) < 0.01f) drawOffset.y = 0;
}