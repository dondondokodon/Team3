#pragma once
#include "Character.h"
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
	enum class kinds	//発射した球の種類
	{
		light = 0,
		heavy,
		pursuit,
		enemy
	};

	Faction GetFaction()const { return faction; }
	kinds GetOwnerId()const { return ownerId; }

	void Destroy();
	//faction→どっちの球か　ownerId→誰が撃ったか
	Projectile(ProjectileManager* manager, Faction faction,int damage, kinds ownerId, float LifeLimit,std::shared_ptr<Sprite> s,VECTOR2 TEX_SIZE, VECTOR2 SCALE, VECTOR2 Speed, float Dadius);
	virtual ~Projectile(){}
	void kill() { alive = false; }
	void update()override  = 0;
	int getDamage()const { return damage; }
	Character* getTarget() { return target; }
	void AnimeUpdate();
	void normalize(VECTOR2 pos1, VECTOR2 pos2);	//１→２
	void Launch(VECTOR2 dir, VECTOR2 pos);

protected:
	float lifeLimit;
	int damage;
	bool alive;
	
	Character* target;		//HitBoxなどで使う
	//VECTOR2 dir;//向き
	ProjectileManager* manager = nullptr;
	Faction faction;
	kinds ownerId;
	//int ownerId;
	//int animeCount = 0;			//２段目のアニメ再生用変数
};

