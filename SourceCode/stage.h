#pragma once
#include"../GameLib/game_lib.h"
#include "CAMERA.h"
#include "Player.h"
#include "HitWall.h"

//抽象クラス 背景
class Stage
{
protected:
	int stageNo;
public:

	virtual ~Stage() {};
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void deinit() = 0;
	virtual void render() = 0;
	virtual void cameraRender(CAMERA camera) = 0;
	int getStageNo() { return stageNo; }
	virtual void checkFootingCollision(Player& character) {};
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
		sprite_render(spr.get(), pos.x - camera.getPos().x * speed.x, pos.y - camera.getPos().y * speed.y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle, color.x, color.y, color.z, color.w);
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
	StageLayer footing;		//足場

	HitWall footingWall; //足場の当たり判定

public:
	Stage01() { stageNo = 1; };
	~Stage01()override {};
	void init()override;
	void update()override;
	void deinit()override;
	void render()override;
	void cameraRender(CAMERA camera);
	void checkFootingCollision(Player& character);

};

//ランタンの明かり
class light 
{
public:
	light(){}
	~light(){}
	void init(VECTOR2 pos);
	void update();

	StageLayer lamp[4];
	void render(CAMERA& camera);
};

//ステージ2
class Stage02 : public Stage
{
private:
	StageLayer back;		//背景
	//StageLayer back_back;	//遠々背景
	StageLayer middle;		//中背景
	StageLayer front;		//近背景
	light Light1;
	light Light2;
	light Light3;

public:
	Stage02() { stageNo = 2; };
	~Stage02()override {};
	void init()override;
	void update()override;
	void deinit()override;
	void render()override;
	void cameraRender(CAMERA camera)override;

};

//以下、ステージを追加するときはStageを継承する

class resultScene :public Stage
{
private:
	StageLayer back;		//背景
	//StageLayer back_back;	//遠々背景
	StageLayer rank;		//ランクの文字
	StageLayer resultMassage;//リザルトメッセージ

public:
	resultScene() {};
	~resultScene()override {};
	void init()override;
	void update()override;
	void deinit()override;
	void render()override;
	void cameraRender(CAMERA camera)override {};

};