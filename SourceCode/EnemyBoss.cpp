#include "EnemyBoss.h"
#include "ImageManager.h"
#include "HitBox.h"
#include "ProjectileManager.h"
#include "Tail.h"
#include "Scene.h"
#include "audio.h"

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
	//if (!spr)
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
	radius           = texSize.y * 0.2f*scale.y;
	invincibleTimer  = 1.0f;
	direction        = { 1,0 };
	//pos              = { 500,360 };
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
	jumpTarget = {0.0f,0.0f};

	isGravityOn = true;
	ac = std::make_shared<AttackContext>();

	for (auto& tail : tails)
	tail.init();
	gravityScale = 1.3f;
	meleeRadius  = radius;
	exitRnd = 1;
	isDeathOn = false;
	

	//ここより下デバッグ用
	//texSize = { 500,350 };
	//scale = { 1.0f,1.0f };
	//pos = { 1000,360 };
	//act = ATTACK2_INIT;
	//act = ATTACK1_INIT;
}

EnemyBoss::~EnemyBoss()
{
	deinit();
}

void EnemyBoss::deinit()
{
	for (auto& tail : tails)
	tail.setDeath();
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

	if (posFlag && act != ATTACK2 && act != ATTACK2_INIT)	//これactのやつら条件に書いた意味忘れた　消してもなんも出なさそうやったら消す
	{
		drawPosOffset = { 0,0 };
		posFlag = false;
	}

	if (isSprChange && ATTACK2 != act && act != ATTACK2_INIT)		//たまに尻尾打つとき画像なくなるから試しにact条件つけてみてる
	{
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::boss);
		texSize = { 500.0f,350.0f };
		isSprChange = false;
	}

	//スケール反転
	if (isCanFlip)
		ScaleReverse(targetPos);

	//状態遷移
	state(targetPos);

	if (hp <= 0&&act!=DEATH)	act = DEATH_INIT;

	for (auto& tail : tails)
	tail.update(camera);

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
	if(ATTACK1!=act&&!isGround)
		friction(this);

	//重力
	if(!isGround&&isGravityOn)
		gravity(this, { 0,gravityScale });

	//位置に速度足す
	pos += speed;

	//当たり判定体更新
	HitWallUpdate();

	//地面判定		120は補正の数字
	if (pos.y > GROUND_Y - pivot.y*scale.y+100)
	{
		pos.y = GROUND_Y - pivot.y * scale.y + 100;
		speed.y = 0;
		isGround = true;
	}


	//死んだら破棄
	if (isDeath())
	{
		Destroy();
		//倒されたらリザルトへ
		ISCENE::nextScene = SCENE_RESULT;

	}
	debug::setString("Pos,state,DrawOFFset:%f:%f:%d", pos.x, pos.y,act);
	debug::setString("DrawOFFset:%f:%f", drawPosOffset.x,drawPosOffset.y);
	debug::setString("BossSpeed:%f", speed.x);
	debug::setString("directionX:%f", direction.x);
}

