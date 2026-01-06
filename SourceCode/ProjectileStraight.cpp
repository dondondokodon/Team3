#include "ProjectileStraight.h"

ProjectileStraight::ProjectileStraight(ProjectileManager* manager, Faction faction, int damage, int ownerId,float LifeLimit, std::shared_ptr<Sprite> s, VECTOR2 TEX_SIZE,VECTOR2 SCALE, VECTOR2 Speed):Projectile(manager, faction,damage,ownerId,LifeLimit,s,TEX_SIZE,SCALE,Speed)
{
	//コメントにしてるのは基底クラスのコンストラクタでしてる
	//spr = std::shared_ptr<GameLib::Sprite>(GameLib::sprite_load(L"./Data/Images/1213_coin6x6.png"));
	pos = {SCREEN_W * 0.5f,SCREEN_H * 0.5f };
	//scale = { 1,1 };
	texPos = { 0,0 };
	//texSize = { 44,66 };
	//texSize = { 6,6 };
	pivot = { texSize.x * 0.5f,texSize.y *0.5f};
	color = { 1,1,1,1 };
	//speed = { 10,10 };
	offset = { 0,0 };
	angle = 0;
	act = 0;
	timer = 0;
	anime = 0;
	animeTimer = 0;
	anime_state = 0;
	radius = texSize.x * 0.5f;
	//lifeLimit = 0.5f;
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
		//自分を削除
		Destroy();
	}
	//発射
	pos.x += dir.x * speed.x;
	pos.y += dir.y * speed.y;

}

void ProjectileStraight::render()
{
	//GameLib::primitive::circle(pos.x, pos.y, 50, 1, 1);
	sprite_render(spr.get(), pos.x, pos.y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle, color.x, color.y, color.z, color.w);
}
void ProjectileStraight::Launch(VECTOR2 dir, VECTOR2 pos)
{
	this->dir = dir;
	this->pos = pos;
}
