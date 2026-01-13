#include "HitBox.h"

HitBox::HitBox(ProjectileManager* manager, Projectile::Faction faction, int damage, Projectile::kinds ownerId, float LifeLimit, std::shared_ptr<Sprite> s, VECTOR2 TEX_SIZE, VECTOR2 SCALE, VECTOR2 Speed, float Radius, Character* Target):Projectile(manager,faction,damage,ownerId,LifeLimit,s,TEX_SIZE,SCALE,Speed,Radius)
{
	target=Target;
	texPos = { 0,0 };
	pivot = { texSize.x * 0.5f,texSize.y * 0.5f };
	color = { 1,1,1,1 };
	offset = { 0,0 };
	angle = 0;
	act = 0;
	timer = 0;
	anime = 0;
	animeTimer = 0;
	anime_state = 0;
	//radius = texSize.x * scale.x * 0.5f;
}

void HitBox::init()
{

}

void HitBox::deinit()
{
	
}

void HitBox::update()
{
	pos = target->getMellePos();

}

void HitBox::render()
{
	primitive::circle(pos.x, pos.y, radius, scale.x, scale.y, 0, 0, 1, 0, 0.4f);
}

void HitBox::Launch(VECTOR2 dir, VECTOR2 pos)
{

}