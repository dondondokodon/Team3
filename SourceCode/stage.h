#pragma once
#include"../GameLib/game_lib.h"
#include "CAMERA.h"

//抽象クラス 背景
class Stage
{
public:

	virtual ~Stage() {};
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void deinit() = 0;
	virtual void render() = 0;

};

//スプライトの読み込み用
//ステージレイヤークラス
class StageLayer
{
public:
	VECTOR2 pos;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;
	VECTOR2 speed;
	VECTOR2 offset;
	int angle;
	std::shared_ptr<GameLib::Sprite> spr;

	int act;
	int timer;
	int anime;
	int animeTimer;
	int anime_state;
	float radius;     // 半径

	void render()
	{
		if (!spr) return;
		sprite_render(
			spr.get(),
			pos.x, pos.y,
			scale.x, scale.y,
			texPos.x, texPos.y,
			texSize.x, texSize.y,
			pivot.x, pivot.y,
			angle,
			color.x, color.y, color.z,
			color.w);
	}

	void cameraRender(CAMERA& camera)
	{
		if (!spr)return;
		sprite_render(spr.get(), pos.x - camera.getPos().x, pos.y - camera.getPos().y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle, color.x, color.y, color.z, color.w);
	}

};

//ステージ１
class Stage01 : public Stage
{
private:
	StageLayer back;		//背景（グラデーション）
	StageLayer back_back;	//遠々背景
	StageLayer middle;		//中背景
	StageLayer front;		//近背景
	StageLayer ground;		//地面

public:
	Stage01() {};
	~Stage01()override {};
	void init()override;
	void update()override;
	void deinit()override;
	void render()override;
	void cameraRender(CAMERA camera);

};

//以下、ステージを追加するときはStageを継承する