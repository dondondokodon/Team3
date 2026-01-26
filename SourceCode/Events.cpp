#include "Events.h"
#include "audio.h"
#include "PlayerEffect.h"

void Events::init()
{
	isScaleUp = false;
	scale     = { 1.0f,1.0f };
	pushCount = 0;
	isRight   = false;
	drawMask  = 0;

	int i = 0;
	for (auto& t : text)
	{
		t.setSprite(ImageManager::Instance().getSprite(ImageManager::SpriteNum::Event1));
		t.setPosition({ 0.0f,0.0f });
		t.setScale({ 1.0f,1.0f });
		t.setTexSize({ 1013.0f, 174.0f });
		t.setTexPos({ i * t.getTexSize().x,0.0f });
		t.setPivot({ t.getTexSize().x * 0.5f,0.0f });
		t.setColor({ 1.0f,1.0f,1.0f,1.0f });
		t.setSpeed({ 0.0f,0.0f });
		t.setOffset({ 0.0f,0.0f });
		t.setAngle(0);
		t.setDirection({ 0.0f,0.0f });
		i++;
	}

	//コメントないのは下の文字
	text[0].setPosition({ 550.0f, 50.0f });	//タイトル	
	text[1].setPosition({ SCREEN_W*0.5f, SCREEN_H-200.0f });
	text[2].setPosition({ 450.0f, SCREEN_H*0.5f });	//選ぶやつ
	text[3].setPosition({ 850.0f, SCREEN_H*0.5f });//選ぶやつ
	text[4].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[5].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[6].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[7].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[8].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[9].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });

	text[2].setTexSize({ 324.0f,99.0f });
	text[2].setPivot({ text[2].getTexSize().x * 0.5f,text[2].getTexSize().y * 0.5f });
	text[3].setTexSize({ 324.0f,99.0f });
	text[3].setPivot({ text[3].getTexSize().x * 0.5f,text[3].getTexSize().y * 0.5f });

	drawMask = TEXT_TITLE | TEXT_LEFT | TEXT_RIGHT|TEXT_MSG1;
}

bool Events::update()
{	
	switch (pushCount)
	{
	case 1:
		drawMask |= TEXT_MSG2;
		break;
	case 2:
		drawMask &= ~TEXT_MSG2;
		drawMask |= TEXT_MSG3;
		if (TRG(0) & PAD_START)
		{
			Coin::AddCoinNum(800);
			Coin::AddGotCoin(800);
			return true;
		}
			
		break;

	case 3:
		drawMask |= TEXT_MSG4;
		break;

	case 4:
		drawMask &= ~TEXT_MSG4;
		drawMask |= TEXT_MSG5;
		if (TRG(0) & PAD_START)
		{
			Coin::DegCoinNum(Coin::GetCoinNum() * 0.4f);
			//特別なビルドをアンロック
			Build::extraMoonGravity = true;
			return true;
		}
		break;

	case 5:
		drawMask |= TEXT_MSG6;
		break;

	case 6:
		drawMask &= ~TEXT_MSG6;
		drawMask |= TEXT_MSG7;
		if (TRG(0) & PAD_START)
		{
			Coin::AddCoinNum(300);
			Coin::AddGotCoin(300);
			music::play(pic);
			return true;
		}	
		break;
	}

	if (!pushCount)
	{
		//右押したら
		if (TRG(0) & PAD_RIGHT)
		{
			isRight = true;
			isScaleUp = false;
			scale = { 1.0f,1.0f };
		}
		//左押したら
		if (TRG(0) & PAD_LEFT)
		{
			isRight = false;
			isScaleUp = false;
			scale = { 1.0f,1.0f };
		}

		if (isRight)
		{
			//スケール更新
			text[3].setScale({ scale.x,scale.x });
			text[2].setScale({ 1.0f,1.0f });
		}
		else
		{
			//スケール更新
			text[2].setScale({ scale.x,scale.x });
			text[3].setScale({ 1.0f,1.0f });
		}

		//文字サイズ大きくする
		const float scaleNum = 0.01f;
		if (isScaleUp)
		{
			scale.x += scaleNum;
			if (scale.x >= 1.3)
			{
				isScaleUp = false;
			}
		}
		else
		{
			scale.x -= scaleNum;
			if (scale.x <= 1.0f)
			{
				isScaleUp = true;
			}
		}

		if (TRG(0) & PAD_START)
		{
			if (isRight)
			{
				pushCount = 5;
			}
			else
			{
				(rand() % 2 == 0) ? pushCount = 1 : pushCount = 3;
			}

			music::play(pic);
			drawMask &= ~TEXT_LEFT;
			drawMask &= ~TEXT_RIGHT;
			drawMask &= ~TEXT_MSG1;
		}
	}
	else
		if (TRG(0) & PAD_START)
		{
			music::play(pic);
			pushCount++;
		}
	
	return false;
}

