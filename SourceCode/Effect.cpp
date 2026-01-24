#include "Effect.h"
#include "EnemyManager.h"

Effect::Effect(Character& chara) :Ghost(chara), owner(&chara)
{
	isRemove = false;
	color    = { 1.0f,1.0f,1.0f,1.0f };
	texSize  = { 50.0f,50.0f };
	scale    = { 2.0f*-chara.getDir().x,2.0f};
	pivot    = { texSize.x,texSize.y * 0.5f };
	spr      = ImageManager::Instance().getSprite(ImageManager::SpriteNum::hitEffectE);
	if (dynamic_cast<EnemyBoss*>(owner))
		scale *= 2;
}

Effect::~Effect()
{

}

void Effect::init()
{
	isRemove = false;
}

void Effect::deinit()
{

}
void Effect::update()
{
	if (owner)
	{
		if (!EnemyManager::instance().isAlive(owner))
		{
			owner = nullptr;
			isRemove = true;   // ’Ç]Œ³‚ªŽ€‚ñ‚¾‚çÁ‚·
			return;
		}

		pos = owner->getPos();
	}

	if (animeUpdate(0, 9, 3, false))
		isRemove = true;
}

bool Effect::Remove()
{
	return isRemove;
}

//EffextP

EffectP::EffectP(Character& chara):Effect(chara)
{
	spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::hitEffectP);
}


EffectP::~EffectP()
{
	isRemove = false;
}

void EffectP::init()
{
	isRemove = false;
}

void EffectP::deinit()
{
	isRemove = false;
}

void EffectP::update()
{
	if (owner)
	{
		if (owner->isDeath())
		{
			owner = nullptr;
			isRemove = true;
			return;
		}

		pos = { owner->getPos().x,owner->getPos().y+30};
	}

	if (animeUpdate(0, 9, 3, false))
		isRemove = true;
}