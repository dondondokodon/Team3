#pragma once
#include<vector>
#include<memory>
#include<set>
#include"Projectile.h"
#include"CAMERA.h"
class ProjectileManager : public OBJ2D
{
public:
	static ProjectileManager& Instance()
	{
		static ProjectileManager instance;
		return instance;
	}
	~ProjectileManager();

	//XV
	void update()override;

	//•`‰æ
	void Render(CAMERA& camera);


	//”æ“¾
	int GetPlayerProjectileCount()const { return static_cast<int>(playerProjectiles.size()); }
	int GetEnemyProjectileCount()const { return static_cast<int>(enemyProjectiles.size()); }

	//‹…‚Ìæ“¾
	Projectile* GetPlayerProjectile(int index) { return playerProjectiles.at(index); }
	Projectile* GetEnemyProjectile(int index) { return enemyProjectiles.at(index); }

	//‘Síœ
	void Clear();

	//“o˜^
	void Register(Projectile* projectile);

	//íœƒŠƒXƒg‚É’Ç‰Á
	void Remove(Projectile* projectile);

	//target‚ª“¯‚¶Ò‚©‚ç‚Ìíœ—v¿
	void targetRemove(Character* obj);

	const std::vector<Projectile*>& GetPlayerProjectile() const { return playerProjectiles; }
	const std::vector<Projectile*>& GetEnemyProjectile() const { return enemyProjectiles; }

private:
	std::vector<Projectile*> playerProjectiles;	//ƒvƒŒƒCƒ„[‚Ì’e
	std::vector<Projectile*> enemyProjectiles;	//“G‚Ì’e
	std::vector<Projectile*> pursuitProjectiles;//’ÇŒ‚’e
	std::set<Projectile*> removeList;	//íœ‚·‚é‹…
	ProjectileManager();
};

