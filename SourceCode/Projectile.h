#pragma once
#include "OBJ2D.h"
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
	//faction¨‚Ç‚Á‚¿‚Ì‹…‚©@ownerId¨’N‚ªŒ‚‚Á‚½‚©
	Projectile(ProjectileManager* manager, Faction faction,int damage, int ownerId, float LifeLimit);
	virtual ~Projectile(){}
	void kill() { alive = false; }
	void update()override  = 0;
	int getDamage()const { return damage; }
protected:
	float lifeLimit;
	int damage;
	bool alive;
	VECTOR2 dir;//Œü‚«
	ProjectileManager* manager = nullptr;
	Faction faction;
	int ownerId;
};

