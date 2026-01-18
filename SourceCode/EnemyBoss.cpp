#include "EnemyBoss.h"
#include "ImageManager.h"
#include "HitBox.h"
#include "ProjectileManager.h"
#include "Tail.h"

EnemyBoss::EnemyBoss() :coinReward(10000), maxSpeedX(10)
{
	hp              = 2000;
	atk             = 100;
	texSize         = { 1000.0f,700.0f };
	texPos          = { 0.0f,0.0f };
	color           = { 1.0f,1.0f,1.0f,1.0f };
	scale           = { 1.0f,1.0f };
	pivot           = { texSize.x * 0.5f,texSize.y * 0.5f };
	speed           = { 0,0 };
	offset          = { 0,0 };
	act             = IDLE_INIT;
	timer           = 0;
	anime           = 0;
	animeTimer      = 0;
	anime_state     = 0;
	radius          = texSize.y * 0.5f;
	spr             = nullptr;
	invincibleTimer = 1.0f;
	direction       = { 1,0 };
	attackType = -1;
	mellePos = { 0,0 };
	melleRadius = 0;
	isTargetRemoveOn = false;
	animeCount = 0;

	//sprTail = nullptr;
}

EnemyBoss::EnemyBoss(VECTOR2 Pos) :coinReward(10000),maxSpeedX(10)
{
	hp              = 2000;
	atk             = 100;
	texSize         = { 1000.0f,700.0f };
	texPos          = { 0.0f,0.0f };
	pos             = { 1000,700 };
	color           = { 1.0f,1.0f,1.0f,1.0f };
	pivot           = { texSize.x * 0.5f,texSize.y * 0.5f };
	speed           = { 0,0 };
	offset          = { 0,0 };
	pos             = Pos;
	act             = IDLE_INIT;
	timer           = 0;
	anime           = 0;
	animeTimer      = 0;
	anime_state     = 0;
	radius          = texSize.y * 0.5f;
	spr             = nullptr;
	invincibleTimer = 1.0f;
	direction       = { 1,0 };
	attackType = -1;
	mellePos = { 0,0 };
	melleRadius = 0;
	isTargetRemoveOn = false;
	animeCount = 0;
	//sprTail = nullptr;
}

void EnemyBoss::init()
{
	if (!spr)
		spr          = ImageManager::Instance().getSprite(ImageManager::SpriteNum::boss);

	/*if (!sprTail)
		sprTail = ImageManager::Instance().getSprite(ImageManager::SpriteNum::bossTail);*/

	hp               = 2000;
	atk              = 100;
	texSize          = { 500.0f,350.0f };
	texPos           = { 0.0f,0.0f };
	color            = { 1.0f,1.0f,1.0f,1.0f };
	scale            = { 1.5f,1.5f };
	pivot            = { texSize.x * 0.5f,texSize.y * 0.5f };
	speed            = { 0,0 };
	offset           = { 0,0 };
	act              = IDLE_INIT;
	timer            = 0;
	anime            = 0;
	animeTimer       = 0;
	anime_state      = 0;
	radius           = texSize.y * 0.3f*scale.y;
	invincibleTimer  = 1.0f;
	direction        = { 1,0 };
	pos              = { 500,360 };
	attackType       = -1;
	mellePos         = { 0,0 };
	melleRadius      = 0;
	isTargetRemoveOn = false;
	animeCount       = 0;
	//tailPos          = { 0,0 };
	//tailTexSize = { 0,0 };
	//act              = ATTACK2_INIT;
	posFlag = false;
	drawPosOffset = { 0,0 };
	isGround = false;
	isCanFlip = false;
	acceleration = false;
	//texSize = { 2600,700 };
	jumpTargetX = 0.0f;

	//texSize = { 500,350 };
	//scale = { 1.0f,1.0f };
	/*pos = { 1000,360 };
	act = ATTACK2_INIT;*/
}

void EnemyBoss::deinit()
{
	isTargetRemoveOn = true;
}

void EnemyBoss::update(CAMERA& camera, VECTOR2 targetPos)
{
	//攻撃出てない様にする
	isAttackOn       = false;
	attackType       = none;
	isTargetRemoveOn = false;

	//オフセット更新
	//offset = { -fabsf(50) * direction.x,0 };

	if (posFlag&& act != ATTACK2 && act != ATTACK2_INIT)
	{
		drawPosOffset = { 0,0 };
		posFlag = false;
	}

	if (isSprChange)
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::boss);
		texSize = { 500.0f,350.0f };
		isSprChange = false;
	}

	//状態遷移
	state(targetPos);

	//無敵時間更新
	invincibleTimerUpdate();

	//画面外に出た場合移動
	if (act == IDLE||act==WALK)
		moveHorizontalInCamera(camera);

	// 速度制限
	if (act != ATTACK1)
	{
		if (speed.x > maxSpeedX) speed.x = maxSpeedX;
		if (speed.x < -maxSpeedX) speed.x = -maxSpeedX;
	}
	
	//摩擦
	if(ATTACK1!=act||!isGround)
		friction(this);

	//重力
	if(!isGround)
		gravity(this, { 0,1.3f });

	//位置に速度足す
	pos += speed;

	//地面判定		120は補正の数字
	if (pos.y > GROUND_Y - pivot.y*scale.y+100)
	{
		pos.y = GROUND_Y - pivot.y * scale.y + 100;
		speed.y = 0;
		isGround = true;
	}

	//スケール反転
	if(isCanFlip)
	ScaleReverse(targetPos);

	//死んだら破棄
	if (isDeath())
	{
		Destroy();
	}
	debug::setString("Pos,state,DrawOFFset:%f:%f:%d", pos.x, pos.y,act);
	debug::setString("DrawOFFset:%f:%f", drawPosOffset.x,drawPosOffset.y);
}

