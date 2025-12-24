#pragma once
#include "OBJ2D.h"
#include "CAMERA.h"
class ProjectileManager;

class Projectile :public OBJ2D
{
public:
	enum class Owner
	{
		player,
		enemy
	};

	Owner GetOwner()const { return owner; }
	int GetOwnerId()const { return ownerId; }

	void Destroy();
	//owner¨‚Ç‚Á‚¿‚Ì‹…‚©@ownerId¨’N‚ªŒ‚‚Á‚½‚©
	Projectile(ProjectileManager* manager, Owner owner,int damage, int ownerId);
	virtual ~Projectile(){}
	void kill() { alive = false; }
	void update()override  = 0;
protected:
	float lifeLimit;
	int damage;
	bool alive;
	VECTOR2 dir;//Œü‚«
	ProjectileManager* manager = nullptr;
	Owner owner;
	int ownerId;
};

