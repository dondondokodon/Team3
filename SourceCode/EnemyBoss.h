#pragma once
#include "Enemy.h"
#include <memory>

class EnemyBoss :
    public Enemy
{
private:
    const float maxSpeedX;
    const int   coinReward;   //撃破時のコイン
    int animeCount=0;         //アニメが２段あるのに対応するため
    float jumpTargetX;
    //std::shared_ptr<Sprite> sprJump;    //ジャンプ
   // bool posYFlag;              //高さを画像に合わせるためのフラグ
   // float drawPosYOffset;           //描画だけ変える
    //std::shared_ptr<Sprite> sprTail;    //尻尾の画像
    //std::unique_ptr<Character> tails;   //尻尾当たり判定付き
   // VECTOR2 tailPos;
   // VECTOR2 tailTexSize;

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
        JUMP_INIT,
        JUMP,
        ATTACK4_INIT,
        ATTACK4,
       
    };

public:
    EnemyBoss();
    EnemyBoss(VECTOR2 Pos);
    void init()override;
    void deinit()override;
    void update(CAMERA& camera,VECTOR2 targetPos)override;
    void state(VECTOR2 targetPos);
    void decideAttack();
   // void cameraRender(CAMERA& camera)override;
};