void EnemyBoss::state(VECTOR2 targetPos)
{
	//モーションないからanimieUpdateのなかとか適当　超仮
	switch (act)
	{
	case IDLE_INIT:
		anime_state = 0;
		drawPosOffset.y -= 50;
		animeCount = 0;
		isCanFlip = true;
		act = IDLE;

	case IDLE:
		//2段アニメーション
		if (!animeCount)
		{
			if (animeUpdate(7, 14, 6, true))
			{
				animeCount++;
				anime_state = 0;
			}
		}	
		else
			if (animeUpdate(8, 1, 6, true))		
			{
				animeCount = 0;
				anime_state = 0;
				posFlag = true;
				decideAttack();
				//act = ATTACK1_INIT;	//仮
				isCanFlip = false;
			}

		//いったんなし
		if (fabsf(speed.x) > 3.0f)
		{
			posFlag = true;
			act = WALK_INIT;
			isCanFlip = false;
		}
		break;

	case WALK_INIT:
		anime_state = 0;
		acceleration = direction.x * 6.5f;
		act = WALK;

	case WALK:
	{
		//移動
		speed.x = acceleration;

		if (animeUpdate(9, 11, 6, true)&&!moveInCamera)
		{
			speed.x = 0;
			decideAttack();
		}

		if (fabsf(speed.x) <= 0.6f)
		{
			act=IDLE_INIT;
		}
		break;
	}
	case ATTACK1_INIT:
	{
		anime_state = 0;
		animeCount = 0;

		// case2 で速度を決めるので、ここでは止めておく
		speed.x = 0.0f;
		isCanFlip = true;
		
		drawPosOffset = { 100 * direction.x,0 };

		act = ATTACK1;
	}
	case ATTACK1:
	{
		switch (animeCount)
		{	//とびかかり１段目
		case 0:
			if (animeUpdate(0, 14, 6, true))
			{
				animeCount++;
				anime_state = 0;
			}
			break;
			//とびかかり２段目
		case 1:

			//一回だけ
			if (animeTimer == 0)
			{
				isCanFlip = false;
				// プレイヤーの前に着地させる
				const float FRONT_OFFSET = 400.0f;
				jumpTargetX = targetPos.x - (FRONT_OFFSET * direction.x);

				const int CASE2_ATTACK_FRAME = 8 * 6;
				float dx = jumpTargetX - pos.x;
				speed.x = dx / CASE2_ATTACK_FRAME;
			}

			if (animeUpdate(1, 2, 6, true))
			{
				isGround = false;
				animeCount++;
				anime_state = 0;
			}
			break;
			//とびかかり発生
		case 2:

			if (animeUpdate(2, 11, 6, true))
			{
				isTargetRemoveOn = true;
				act = FALL_INIT;
			}

			//攻撃発生
			if (animeTimer == 8 * 6)
			{
				speed.x = 0;
				mellePos = { pos.x + (200 * direction.x),pos.y - 100 };
				isAttackOn = true;	//球発射
				attackType = melle;
			}
			break;
		}

		break;
	}
	case FALL_INIT:
		anime_state = 0;
		act = FALL;

	case FALL:
		//接地しているかどうかの条件も後で追加する
		if (animeUpdate(3, 4, 6, false)&&isGround)
		{
			act = LANDING_INIT;
		}

		break;

	case LANDING_INIT:
		anime_state = 0;
		act = LANDING;

	case LANDING:
		if (animeUpdate(4, 4, 6, false))
		{
			if (rand() % 2)
				decideAttack();
			else
				act = ATTACK2_INIT;
		}

		break;

	case ATTACK2_INIT:
		anime_state = 0;
		animeCount = 0;
		texSize = { 1300.0f,350.0f };
		drawPosOffset = { 1200.0f * direction.x,0 };
		scale.x = fabsf(scale.x)* - direction.x;
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::bossTail);
		act = ATTACK2;
		//break;

	case ATTACK2:
	{
		//尻尾のやり方変えるのでコメントにしておく　いらなくなったら消す
		//constexpr float tailPlusNum = 25;
		switch (animeCount)
		{	//しっぽ１段目
		case 0:
		{
			if (animeUpdate(0, 2, 6, false))
			{
				animeCount++;
				anime_state = 0;
			}

			//const int TAIL_SEG = 10;
			//const float SEG_LEN = 50.0f;
			//for (int i = 0;i < TAIL_SEG;i++)
			//{
			//	if (animeTimer == 6 * 7)
			//	{
			//		
			//		TailHitCircle* c=new TailHitCircle(
			//			&ProjectileManager::Instance(),
			//			10,						//damage
			//			Projectile::kinds::enemy,
			//			0.3f,					//lifeLimit
			//			sprTail,				//使う画像
			//			{ 30,30 },				//TEX_SIZE
			//			{ -1.5f,1.5f },					//Scale
			//			{ 0,0 },					//Speed
			//			25*1.5f,					//radius
			//			this,					//owner
			//			{ (i + 1) * SEG_LEN,-100 },			//offset
			//			16.0f
			//		);
			//	}
			//}
			/*if (animeTimer == 6 * 12)
			{
				sprTail = ImageManager::Instance().getSprite(ImageManager::SpriteNum::bossTail);
				tailPos = { pos.x+(250*direction.x),pos.y - 75};
				tailTexSize = { 80,50 };
			}*/

			break;
		}
			//しっぽ２段目
		case 1:
			if (animeUpdate(2, 1, 6, false))
			{
				animeCount++;
				anime_state = 0;
				//sprTail = nullptr;
				//act = ATTACK2_INIT;
			}
			break;

		case 2:
			if (animeUpdate(3, 2, 6, false))
			{
				animeCount++;
				anime_state = 0;
			}
			break;
		case 3:
			if (animeUpdate(4, 2, 6, false))
			{
				animeCount++;
				anime_state = 0;
			}
			break;

		case 4:
			if (animeUpdate(5, 2, 6, false))
			{
				animeCount++;
				anime_state = 0;
			}
			break;

		case 5:
			if (animeUpdate(6, 2, 6, false))
			{
				animeCount++;
				anime_state = 0;
			}
			break;

		case 6:
			if (animeUpdate(7, 2, 6, false))
			{
				animeCount++;
				anime_state = 0;
			}
			break;

		case 7:
			if (animeUpdate(8, 2, 6, false))
			{
				//texSize = { 500.0f,350.0f };
				posFlag = true;
				isSprChange = true;
				//act = ATTACK2_INIT;		//デバッグ用
				decideAttack();
			}
			break;
		}

		////尻尾のアップデート
		//if (sprTail&&animeTimer%6==0)
		//{
		//	tailPos.x += (tailPlusNum * direction.x);
		//	tailTexSize.x += tailPlusNum;
		//}

		break;
	}
	case JUMP_INIT:
		anime_state = 0;
		animeCount = 0;
		//ボスジャンプの画像
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::bossJump);
		act = JUMP;

	case JUMP:
		switch (animeCount)
		{
		case 0:
			if (animeUpdate(0, 14, 6, true))
			{
				animeCount++;
				anime_state = 0;
			}
				
			break;

		case 1:
			speed.y = -50;
			if (animeUpdate(1, 1, 6, true))
			{
				spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::boss);
				isGround = false;
				animeCount = 0;
				act = FALL_INIT;
			}
		}

		break;

	/*case ATTACK4_INIT:
		anime_state = 0;
		act = ATTACK2;

	case ATTACK4:

		break;*/
		
	}
	/*switch(animeCount)
	{
	case 0:
		if (animeUpdate(0, 4, 6, false))
			animeCount++;
		break;
	case 1:
		if (animeUpdate(1, 4, 6, false))
			animeCount++;
		break;
	case 2:
		if (animeUpdate(2, 4, 6, false))
			animeCount++;
		break;
	case 3:
		if (animeUpdate(3, 4, 6, false))
			animeCount++;
		break;
	case 4:
		if (animeUpdate(4, 4, 6, false))
			animeCount++;
		break;
	case 5:
		if (animeUpdate(5, 4, 6, false))
			animeCount++;
		break;*/
	//}
}

