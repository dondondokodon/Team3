#include "ProjectileStraight.h"

ProjectileStraight::ProjectileStraight(VECTOR2 Pos,VECTOR2 direction)
{

}
void ProjectileStraight::init()  
{

}
void ProjectileStraight::deinit()
{

}
void ProjectileStraight::update()
{
	lifeLimit -= 0.01f;
	if (lifeLimit < 0)
	{
		//Ž©•ª‚ðíœ
		
	}

	//ˆÚ“®
	pos.x += dir.x * speed.x;
	pos.y += dir.y * speed.y;
}