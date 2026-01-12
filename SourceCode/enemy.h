#pragma once
#include "../GameLib/game_lib.h"
#include "Character.h"
class Enemy :
    public Character
{
private:
    enum STATE
    {
        IDLE_INIT,
        IDLE,
        ATTACK1_INIT,
        ATTACK1,
        WALK_INIT,
        WALK,
    };

    const float maxSpeedX;
    const int   coinReward;   //撃破時のコイン
    bool gravityOn = false;     //重量を呼ぶかどうか

protected:
    int hp = 100;
    bool moveInCamera;      //カメラの中に入ろうとする動きの条件
    bool isAttackOn=false;  //攻撃するか
    bool isHitOn = false;   //trueで被弾
    VECTOR2 hitPos;
    
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
    void setHitFlag(bool b) { isHitOn = b; }
     
    virtual void ScaleReverse(VECTOR2 target);   //必要ないときは{}でoverride
    VECTOR2 shotDir(VECTOR2 targetPos);//発射方向
};
