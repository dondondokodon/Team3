#include "ProjectileManager.h"

ProjectileManager::ProjectileManager()
{

}

ProjectileManager::~ProjectileManager()
{
	Clear();
}

//更新
void ProjectileManager::update()
{
	//球の一斉更新
	for (Projectile* p : playerProjectiles)
	{
		p->update();
		p->AnimeUpdate();
	}
		
	for (Projectile* p : enemyProjectiles)
	{
		p->update();
		//p->AnimeUpdate();		敵は今のところアニメーションないからこれしてない
	}

	//破棄処理
	for (Projectile* projectile : removeList)
	{
		//playerかenemyかを判別
		auto& vec = (projectile->GetFaction() == Projectile::Faction::player)
			? playerProjectiles
			: enemyProjectiles;



		auto it = std::find(vec.begin(), vec.end(), projectile);
		if (it != vec.end())
			vec.erase(it);
			
		delete projectile;
		
		
	}

	//破棄リストをクリア
	removeList.clear();
}

//描画処理
void ProjectileManager::Render(CAMERA& camera)
{
	for (Projectile* projectile : playerProjectiles)
	{
		projectile->cameraRender(camera);
		GameLib::primitive::circle(projectile->getPos() - camera.getPos(), projectile->getRadius(), { 1, 1 }, 0, { 1, 1, 1, 0.5f });
		/*debug::setString("radius:%f", projectile->getRadius());
		debug::setString("TexSizeX:%f", projectile->getTexSize().x);*/
	}
	for (Projectile* projectile : enemyProjectiles)
	{
		projectile->cameraRender(camera);
		GameLib::primitive::circle(projectile->getPos() - camera.getPos(), projectile->getRadius(), { 1, 1 }, 0, { 1, 1, 1, 0.5f });
	}

}

//球登録
void ProjectileManager::Register(Projectile* projectile)
{
	if (!projectile)	return;

	if (projectile->GetFaction() == Projectile::Faction::player)
		playerProjectiles.emplace_back(projectile);
	else
		enemyProjectiles.emplace_back(projectile);
}

//全削除
void ProjectileManager::Clear()
{
	for (Projectile* projectile : playerProjectiles)
		delete projectile;

	for (Projectile* projectile : enemyProjectiles)
		delete projectile;

	playerProjectiles.clear();
	enemyProjectiles.clear();
	removeList.clear();
	
}

//リストに追加
void ProjectileManager::Remove(Projectile* projectile)
{
	removeList.insert(projectile);
}