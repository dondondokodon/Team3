#pragma once
#include "Enemy.h"
#include <memory>
#include "Tail.h"
class EnemyBoss :
    public Enemy
{
private:
    const float maxSpeedX;
    const int   coinReward;   //撃破時のコイン
    int animeCount=0;         //アニメが２段あるのに対応するため
    VECTOR2 jumpTarget;
    bool isCanFlip;           //反転していいか（スケールリバース）
    bool isSprChange;         //画像差し替えのタイミング
    bool isGravityOn;
    //std::shared_ptr<Sprite> sprJump;    //ジャンプ
    bool posFlag;              //高さを画像に合わせるためのフラグ
    VECTOR2 drawPosOffset;           //描画だけ変える
    std::shared_ptr<AttackContext> ac;                //尻尾の攻撃の当たり判定の弾で使う
    float gravityScale;
    //std::shared_ptr<Sprite> sprTail;    //尻尾の画像
    //std::unique_ptr<Character> tails;   //尻尾当たり判定付き
   // VECTOR2 tailPos;
   // VECTOR2 tailTexSize;
    static constexpr int TailMAX=5;
    Tail tails[TailMAX];                          //ウルト用の尻尾
    float meleeRadius;

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
        DEATH_INIT,
        DEATH
    };

public:
    EnemyBoss();
    EnemyBoss(VECTOR2 Pos);
    ~EnemyBoss();
    void init()override;
    void deinit()override;
    void update(CAMERA& camera,VECTOR2 targetPos)override;
    void state(VECTOR2 targetPos);
    void decideAttack();
    void cameraRender(CAMERA& camera)override;
    float getMelleRadius() { return meleeRadius; }
    HitWall getHitWall()const { return hitWall; }
};