void Events::render()
{
	for (int i = 0; i <10; i++)
	{
		if (drawMask & (1 << i))
		{
			text[i].render();
		}
	}
}
/// <summary>
/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// </summary>

void Event2::init()
{
	isScaleUp = false;
	scale = { 1.0f,1.0f };
	pushCount = 0;
	isRight = false;
	drawMask = 0;

	int i = 0;
	for (auto& t : text)
	{
		t.setSprite(ImageManager::Instance().getSprite(ImageManager::SpriteNum::Event2));
		t.setPosition({ 0.0f,0.0f });
		t.setScale({ 1.0f,1.0f });
		t.setTexSize({ 1093.0f, 174.0f });
		t.setTexPos({ i * t.getTexSize().x,0.0f });
		t.setPivot({ t.getTexSize().x * 0.5f,0.0f });
		t.setColor({ 1.0f,1.0f,1.0f,1.0f });
		t.setSpeed({ 0.0f,0.0f });
		t.setOffset({ 0.0f,0.0f });
		t.setAngle(0);
		t.setDirection({ 0.0f,0.0f });
		i++;
	}

	//コメントないのは下の文字
	text[0].setPosition({ 550.0f, 50.0f });	//タイトル	
	text[1].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[2].setPosition({ 450.0f, SCREEN_H * 0.5f });	//選ぶやつ
	text[3].setPosition({ 850.0f, SCREEN_H * 0.5f });//選ぶやつ
	text[4].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[5].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[6].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[7].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });

	text[8].setSprite(nullptr);
	text[9].setSprite(nullptr);

	text[2].setTexSize({ 324.0f,99.0f });
	text[2].setPivot({ text[2].getTexSize().x * 0.5f,text[2].getTexSize().y * 0.5f });
	text[3].setTexSize({ 324.0f,99.0f });
	text[3].setPivot({ text[3].getTexSize().x * 0.5f,text[3].getTexSize().y * 0.5f });

	drawMask = TEXT_TITLE | TEXT_LEFT | TEXT_RIGHT | TEXT_MSG1;
}

