#pragma once
#include "../GameLib/game_lib.h"
#include "Character.h"
class Enemy :
    public Character
{
private:
    int hp = 100;
    const float maxSpeedX;
    const int coinReward;   //撃破時のコイン
    bool moveInCamera;      //カメラの中に入ろうとする動きの条件
    bool isAttackOn=false;        //攻撃するか
    enum STATE
    {
        IDLE_INIT,
        IDLE,
        ATTACK1_INIT,
        ATTACK1,
        WALK_INIT,
        WALK,
    };
public:
    Enemy();
    Enemy(VECTOR2 Pos);
    virtual void init()override;
    virtual void deinit()override;
    virtual void update(CAMERA& camera, VECTOR2 targetPos);
    virtual void state();
    int getCoinReward()const { return coinReward; }
    bool isDeath()override { return (hp <= 0); }
    void degHp(int damage) { hp += -damage; }
    int getHp()const { return hp; }
    bool getIsAttackOn() { return isAttackOn; }
    void moveHorizontalInCamera(CAMERA& camera);
    void Destroy();
    virtual void ScaleReverse(VECTOR2 target);   //必要ないときは{}でoverride
    VECTOR2 shotDir(VECTOR2 targetPos);//発射方向
};

