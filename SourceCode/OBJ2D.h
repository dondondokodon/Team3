#pragma once
#include "../GameLib/game_lib.h"
#include"common.h"
using namespace GameLib;
using namespace input;

enum
{
	circle,
	rect,
	line
};

class OBJ2D
{
protected:
	VECTOR2 pos;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;
	VECTOR2 speed;
	VECTOR2 offset;
	VECTOR2 drawScale;	//ƒJƒƒ‰‚Ì‚â‚Â
	int angle;
	GameLib::Sprite* spr;
	GameLib::Sprite* spr_Sengeki;
	int act;
	int timer;
	int anime;
	int animeTimer;
	int anime_state;
	float radius;     // ”¼Œa
	float eyeRadius;
	VECTOR2 screenPos;	//•`‰æˆÊ’u

	//‘Ì‚¾‚¯
	float   bodyRadius;     // ”¼Œa
	VECTOR2 bodySize;
	VECTOR2 bodyOffset;

public:
	void setsprite(Sprite* s)
	{
		spr = s;
	}

	virtual void render()
	{
		if (!spr) return;
		sprite_render(spr, pos.x, pos.y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle, color.x, color.y, color.z, color.w);
	}

	/*void camera_render(Camera& camera)
	{
		if (!spr) return;
			screenPos = camera.ZoomScreen(pos);
			drawScale.x = scale.x * camera.GetZoom();
			drawScale.y = scale.y * camera.GetZoom();
			sprite_render(spr, screenPos.x, screenPos.y, drawScale.x, drawScale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle,color.x, color.y, color.z, color.w);
	}*/

	virtual void init() {}
	virtual void deinit() {}
	virtual void update() = 0;
	bool animeUpdate(int animeNo, int total, int frame, bool loop);

	int                 hitPrimitive;//•¨‚ÌŒ`
	VECTOR2 getPos() { return pos; }
	VECTOR2 getScale() { return scale; }
	bool getRadius() { return radius; }
	int getAct() { return act; }
	int getAnime() { return anime; }
	float getBodyRadius() { return bodyRadius; }
	VECTOR2 getBodyOffset() { return bodyOffset; }

	void setScale(VECTOR2 Scale) { scale = Scale; }
	void setAct(int Act) { act = Act; }
	void setColor(VECTOR4 c) { color = c; }

	void hitAreaRender(int f);
	void hitAreaRender();
	void setSpeed(VECTOR2 Speed) { speed = Speed; }
	//void hitAreaRender(Camera& camera);
	//void bodyHitAreaRender(Camera& camera);

	void bodyHitAreaRender();
	virtual bool hitCheck(OBJ2D& obj, bool bodyOnly);
	//bool hitCheck(OBJ2D& obj, bool bodyOnly, Camera& camera);
};
class CHARACTER :public OBJ2D
{
protected:
	int hp;
	int atk;
	int MaxHP;
	bool attackOn;	//UŒ‚”­¶’†‚©‚Ç‚¤‚©
	int  joutai = -1;	//-1‰½‚à‚È‚µ@0‘Ì‚¾‚¯@‚PUŒ‚‚µ‚½@‚QUŒ‚‚³‚ê‚½
	int  targetATK = 0;	//“G‚ÌUŒ‚—Í
	int mutekiTimer = 0;
	bool efectOn = false;

public:
	virtual void Act() = 0;
	virtual int getHp() { return hp; }
	virtual int getMaxhp() { return MaxHP; }
	int getATK() { return atk; }
	//bool hitCheck(OBJ2D& obj,bool bodyOnly);
	virtual int getUltCount() const { return 0; }
	bool getAttackOn() { return attackOn; }
	int getMutekiTimer() { return mutekiTimer; }
	//-1‰½‚à‚È‚µ@0‘Ì‚¾‚¯@‚PUŒ‚‚µ‚½@‚QUŒ‚‚³‚ê‚½  “G‚ÌUŒ‚—Í‚ðˆø”‚É“ü‚ê‚é
	void setJoutai(int j, int atk) { joutai = j;targetATK = atk; }
	bool isAlive() { return hp > 0; }	//Ž€‚ñ‚Å‚½‚çfalse
	VECTOR2 getpos() { return pos; }
	float getSX() { return speed.x; }

	void setp(float position) { pos.x = position; }

	void hitEfect();
};

enum JUDGE
{
	attackPlayer,
	attackEnemy,
	bodyOnly
};
bool hitCheck(CHARACTER* p1, CHARACTER* p2, int num);
//bool camera_hitCheck(CHARACTER* p1, CHARACTER* p2, int num, Camera& camera);

void ScaleRebarse(CHARACTER* p1, CHARACTER* p2);
void setPos(CHARACTER* p1, CHARACTER* p2);