bool Event2::update()
{
	switch (pushCount)
	{
	case 1:
		drawMask |= TEXT_MSG2;
		break;
	case 2:
		drawMask &= ~TEXT_MSG2;
		drawMask |= TEXT_MSG3;
		if (TRG(0) & PAD_START)
		{
#if 2
			//TODO::後でやる
#endif

			//攻撃に使用するコインの量を増やす
			//PlayerEffect::attackCoinUp = true;
			Build::extraCost = true;

			//被ダメージ上昇
			//PlayerEffect::defDef = true;
			Build::defenseDown = true;

			return true;
		}

		break;

	case 3:
		drawMask |= TEXT_MSG4;
		break;

	case 4:
		drawMask &= ~TEXT_MSG4;
		drawMask |= TEXT_MSG5;
		if (TRG(0) & PAD_START)
		{
#if 3
			//TODO::パーク
#endif
			//複数のパーク入手
			Build::extraJump = true;


			//コイン減少
			Coin::DegCoinNum(Coin::GetCoinNum() * 0.4f);

			return true;
		}
		break;
	}

	if (!pushCount)
	{
		//右押したら
		if (TRG(0) & PAD_RIGHT)
		{
			isRight = true;
			isScaleUp = false;
			scale = { 1.0f,1.0f };
		}
		//左押したら
		if (TRG(0) & PAD_LEFT)
		{
			isRight = false;
			isScaleUp = false;
			scale = { 1.0f,1.0f };
		}

		if (isRight)
		{
			//スケール更新
			text[3].setScale({ scale.x,scale.x });
			text[2].setScale({ 1.0f,1.0f });
		}
		else
		{
			//スケール更新
			text[2].setScale({ scale.x,scale.x });
			text[3].setScale({ 1.0f,1.0f });
		}

		//文字サイズ大きくする
		const float scaleNum = 0.01f;
		if (isScaleUp)
		{
			scale.x += scaleNum;
			if (scale.x >= 1.3)
			{
				isScaleUp = false;
			}
		}
		else
		{
			scale.x -= scaleNum;
			if (scale.x <= 1.0f)
			{
				isScaleUp = true;
			}
		}

		if (TRG(0) & PAD_START)
		{
			if (isRight)
			{
				pushCount = 3;
			}
			else
			{
				pushCount = 1;
			}

			music::play(pic);
			drawMask &= ~TEXT_LEFT;
			drawMask &= ~TEXT_RIGHT;
			drawMask &= ~TEXT_MSG1;
		}
	}
	else
		if (TRG(0) & PAD_START)
		{
			music::play(pic);
			pushCount++;
		}

	return false;
}

/// <summary>
/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// </summary>
void Event3::init()
{
	isScaleUp = false;
	scale = { 1.0f,1.0f };
	pushCount = 0;
	isRight = false;
	drawMask = 0;

	int i = 0;
	for (auto& t : text)
	{
		t.setSprite(ImageManager::Instance().getSprite(ImageManager::SpriteNum::Event5));
		t.setPosition({ 0.0f,0.0f });
		t.setScale({ 1.0f,1.0f });
		t.setTexSize({ 928.0f, 174.0f });
		t.setTexPos({ i * t.getTexSize().x,0.0f });
		t.setPivot({ t.getTexSize().x * 0.5f,0.0f });
		t.setColor({ 1.0f,1.0f,1.0f,1.0f });
		t.setSpeed({ 0.0f,0.0f });
		t.setOffset({ 0.0f,0.0f });
		t.setAngle(0);
		t.setDirection({ 0.0f,0.0f });
		i++;
	}

	//コメントないのは下の文字
	text[0].setPosition({ 550.0f, 50.0f });	//タイトル	
	text[1].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[2].setPosition({ 450.0f, SCREEN_H * 0.5f });	//選ぶやつ
	text[3].setPosition({ 850.0f, SCREEN_H * 0.5f });//選ぶやつ
	text[4].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[5].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[6].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[7].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });

	text[8].setSprite(nullptr);
	text[9].setSprite(nullptr);

	text[2].setTexSize({ 324.0f,99.0f });
	text[2].setPivot({ text[2].getTexSize().x * 0.5f,text[2].getTexSize().y * 0.5f });
	text[3].setTexSize({ 324.0f,99.0f });
	text[3].setPivot({ text[3].getTexSize().x * 0.5f,text[3].getTexSize().y * 0.5f });

	drawMask = TEXT_TITLE | TEXT_LEFT | TEXT_RIGHT | TEXT_MSG1;
}