void EnemyBoss::decideAttack()
{
	if (act == WALK || act == ATTACK2 || act == ATTACK1)
	{
		act = IDLE_INIT;
		return;
	}

	int r = rand() % 150;
	if (r < 40)
		act = WALK_INIT;
	else if (r < 70)
		act = ATTACK1_INIT;
	else if (r < 100)
		act = ATTACK2_INIT;
	else if (r < 150)
		act = JUMP_INIT;

}

//尻尾も描画したいので
void EnemyBoss::cameraRender(CAMERA& camera)
{
	VECTOR2 drawPos = pos;
	drawPos += drawPosOffset;

	sprite_render(
		spr.get(),
		drawPos.x - camera.getPos().x,
		drawPos.y - camera.getPos().y,
		scale.x, scale.y,
		texPos.x, texPos.y,
		texSize.x, texSize.y,
		pivot.x, pivot.y,
		angle,
		color.x, color.y, color.z, color.w
	);
	//VECTOR2 scale = {-direction.x,1.0f};	//元が左向きなので-
	//if(sprTail)
	//sprite_render(sprTail.get(), tailPos.x-camera.getPos().x, tailPos.y-camera.getPos().y, scale.x, scale.y, 0, 0, tailTexSize.x, tailTexSize.y,0,25,ToRadian(0),1,1,1,1);
}