void EnemyBoss::state(VECTOR2 targetPos)
{
	//モーションないからanimieUpdateのなかとか適当　超仮
	switch (act)
	{
	case IDLE_INIT:
		anime_state = 0;
		drawPosOffset.y -= 30;
		animeCount = 0;
		isCanFlip = true;
		act = IDLE;

	case IDLE:
		//2段アニメーション
		if (!animeCount)
		{
			if (animeUpdate(5, 14, 6, true))
			{
				animeCount++;
				anime_state = 0;
			}
		}	
		else
			if (animeUpdate(6, 1, 6, true))		
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
		if (!moveInCamera)	//画面内に入ろうとしているときは無し
		acceleration = direction.x * 3.5f;
		drawPosOffset = { 0, -40.0f };		//追加した
		act = WALK;

	case WALK:
	{
		//移動
		if(!moveInCamera)	//画面内に入ろうとしているときは無し
		speed.x = acceleration;

		if (animeUpdate(7, 11, 6, true)&&!moveInCamera)
		{
			posFlag = true;
			speed.x = 0;
			decideAttack();
		}

		if (fabsf(speed.x) <= 0.6f)
		{
			posFlag = true;
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
		meleeRadius = radius + 100;
		
		drawPosOffset = { 30 * direction.x,0 };
		music::play(B_jumpA1);

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
				isGravityOn = false;
				isCanFlip = false;
				// プレイヤーの前に着地させる
				const float FRONT_OFFSET_X = 300.0f;
				jumpTarget.x = targetPos.x - (FRONT_OFFSET_X * direction.x);

				//少し上
				const float FRONT_OFFSET_Y = 250;
				jumpTarget.y = targetPos.y - (FRONT_OFFSET_Y);

				const int CASE2_ATTACK_FRAME = 8 * 6;
				float dx = jumpTarget.x - pos.x;
				speed.x = dx / CASE2_ATTACK_FRAME;

				float dy = jumpTarget.y - pos.y;
				speed.y = dy / (CASE2_ATTACK_FRAME*0.5f);
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
			if (speed.y < 0)
				speed.y += 1;
			if (speed.y > 0)	speed.y = 0.0f;

			if (animeUpdate(2, 11, 6, true))
			{
				isGravityOn = true;
				isTargetRemoveOn = true;
				act = FALL_INIT;
			}

			//攻撃発生
			if (animeTimer == 8 * 6)
			{
				speed.x = 0;
				speed.y = 0;
				
				gravityScale = 0.3f;
				mellePos = { pos.x + (150 * direction.x),pos.y};
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
		if (animeUpdate(3, 4, 3, false)&&isGround)
		{
			posFlag = true;
			act = LANDING_INIT;
		}

		break;

	case LANDING_INIT:
		anime_state = 0;
		//drawPosOffset.y = -100.0f;
		act = LANDING;

	case LANDING:
		timer++;
		animeUpdate(4, 4, 6, false);		//ここ2個飛ばしにするために２個読んでる
		if (animeUpdate(4, 4, 6, false))
		{
			gravityScale = 1.3f;
			//posFlag = true;
			isCanFlip = true;
			if (rand() % 2)
				decideAttack();
			else
				act = ATTACK2_INIT;	
				act = ATTACK2_INIT;	
		}

		break;

	case ATTACK2_INIT:
		anime_state = 0;
		animeCount = 0;
		texSize = { 1300.0f,350.0f };
		isCanFlip = false;
		drawPosOffset = { 1100.0f * direction.x,0 };
		scale.x = fabsf(scale.x)* - direction.x;
		spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::bossTail);
		music::play(B_tailA);
		act = ATTACK2;

	case ATTACK2:
	{
		switch (animeCount)
		{	//しっぽ１段目
		case 0:
		{
			drawPosOffset = { 1100.0f * direction.x,0 };
			texSize       = { 1300.0f,350.0f };
			spr           = ImageManager::Instance().getSprite(ImageManager::SpriteNum::bossTail);	//画像差し替えてもsprChangeかの関係で画像おかしくなることあるから無理やり
			if (animeUpdate(0, 2, 6, false))
			{
				animeCount++;
				anime_state = 0;
			}
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
		{
			const int TAIL_SEG = 30;
			const float SEG_LEN = 50.0f;
			if (animeTimer == 6)
			{
				for (int i = 0;i < TAIL_SEG;i++)
				{
					TailHitCircle* c = new TailHitCircle(
						&ProjectileManager::Instance(),
						atk,						//damage
						Projectile::kinds::enemy,
						0.3f,					//lifeLimit
						nullptr,				//使う画像
						{ 30,30 },				//TEX_SIZE
						{ -1.0f,1.0f },					//Scale
						{ 0,0 },					//Speed
						25 * 1.5f,					//radius
						this,					//owner
						{ ((i + 1) * SEG_LEN)*direction.x,-70.0f + (i * 7) },			//offset
						12.0f,				
						this,					//target
						ac							//hit 下かどうかのフラグ
					);	
				}
			}
		}
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
				isTargetRemoveOn = true;	//1判定長いから１つ上にあげた
				animeCount++;
				anime_state = 0;
			}
			break;

		case 7:
			//if (animeUpdate(8, 2, 6, false))
			//{
			//	//texSize = { 500.0f,350.0f };
			//	isTargetRemoveOn = true;
			//	posFlag = true;
			//	isSprChange = true;
			//	//act = ATTACK2_INIT;		//デバッグ用
			//	decideAttack();
			//}

			if (animeUpdate(8, 2, 6, false))
			{
				//texSize = { 500.0f,350.0f };
				anime_state = 0;
				//spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::bossTailPull);
				animeCount++;
			}
			break;

			//尻尾引き戻し
		case 8:
			drawPosOffset = { 1100.0f * direction.x,0 };
			texSize = { 1300.0f,350.0f };
			drawPosOffset = { 1100.0f * direction.x,0 };
			spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::bossTailPull);	//画像差し替えてもsprChangeかの関係で画像おかしくなることあるから無理やり
			if (animeUpdate(0, 2, 6, false))
			{
				anime_state = 0;
				animeCount++;
			}
			break;

		case 9:
			if (animeUpdate(1, 2, 6, false))
			{
				anime_state = 0;
				animeCount++;
			}

			break;

		case 10:
			if (animeUpdate(2, 2, 6, false))
			{
				anime_state = 0;
				animeCount++;
			}

			break;

		case 11:
			if (animeUpdate(3, 2, 6, false))
			{
				anime_state = 0;
				animeCount++;
			}

			break;

		case 12:
			if (animeUpdate(4, 2, 6, false))
			{
				anime_state = 0;
				animeCount++;
			}

			break;

		case 13:
			if (animeUpdate(5, 0, 6, false))
			{
				posFlag = true;
				isSprChange = true;
				isCanFlip = true;
				ac->hasHit = false;
				decideAttack();
				//act = ATTACK2_INIT;
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
		music::play(B_Jump);
		CAMERA::shake(VECTOR2{	rand()%15+7.5f, static_cast<float>( - rand() % 60)});
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
			speed.y = -30;
			if (animeUpdate(1, 1, 6, true)&&pos.y<-300)
			{
				spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::boss);
				isGround = false;
				animeCount = 0;
				act = ATTACK4_INIT;
			}
		}

		break;

	case ATTACK4_INIT:
		anime_state = 0;
		isGravityOn = false;
		isCanFlip   = true;
		
		for (auto& tail : tails)
		{
			tail.setNone(false);
			tail.setFunction(rand() % Tail::funcNum::MAX);
		}
		
		//tail.setFunction(Tail::funcNum::MOVE_LEFT);
		timer = 0;
		act = ATTACK4;

	case ATTACK4:
		if (pos.y < -500)	speed.y = 0.0f;
		timer++;
		if (timer > 60 * 10)
		{
			for(auto& tail:tails)
			tail.setNone(true);
			act = FALL_INIT;
			isGravityOn = true;
		}
		
		break;
		
	case DEATH_INIT:
		anime_state   = 0;
		animeCount    = 0;
		speed         = { 0.0f,0.0f };
		spr           = ImageManager::Instance().getSprite(ImageManager::SpriteNum::boss);
		texSize       = { 500.0f,350.0f };
		drawPosOffset = { 0.0f,0.0f };
		radius        = 0.0f;	//死んだら当たり判定消す

		act = DEATH;

	case DEATH:
		switch (animeCount)
		{
		case 0:
			if (animeUpdate(10, 14, 6, false))
			{
				anime_state = 0;
				animeCount++;
			}
			break;

		case 1:
			if (animeUpdate(11, 14, 6, false))
			{
				isDeathOn = true;
			}
		}
		
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
	//Walkも入れてたけど消した
	if ( act == ATTACK2 || act == ATTACK1)
	{
		act = IDLE_INIT;
		return;
	}

	int r = rand() % 100;
	if (r < 20)
		act = WALK_INIT;
	else if (r < 50)
		act = ATTACK1_INIT;
	else if (r < 80)
		act = ATTACK2_INIT;
	else if (r < 100)
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
	for(auto& tail:tails)
	tail.cameraRender(camera);

	//当たり判定壁
	//primitive::line(hitWall.x - camera.getPos().x, hitWall.top - camera.getPos().y, hitWall.x - camera.getPos().x, hitWall.bottom - camera.getPos().y);
	//VECTOR2 scale = {-direction.x,1.0f};	//元が左向きなので-
	//if(sprTail)
	//sprite_render(sprTail.get(), tailPos.x-camera.getPos().x, tailPos.y-camera.getPos().y, scale.x, scale.y, 0, 0, tailTexSize.x, tailTexSize.y,0,25,ToRadian(0),1,1,1,1);
}
