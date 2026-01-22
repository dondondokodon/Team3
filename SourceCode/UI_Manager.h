#pragma once
#include <vector>
#include "OBJ2D.h"
#include "Character.h"
#include "../GameLib/game_lib.h"
#include"CAMERA.h"

//各uiの基底クラス
class textUI : public OBJ2D
{
public:
	textUI(){}
	virtual ~textUI(){}
	enum kinds
	{
		deg,
		add
	};

	virtual void update() override {}
	int getKind()const { return kind; }
	int kind = -1;
};

class DegMoneyText : public textUI
{
public:
	DegMoneyText(VECTOR2 pos);
	~DegMoneyText() override {}

};

class AddMoneyText : public textUI
{
public:
	AddMoneyText(VECTOR2 pos);
	~AddMoneyText() override {}

};

//戦闘中のコインの増減用のテキストを管理するクラス
class textUI_Manager
{
public:
	static textUI_Manager& Instance()
	{
		static textUI_Manager instance;
		return instance;
	}

	void spawnDegText(Character& target);
	void spawnAddText(Character& target);

	int textCount()const { return texts.size(); }
	textUI* getText(int index) { return texts.at(index).get(); }

	void Clear();

	void update();
	void render(CAMERA& camera);


private:
	std::vector<std::unique_ptr<textUI>> texts;

};