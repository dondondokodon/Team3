#include "EffektManager.h"

void EffektManager::update(CAMERA camera)
{
	int num = 0;	//ループ回数　デバッグ用
	for (auto it = Effekts.begin(); it != Effekts.end(); )
	{
			(*it)->update();
	
		//生存時間が消えたら
		if ((*it)->Remove())
		{
			(*it)->deinit();
			it = Effekts.erase(it); // eraseは次のiteratorを返す
		}
		else
		{
			++it;
			++num;
		}
	}
}
void EffektManager::render(CAMERA camera)
{
	for (auto& e : Effekts)
	{
		e->cameraRender(camera);
	}
}
void EffektManager::init()
{

}
void EffektManager::clear()
{
	Effekts.clear();
}
void EffektManager::Remove()
{

}

//エフェクト登録
void EffektManager::Register(Ghost* efk)
{
	if (!efk)	return;
	Effekts.emplace_back(efk);
}
