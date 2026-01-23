#pragma once
#include "enemy.h"
class EnemySlip : public Enemy
{
private:
	enum
	{
		WALK_INIT,
		WALK,
		ATTACK_INIT,
		ATTACK,
		SLIP_INIT,
		SLIP,
	};
	const float maxSpeedX = 10.0f;
	VECTOR2 targetPos = { 0.0f,0.0f };
	float addSpeed = 0;;
	bool isHitMotionOn = false;
	int attackTimer = 0;
public:
	EnemySlip();
	EnemySlip(VECTOR2 pos);
	void init()override;
	void update(CAMERA& camera, VECTOR2 targetPos)override;
    void deinit()override;
	void state()override;
};

