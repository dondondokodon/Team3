#include"all.h"
#include<cmath>
#include<algorithm>
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
				anime = total - 1;
				return true;    // アニメの終端に達した
			}
		}
		texPos.x = anime * texSize.x;
		++animeTimer;

		return false;           // アニメの終端ではない

	}
}


void gravity(OBJ2D* obj)
{
	//下に加速
	obj->setSpeed(obj->getSpeed() + VECTOR2{ 0,5 });
}