bool Event3::update()
{
	switch (pushCount)
	{
	case 1:
		drawMask |= TEXT_MSG2;
		break;
	case 2:
		drawMask &= ~TEXT_MSG2;
		drawMask |= TEXT_MSG3;
		if (TRG(0) & PAD_START)
		{
			Coin::AddCoinNum(600);
			Coin::AddGotCoin(600);
			return true;
		}

		break;

	case 3:
		drawMask |= TEXT_MSG4;
		break;

	case 4:
		drawMask &= ~TEXT_MSG4;
		drawMask |= TEXT_MSG5;
		if (TRG(0) & PAD_START)
		{
#if 4
			//TODO::パーク
#endif
			//パーク入手
		
			return true;
		}
		break;
	}

	if (!pushCount)
	{
		//右押したら
		if (TRG(0) & PAD_RIGHT)
		{
			isRight = true;
			isScaleUp = false;
			scale = { 1.0f,1.0f };
		}
		//左押したら
		if (TRG(0) & PAD_LEFT)
		{
			isRight = false;
			isScaleUp = false;
			scale = { 1.0f,1.0f };
		}

		if (isRight)
		{
			//スケール更新
			text[3].setScale({ scale.x,scale.x });
			text[2].setScale({ 1.0f,1.0f });
		}
		else
		{
			//スケール更新
			text[2].setScale({ scale.x,scale.x });
			text[3].setScale({ 1.0f,1.0f });
		}

		//文字サイズ大きくする
		const float scaleNum = 0.01f;
		if (isScaleUp)
		{
			scale.x += scaleNum;
			if (scale.x >= 1.3)
			{
				isScaleUp = false;
			}
		}
		else
		{
			scale.x -= scaleNum;
			if (scale.x <= 1.0f)
			{
				isScaleUp = true;
			}
		}

		if (TRG(0) & PAD_START)
		{
			if (isRight)
			{
				pushCount = 3;
			}
			else
			{
				pushCount = 1;
			}

			music::play(pic);
			drawMask &= ~TEXT_LEFT;
			drawMask &= ~TEXT_RIGHT;
			drawMask &= ~TEXT_MSG1;
		}
	}
	else
		if (TRG(0) & PAD_START)
		{
			music::play(pic);
			pushCount++;
		}

	return false;
}


///////////////////////////////////////////////////////////////////////////////////////
void Event4::init()
{
	isScaleUp = false;
	scale = { 1.0f,1.0f };
	pushCount = 0;
	isRight = false;
	drawMask = 0;

	int i = 0;
	for (auto& t : text)
	{
		t.setSprite(ImageManager::Instance().getSprite(ImageManager::SpriteNum::Event3));
		t.setPosition({ 0.0f,0.0f });
		t.setScale({ 1.0f,1.0f });
		t.setTexSize({ 929.0f, 174.0f });
		t.setTexPos({ i * t.getTexSize().x,0.0f });
		t.setPivot({ t.getTexSize().x * 0.5f,0.0f });
		t.setColor({ 1.0f,1.0f,1.0f,1.0f });
		t.setSpeed({ 0.0f,0.0f });
		t.setOffset({ 0.0f,0.0f });
		t.setAngle(0);
		t.setDirection({ 0.0f,0.0f });
		i++;
	}

	//コメントないのは下の文字
	text[0].setPosition({ 550.0f, 50.0f });	//タイトル	
	text[1].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[2].setPosition({ 450.0f, SCREEN_H * 0.5f });	//選ぶやつ
	text[3].setPosition({ 850.0f, SCREEN_H * 0.5f });//選ぶやつ
	text[4].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[5].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[6].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[7].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });

	text[8].setSprite(nullptr);
	text[9].setSprite(nullptr);

	text[2].setTexSize({ 324.0f,99.0f });
	text[2].setPivot({ text[2].getTexSize().x * 0.5f,text[2].getTexSize().y * 0.5f });
	text[3].setTexSize({ 324.0f,99.0f });
	text[3].setPivot({ text[3].getTexSize().x * 0.5f,text[3].getTexSize().y * 0.5f });

	drawMask = TEXT_TITLE | TEXT_LEFT | TEXT_RIGHT | TEXT_MSG1;
}

