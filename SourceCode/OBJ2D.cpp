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

void OBJ2D::cameraRender(CAMERA& camera)
{
	//primitive::rect(pos.x, pos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle, color.x);
	if (!spr)return;
	sprite_render(spr.get(), pos.x - camera.getPos().x, pos.y - camera.getPos().y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle, color.x, color.y, color.z, color.w);
}


void gravity(OBJ2D* obj)
{
	//下に加速
	obj->setSpeed(obj->getSpeed() + VECTOR2{ 0,1.3f });
}

void friction(OBJ2D* obj)	//摩擦
{
	float speedX = fabsf(obj->getSpeed().x);
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
	}
}

