#pragma once
#include "Ghost.h"
#include <vector>
#include <memory>
#include"CAMERA.h"
class EffektManager
{
public:
	static EffektManager& Instance()
	{
		static EffektManager efk;
		return efk;
	}

	void update(CAMERA camera);
	void render(CAMERA camera);
	void init();
	void clear();
	void Remove();
	//エフェクト登録
	void Register(Ghost* efk);
private:
	EffektManager(){}
	~EffektManager(){}
	std::vector<std::shared_ptr<Ghost>> Effekts;
	std::vector<std::shared_ptr<Ghost>> removeList;

};