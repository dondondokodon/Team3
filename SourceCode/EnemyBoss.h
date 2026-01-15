#pragma once
#include "Enemy.h"

class EnemyBoss :
    public Enemy
{
private:
    const float maxSpeedX;
    const int   coinReward;   //撃破時のコイン
    int animeCount=0;         //アニメが２段あるのに対応するため

    enum STATE
    {
        IDLE_INIT,
        IDLE,
        WALK_INIT,
        WALK,

        ATTACK1_INIT,
        ATTACK1,
        FALL_INIT,
        FALL,
        LANDING_INIT,
        LANDING,

        ATTACK2_INIT,
        ATTACK2,
        ATTACK3_INIT,
        ATTACK3,
        ATTACK4_INIT,
        ATTACK4,
       
    };

public:
    EnemyBoss();
    EnemyBoss(VECTOR2 Pos);
    void init()override;
    void deinit()override;
    void update(CAMERA& camera,VECTOR2 targetPos)override;
    void state()override;
};

