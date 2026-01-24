#include "Ghost.h"

Ghost::Ghost(Player& player)
{
	pos     = player.getPos();
	scale   = player.getScale();
	color   = { 0.5f,0.5f,0.5f,0.5f };
	spr     = player.getSprite();
	texSize = player.getTexSize();
	texPos  = player.getTexPos();
	offset  = player.getOffset();
	pivot = player.getPivot();
	timer   = 60;
}

Ghost::Ghost(Character& chara)
{
	pos     = chara.getPos();
	scale   = chara.getScale();
	color   = { 0.5f,0.5f,0.5f,0.5f };
	spr     = chara.getSprite();
	texSize = chara.getTexSize();
	texPos  = chara.getTexPos();
	offset  = chara.getOffset();
	pivot   = chara.getPivot();
	timer   = 60;
}

Ghost::~Ghost()
{

}

void Ghost::init()
{
}

void Ghost::deinit()
{

}
void Ghost::update()
{
	timer--;
	color.w -= 0.02f;
}

bool Ghost::Remove()
{
	return (timer <= 0);
}