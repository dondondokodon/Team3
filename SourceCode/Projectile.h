#pragma once
#include "OBJ2D.h"
#include <memory>
#include "CAMERA.h"
class ProjectileManager;

class Projectile :public OBJ2D
{
public:
	enum class Faction
	{
		player,
		enemy
	};

	Faction GetFaction()const { return faction; }
	int GetOwnerId()const { return ownerId; }

	void Destroy();
	//faction→どっちの球か　ownerId→誰が撃ったか
	Projectile(ProjectileManager* manager, Faction faction,int damage, int ownerId, float LifeLimit,std::shared_ptr<Sprite> s,VECTOR2 TEX_SIZE, VECTOR2 SCALE, VECTOR2 Speed);
	virtual ~Projectile(){}
	void kill() { alive = false; }
	void update()override  = 0;
	int getDamage()const { return damage; }
	void AnimeUpdate();

protected:
	float lifeLimit;
	int damage;
	bool alive;
	VECTOR2 dir;//向き
	ProjectileManager* manager = nullptr;
	Faction faction;
	int ownerId;
	//int animeCount = 0;			//２段目のアニメ再生用変数
};

