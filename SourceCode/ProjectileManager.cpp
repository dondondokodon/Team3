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
	//破棄処理
	for (Projectile* projectile : removeList)
	{
		//playerかenemyかを判別
		std::vector<Projectile*>* vec = nullptr;

		if (projectile->GetFaction() == Projectile::Faction::enemy)
			vec = &enemyProjectiles;
		else
		{
			if (projectile->GetOwnerId() == Projectile::kinds::pursuit)
				vec = &pursuitProjectiles;
			else
				vec = &playerProjectiles;

		}

		auto it = std::find(vec->begin(), vec->end(), projectile);
		if (it != vec->end())
			vec->erase(it);

		delete projectile;


	}

	//破棄リストをクリア
	removeList.clear();

	//球の一斉更新
	for (Projectile* p : playerProjectiles)
	{
		p->update();
		p->AnimeUpdate(1);
	}
		
	for (Projectile* p : enemyProjectiles)
	{
		p->update();
		p->AnimeUpdate(0);		//敵は今のところアニメーションないからこれしてない
	}

	for (Projectile* p : pursuitProjectiles)
	{
		p->update();
	}
}

//描画処理
void ProjectileManager::Render(CAMERA& camera)
{
	for (Projectile* projectile : playerProjectiles)
	{
		projectile->cameraRender(camera);
		//GameLib::primitive::circle(projectile->getPos() - camera.getPos(), projectile->getRadius(), { 1, 1 }, 0, { 1, 1, 1, 0.5f });
	}
	for (Projectile* projectile : enemyProjectiles)
	{
		projectile->cameraRender(camera);
		//GameLib::primitive::circle(projectile->getPos() - camera.getPos(), projectile->getRadius(), { 1, 1 }, 0, { 1, 1, 1, 0.5f });
	}
	for (Projectile* projectile : pursuitProjectiles)
	{
		projectile->cameraRender(camera);
		//GameLib::primitive::circle(projectile->getPos() - camera.getPos(), projectile->getRadius(), { 1, 1 }, 0, { 1, 1, 1, 0.5f });
	}

}

//球登録
void ProjectileManager::Register(Projectile* projectile)
{
	if (!projectile)	return;

	if (projectile->GetFaction() == Projectile::Faction::player)
	{
		if (projectile->GetOwnerId() == Projectile::kinds::pursuit)
			pursuitProjectiles.emplace_back(projectile);
		else 
			playerProjectiles.emplace_back(projectile);
	}

	else if (projectile->GetFaction() == Projectile::Faction::enemy)
		enemyProjectiles.emplace_back(projectile);

}

//全削除
void ProjectileManager::Clear()
{
	for (Projectile* projectile : playerProjectiles)
		delete projectile;

	for (Projectile* projectile : enemyProjectiles)
		delete projectile;

	for (Projectile* projectile : pursuitProjectiles)
		delete projectile;

	playerProjectiles.clear();
	enemyProjectiles.clear();
	pursuitProjectiles.clear();
	removeList.clear();
	
}

//リストに追加
void ProjectileManager::Remove(Projectile* projectile)
{
	removeList.insert(projectile);
}

//ターゲットが同じものを削除する
void ProjectileManager::targetRemove(Character* obj)
{
	//敵
	for (auto& p : enemyProjectiles)
	{
		if (p->getTarget() == obj)
		{
			Remove(p);
		}
	}

	//プレイヤー
	for (auto& p : playerProjectiles)
	{
		if (p->getTarget() == obj)
		{
			Remove(p);
		}
	}

	//プレイヤー(追撃弾)
	for (auto& p : pursuitProjectiles)
	{
		if (p->getTarget() == obj)
		{
			Remove(p);
		}
	}
}