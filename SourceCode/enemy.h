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
    bool isTargetRemoveOn = false;  //自分を参照しているターゲットを全て消す
    VECTOR2 hitPos;
    int attackType = -1;
    int exitRnd;
    bool isDeathOn;
    
public:
    enum ATTACK_TYPE
    {
        none=-1,
        bulet,
        melle
    };
    Enemy();
    Enemy(VECTOR2 Pos);
    virtual ~Enemy(){}
    virtual void init()override;
    virtual void deinit()override;
    virtual void update(CAMERA& camera, VECTOR2 targetPos);
    virtual void state();
    int getCoinReward()const { return coinReward; }
    bool isDeath()override { return isDeathOn; }
    void degHp(int damage) { hp += -damage; }
    int getHp()const { return hp; }
    bool getIsAttackOn() { return isAttackOn; }
    int getAttackType() { return attackType; }
    bool getIsTargetRemoveOn() { return isTargetRemoveOn; }
    void moveHorizontalInCamera(CAMERA& camera);
    void Destroy();
    void setHitFlag(bool b) { isHitOn = b; }
     
    virtual void ScaleReverse(VECTOR2 target);   //必要ないときは{}でoverride
    VECTOR2 shotDir(VECTOR2 targetPos);//発射方向
};