bool Event4::update()
{
	switch (pushCount)
	{
	case 1:
		drawMask |= TEXT_MSG2;
		break;
	case 2:
		drawMask &= ~TEXT_MSG2;
		drawMask |= TEXT_MSG3;
		if (TRG(0) & PAD_START)
		{
			Coin::DegCoinNum(Coin::GetCoinNum() * 0.4f);
			flag = true;
			return true;
		}

		break;

	case 3:
		drawMask |= TEXT_MSG4;
		break;

	case 4:
		drawMask &= ~TEXT_MSG4;
		drawMask |= TEXT_MSG5;
		if (TRG(0) & PAD_START)
		{
			Coin::AddCoinNum(600);
			Coin::AddGotCoin(600);
			return true;
		}
		break;
	}

	if (!pushCount)
	{
		//右押したら
		if (TRG(0) & PAD_RIGHT)
		{
			isRight = true;
			isScaleUp = false;
			scale = { 1.0f,1.0f };
		}
		//左押したら
		if (TRG(0) & PAD_LEFT)
		{
			isRight = false;
			isScaleUp = false;
			scale = { 1.0f,1.0f };
		}

		if (isRight)
		{
			//スケール更新
			text[3].setScale({ scale.x,scale.x });
			text[2].setScale({ 1.0f,1.0f });
		}
		else
		{
			//スケール更新
			text[2].setScale({ scale.x,scale.x });
			text[3].setScale({ 1.0f,1.0f });
		}

		//文字サイズ大きくする
		const float scaleNum = 0.01f;
		if (isScaleUp)
		{
			scale.x += scaleNum;
			if (scale.x >= 1.3)
			{
				isScaleUp = false;
			}
		}
		else
		{
			scale.x -= scaleNum;
			if (scale.x <= 1.0f)
			{
				isScaleUp = true;
			}
		}

		if (TRG(0) & PAD_START)
		{
			if (isRight)
			{
				pushCount = 3;
			}
			else
			{
				pushCount = 1;
			}

			music::play(pic);
			drawMask &= ~TEXT_LEFT;
			drawMask &= ~TEXT_RIGHT;
			drawMask &= ~TEXT_MSG1;
		}
	}
	else
		if (TRG(0) & PAD_START)
		{
			music::play(pic);
			pushCount++;
		}

	return false;
}


///////////////////////////////////////////////////////////////////////////////////////
void Event5::init()
{
	isScaleUp = false;
	scale = { 1.0f,1.0f };
	pushCount = 0;
	isRight = false;
	drawMask = 0;

	int i = 0;
	for (auto& t : text)
	{
		t.setSprite(ImageManager::Instance().getSprite(ImageManager::SpriteNum::Event4));
		t.setPosition({ 0.0f,0.0f });
		t.setScale({ 1.0f,1.0f });
		t.setTexSize({ 1179.0f, 174.0f });
		t.setTexPos({ i * t.getTexSize().x,0.0f });
		t.setPivot({ t.getTexSize().x * 0.5f,0.0f });
		t.setColor({ 1.0f,1.0f,1.0f,1.0f });
		t.setSpeed({ 0.0f,0.0f });
		t.setOffset({ 0.0f,0.0f });
		t.setAngle(0);
		t.setDirection({ 0.0f,0.0f });
		i++;
	}

	//コメントないのは下の文字
	text[0].setPosition({ 550.0f, 50.0f });	//タイトル	
	text[1].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[2].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[3].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[4].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[5].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[6].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });
	text[7].setPosition({ SCREEN_W * 0.5f, SCREEN_H - 200.0f });

	/*text[8].setSprite(nullptr);
	text[9].setSprite(nullptr);
	text[2].setSprite(nullptr);
	text[3].setSprite(nullptr);
	text[6].setSprite(nullptr);
	text[7].setSprite(nullptr);*/

	drawMask = TEXT_TITLE | TEXT_MSG1;
}

bool Event5::update()
{
	switch (pushCount)
	{
	case 1:
		drawMask |= TEXT_MSG2;
		break;
	case 2:
		drawMask &= ~TEXT_MSG2;
		drawMask |= TEXT_MSG3;
		if (TRG(0) & PAD_START)
		{
			Coin::AddCoinNum(2000);
			Coin::AddGotCoin(2000);
			flag = false;
			return true;
		}
	}

	if (!pushCount)
	{
		if (TRG(0) & PAD_START)
		{
			pushCount = 1;
			music::play(pic);
			drawMask &= ~TEXT_MSG1;
		}
	}
	else
		if (TRG(0) & PAD_START)
		{
			music::play(pic);
			pushCount++;
		}

	return false;
}