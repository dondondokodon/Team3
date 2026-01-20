#include"all.h"
#include<cmath>
#include<algorithm>
#include "CAMERA.h"
using namespace std;


bool OBJ2D::animeUpdate(int animeNo, int total, int frame, bool loop)
{
	switch (anime_state)
	{
	case 0:
		anime = animeTimer = 0;
		texPos = { 0, animeNo * texSize.y };

		anime_state++;
	case 1:
		anime = animeTimer / frame;
		if (loop)
		{
			if (anime >= total)
			{
				anime = 0;
				animeTimer = 0;
				return true;
			}
		}
		else
		{
			if (anime >= total)
			{
				anime = total;
				return true;    // アニメの終端に達した
			}
		}
		texPos.x = anime * texSize.x;
		++animeTimer;

		return false;           // アニメの終端ではない

	}
}

void OBJ2D::hitAreaRender(CAMERA& camera)
{
	//いったん円だけ
	primitive::circle(VECTOR2(pos - camera.getPos()) + (VECTOR2{ offset.x * scale.x,offset.y * scale.y }), radius, {1,1}, angle, {1,0,0,0.3f});
}

void OBJ2D::cameraRender(CAMERA& camera)
{
	//primitive::rect(pos.x, pos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle, color.x);
	if (!spr)return;
	sprite_render(spr.get(), pos.x - camera.getPos().x, pos.y - camera.getPos().y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle, color.x, color.y, color.z, color.w);
}


void gravity(OBJ2D* obj, VECTOR2 energy)
{
	//下に加速
	obj->setSpeed(obj->getSpeed() + energy);
}

void friction(OBJ2D* obj)	//摩擦
{
	/*float speedX = fabsf(obj->getSpeed().x);
	if (speedX > 0)
	{
		float friction = 1.0f;
		VECTOR2 Speed = obj->getSpeed();
		if (speedX > friction)
		{
			float scale =( speedX - friction )/ speedX;
			Speed.x*= scale;
		}
		else
			Speed.x = 0.0f;
		obj->setSpeed(Speed);
	}*/

	float friction = 0.8f; // 20% 減速
	VECTOR2 v = obj->getSpeed();
	v.x *= friction;

	if (fabsf(v.x) < 0.1f)
		v.x = 0;

	obj->setSpeed(v);
}

//小さい桁から
void NumbersRender(int num, Sprite* spr, VECTOR2 pos, VECTOR2 scale, VECTOR2 texPos, VECTOR2 texSize, VECTOR2 pivot, int angle, VECTOR4 color)
{
	if (!num)
	{
		sprite_render(spr,
			pos.x, pos.y, scale.x, scale.y,
			texPos.x, texPos.y, texSize.x, texSize.y,
			pivot.x, pivot.y, angle,
			color.x, color.y, color.z, color.w);
		return;
	}
	int offset = 0;
	while (num > 0)
	{
		int number = num % 10;  // 1の位から取り出す
		num /= 10;              // 次の桁へ

		// 桁ごとに少しずつ右にずらす（40ピクセル単位など）
		sprite_render(spr,
			pos.x - offset, pos.y, scale.x, scale.y,
			texPos.x + texSize.x * number, texPos.y, texSize.x, texSize.y,
			pivot.x, pivot.y, angle,
			color.x, color.y, color.z, color.w);

		offset += texSize.x; // 次の桁の位置調整
	}
}

void OBJ2D::init()
{
	pos        = { 0.0f,0.0f };
	scale      = { 1.0f,1.0f };
	texPos     = { 0.0f,0.0f };
	texSize    = {0.0f,0.0f};
	pivot      = { 0.0f,0.0f };
	color      ={ 1.0f,1.0f,1.0f,1.0f };
	speed      = { 0.0f,0.0f };
	offset     = {0.0f,0.0f};
	direction  = { 0.0f,0.0f };
	angle      =0.0f;
	spr        =nullptr;

	act        =0;
	timer      =0;
	anime      =0;
	animeTimer =0;
	anime_state=0;
	radius     =0;     // 半径
}