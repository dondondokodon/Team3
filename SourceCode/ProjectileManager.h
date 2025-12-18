#pragma once
#include<vector>
#include<memory>
#include"Projectile.h"
class ProjectileManager
{
	std::vector<std::unique_ptr<Projectile>> playerProjcetiles;	//ƒvƒŒƒCƒ„[‚Ì’e
	std::vector<std::unique_ptr<Projectile>> enemyProjcetiles;	//“G‚Ì’e
	std::vector<Projectile*> removeList;	//íœ‚·‚é‹…
};

